/*
  Copyright (c) 2005, The Musepack Development Team
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  * Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the following
  disclaimer in the documentation and/or other materials provided
  with the distribution.

  * Neither the name of the The Musepack Development Team nor the
  names of its contributors may be used to endorse or promote
  products derived from this software without specific prior
  written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <math.h>
#include <string.h>
#include "../include/mpc/streaminfo.h"
#include "../include/mpc/mpcdec.h"
#include "internal.h"
#include "decoder.h"
#include "huffman.h"
#include "mpc_bits_reader.h"

// streaminfo.c
mpc_status streaminfo_read_header_sv8(mpc_streaminfo* si,
									  const mpc_bits_reader * r_in,
									  mpc_size_t block_size);
mpc_status streaminfo_read_header_sv7(mpc_streaminfo* si, mpc_bits_reader * r_in);
void  streaminfo_encoder_info(mpc_streaminfo* si, const mpc_bits_reader * r_in);
void  streaminfo_gain(mpc_streaminfo* si, const mpc_bits_reader * r_in);


enum {
	MPC_BUFFER_SWAP = 1,
	MPC_BUFFER_FULL = 2,
};

static void mpc_demux_clear_buff(mpc_demux * d)
{
	d->bytes_total = 0;
	d->bits_reader.buff = d->buffer;
	d->bits_reader.count = 8;
	d->block_bits = 0;
	d->block_frames = 0;
}

static mpc_uint32_t
mpc_demux_fill(mpc_demux * d, mpc_uint32_t min_bytes, int flags)
{
	mpc_uint32_t unread_bytes = d->bytes_total + d->buffer - d->bits_reader.buff
			- ((8 - d->bits_reader.count) >> 3);
	int offset = 0;

	if (min_bytes == 0 || min_bytes > DEMUX_BUFFER_SIZE ||
		    (unread_bytes < min_bytes && flags & MPC_BUFFER_FULL))
		min_bytes = DEMUX_BUFFER_SIZE;

	if (unread_bytes < min_bytes) {
		mpc_uint32_t bytes2read = min_bytes - unread_bytes;
		mpc_uint32_t bytes_free = DEMUX_BUFFER_SIZE - d->bytes_total;

		if (flags & MPC_BUFFER_SWAP) {
			bytes2read &= -1 << 2;
			offset = (unread_bytes + 3) & ( -1 << 2);
			offset -= unread_bytes;
		}

		if (bytes2read > bytes_free) {
			if (d->bits_reader.count == 0) {
				d->bits_reader.count = 8;
				d->bits_reader.buff++;
			}
			memmove(d->buffer + offset, d->bits_reader.buff, unread_bytes);
			d->bits_reader.buff = d->buffer + offset;
			d->bytes_total = unread_bytes + offset;
		}
		bytes2read = d->r->read(d->r, d->buffer + d->bytes_total, bytes2read);
		if (flags & MPC_BUFFER_SWAP){
			unsigned int i, * tmp = (unsigned int *) (d->buffer + d->bytes_total);
			for(i = 0 ;i < (bytes2read >> 2); i++)
				tmp[i] = mpc_swap32(tmp[i]);
		}
		d->bytes_total += bytes2read;
		return bytes2read;
	}

	return (mpc_uint32_t) -1;
}

/**
 * seek to a bit position in the stream
 * @param d demuxer context
 * @param fpos position in the stream in bits from the beginning of mpc datas
 * @param min_bytes number of bytes to load after seeking
 */
static void
mpc_demux_seek(mpc_demux * d, mpc_size_t fpos, mpc_uint32_t min_bytes) {
// 	mpc_uint32_t cur_pos = d->r->tell(d->r);
	mpc_size_t next_pos;
	mpc_int_t bit_offset;

	// FIXME : do not flush the buffer if fpos is in the current buffer

	next_pos = fpos >> 3;
	if (d->si.stream_version == 7)
		next_pos &= (-1 << 2);
	bit_offset = (int) (fpos - (next_pos << 3));
	next_pos += d->si.header_position; // add id3 offset

	d->r->seek(d->r, (mpc_int32_t) next_pos);
	mpc_demux_clear_buff(d);
	if (d->si.stream_version == 7)
		mpc_demux_fill(d, (min_bytes + ((bit_offset + 7) >> 3) + 3) & (~3), MPC_BUFFER_SWAP);
	else
		mpc_demux_fill(d, min_bytes + ((bit_offset + 7) >> 3), 0);
	d->bits_reader.buff += bit_offset >> 3;
	d->bits_reader.count = 8 - (bit_offset & 7);
}

/**
 * return the current position in the stream (in bits)
 * @param d demuxer context
 * @return current stream position in bits
 */
mpc_size_t mpc_demux_pos(mpc_demux * d)
{
	return ((d->r->tell(d->r) - d->bytes_total + d->bits_reader.buff - d->buffer) << 3) + 8 - d->bits_reader.count;
}

/**
 * Searches for a ID3v2-tag and reads the length (in bytes) of it.
 *
 * @param d demuxer context
 * @return size of tag, in bytes
 * @return MPC_STATUS_FILE on errors of any kind
 */
mpc_int32_t mpc_demux_skip_id3v2(mpc_demux * d)
{
	mpc_uint8_t  tmp [4];
	mpc_bool_t footerPresent;     // ID3v2.4-flag
	mpc_int32_t size;

    // we must be at the beginning of the stream
	mpc_demux_fill(d, 3, 0);

    // check id3-tag
	if ( 0 != memcmp( d->bits_reader.buff, "ID3", 3 ) )
		return 0;

	mpc_demux_fill(d, 10, 0);

	mpc_bits_read(&d->bits_reader, 24); // read ID3
	mpc_bits_read(&d->bits_reader, 16); // read tag version

	tmp[0] = mpc_bits_read(&d->bits_reader, 8); // read flags
	footerPresent = tmp[0] & 0x10;
	if ( tmp[0] & 0x0F )
		return MPC_STATUS_FILE; // not (yet???) allowed

	tmp[0] = mpc_bits_read(&d->bits_reader, 8); // read size
	tmp[1] = mpc_bits_read(&d->bits_reader, 8); // read size
	tmp[2] = mpc_bits_read(&d->bits_reader, 8); // read size
	tmp[3] = mpc_bits_read(&d->bits_reader, 8); // read size

	if ( (tmp[0] | tmp[1] | tmp[2] | tmp[3]) & 0x80 )
		return MPC_STATUS_FILE; // not allowed

    // read headerSize (syncsave: 4 * $0xxxxxxx = 28 significant bits)
	size = tmp[0] << 21;
	size |= tmp[1] << 14;
	size |= tmp[2] << 7;
	size |= tmp[3];

	if ( footerPresent )
		size += 10;

	mpc_demux_fill(d, size, 0);
	d->bits_reader.buff += size;

	return size + 10;
}

mpc_status mpc_demux_seek_init(mpc_demux * d)
{
	if (d->seek_table != 0)
		return MPC_STATUS_OK;

	d->seek_pwr = 6;
	if (d->si.block_pwr > d->seek_pwr)
		d->seek_pwr = d->si.block_pwr;
	d->seek_table = (mpc_uint32_t*) malloc((size_t)(2 + d->si.samples / (MPC_FRAME_LENGTH << d->seek_pwr)) * sizeof(mpc_uint32_t));
	if (d->seek_table == 0)
		return MPC_STATUS_FILE;
	d->seek_table[0] = (mpc_uint32_t)mpc_demux_pos(d);
	d->seek_table_size = 1;

	return MPC_STATUS_OK;
}

static void mpc_demux_ST(mpc_demux * d)
{
	mpc_uint64_t tmp;
	mpc_uint32_t * table;
	mpc_bits_reader r = d->bits_reader;
	mpc_uint_t i;

	if (d->seek_table != 0)
		return;

	mpc_bits_get_size(&r, &tmp);
	d->seek_table_size = (mpc_uint32_t) tmp;
	d->seek_pwr = d->si.block_pwr + mpc_bits_read(&r, 4);
	tmp = 2 + d->si.samples / (MPC_FRAME_LENGTH << d->seek_pwr);
	if (tmp < d->seek_table_size) tmp = d->seek_table_size;
	d->seek_table = (mpc_uint32_t*) malloc((size_t)(tmp * sizeof(mpc_uint32_t)));

	table = d->seek_table;
	mpc_bits_get_size(&r, &tmp);
	table[0] = (mpc_uint32_t) (tmp + d->si.header_position) * 8;

	if (d->seek_table_size == 1)
		return;

	mpc_bits_get_size(&r, &tmp);
	table[1] = (mpc_uint32_t) (tmp + d->si.header_position) * 8;

	for (i = 2; i < d->seek_table_size; i++) {
		int code = mpc_bits_golomb_dec(&r, 12);
		if (code & 1)
			code = -(code & (-1 << 1));
		code <<= 2;
		table[i] = code + 2 * table[i-1] - table[i-2];
	}
}

static void mpc_demux_SP(mpc_demux * d, int size, int block_size)
{
	mpc_size_t cur;
	mpc_uint64_t ptr;
	mpc_block b;

	cur = mpc_demux_pos(d);
	mpc_bits_get_size(&d->bits_reader, &ptr);
	mpc_demux_seek(d, (ptr - size) * 8 + cur, 11);
	mpc_bits_get_block(&d->bits_reader, &b);
	if (memcmp(b.key, "ST", 2) == 0) {
		mpc_demux_fill(d, (mpc_uint32_t) b.size, 0);
		mpc_demux_ST(d);
	}
	mpc_demux_seek(d, cur, 11 + block_size);
}

static mpc_status mpc_demux_header(mpc_demux * d)
{
	char magic[4];

	d->si.pns = 0xFF;
	d->si.profile_name = "n.a.";

    // get header position
	d->si.header_position = mpc_demux_skip_id3v2(d);
	if(d->si.header_position < 0) return MPC_STATUS_FILE;

	d->si.tag_offset = d->si.total_file_length = d->r->get_size(d->r);

	mpc_demux_fill(d, 4, 0);
	magic[0] = mpc_bits_read(&d->bits_reader, 8);
	magic[1] = mpc_bits_read(&d->bits_reader, 8);
	magic[2] = mpc_bits_read(&d->bits_reader, 8);
	magic[3] = mpc_bits_read(&d->bits_reader, 8);

	if (memcmp(magic, "MP+", 3) == 0) {
		d->si.stream_version = magic[3] & 15;
		d->si.pns = magic[3] >> 4;
		if (d->si.stream_version == 7) {
			mpc_demux_fill(d, 6 * 4, MPC_BUFFER_SWAP); // header block size + endian convertion
			streaminfo_read_header_sv7(&d->si, &d->bits_reader);
		} else {
			return MPC_STATUS_INVALIDSV;
		}
	} else if (memcmp(magic, "MPCK", 4) == 0) {
		mpc_block b;
		int size;
		mpc_demux_fill(d, 11, 0); // max header block size
		size = mpc_bits_get_block(&d->bits_reader, &b);
		while( memcmp(b.key, "AP", 2) != 0 ){ // scan all blocks until audio
			if (b.key[0] < 65 || b.key[0] > 90 || b.key[1] < 65 || b.key[1] > 90)
				return MPC_STATUS_INVALIDSV;
			if (b.size > (mpc_uint64_t) DEMUX_BUFFER_SIZE - 11)
				return MPC_STATUS_INVALIDSV;
			mpc_demux_fill(d, 11 + (mpc_uint32_t) b.size, 0);
			if (memcmp(b.key, "SH", 2) == 0){
				mpc_status ret = streaminfo_read_header_sv8(&d->si, &d->bits_reader, (mpc_uint32_t) b.size);
				if (ret != MPC_STATUS_OK) return ret;
			} else if (memcmp(b.key, "RG", 2) == 0)
				streaminfo_gain(&d->si, &d->bits_reader);
			else if (memcmp(b.key, "EI", 2) == 0)
				streaminfo_encoder_info(&d->si, &d->bits_reader);
			else if (memcmp(b.key, "SO", 2) == 0)
				mpc_demux_SP(d, size, (mpc_uint32_t) b.size);
			else if (memcmp(b.key, "ST", 2) == 0)
				mpc_demux_ST(d);
			d->bits_reader.buff += b.size;
			size = mpc_bits_get_block(&d->bits_reader, &b);
		}
		d->bits_reader.buff -= size;
		if (d->si.stream_version == 0) // si not initialized !!!
			return MPC_STATUS_INVALIDSV;
	} else
		return MPC_STATUS_INVALIDSV;

	return MPC_STATUS_OK;
}

mpc_demux * mpc_demux_init(mpc_reader * p_reader)
{
	mpc_demux* p_tmp = (mpc_demux*) malloc(sizeof(mpc_demux));

	if (p_tmp != 0) {
		memset(p_tmp, 0, sizeof(mpc_demux));
		p_tmp->r = p_reader;
		mpc_demux_clear_buff(p_tmp);
		p_tmp->seek_table = 0;
		if (mpc_demux_header(p_tmp) == MPC_STATUS_OK &&
				  mpc_demux_seek_init(p_tmp) == MPC_STATUS_OK) {
			p_tmp->d = mpc_decoder_init(&p_tmp->si);
		} else {
			if (p_tmp->seek_table)
				free(p_tmp->seek_table);
			free(p_tmp);
			p_tmp = 0;
		}
	}

	return p_tmp;
}

void mpc_demux_exit(mpc_demux * d)
{
	mpc_decoder_exit(d->d);
	free(d->seek_table);
	free(d);
}

void mpc_demux_get_info(mpc_demux * d, mpc_streaminfo * i)
{
	memcpy(i, &d->si, sizeof d->si);
}

mpc_status mpc_demux_decode(mpc_demux * d, mpc_frame_info * i)
{
	mpc_bits_reader r;
	if (d->si.stream_version >= 8) {
		i->is_key_frame = MPC_FALSE;

		if (d->block_frames == 0) {
			mpc_block b = {{0,0},0};
			d->bits_reader.count &= -8;
			if (d->d->decoded_samples == (d->seek_table_size << d->seek_pwr) * MPC_FRAME_LENGTH) {
				d->seek_table[d->seek_table_size] = (mpc_uint32_t) mpc_demux_pos(d);
				d->seek_table_size ++;
			}
			mpc_demux_fill(d, 11, 0); // max header block size
			mpc_bits_get_block(&d->bits_reader, &b);
			while( memcmp(b.key, "AP", 2) != 0 ) { // scan all blocks until audio
				if (b.key[0] < 65 || b.key[0] > 90 || b.key[1] < 65 || b.key[1] > 90)
					goto error;
				if (memcmp(b.key, "SE", 2) == 0) { // end block
					i->bits = -1;
					return MPC_STATUS_OK;
				}
				if (mpc_demux_fill(d, 11 + (mpc_uint32_t) b.size, 0) == 0)
					goto error;
				d->bits_reader.buff += b.size;
				mpc_bits_get_block(&d->bits_reader, &b);
			}
			d->block_bits = (mpc_uint32_t) b.size * 8;
			d->block_frames = 1 << d->si.block_pwr;
			i->is_key_frame = MPC_TRUE;
		}
		if (d->buffer + d->bytes_total - d->bits_reader.buff <= MAX_FRAME_SIZE)
			mpc_demux_fill(d, (d->block_bits >> 3) + 1, 0);
		r = d->bits_reader;
		mpc_decoder_decode_frame(d->d, &d->bits_reader, i);
		d->block_bits -= ((d->bits_reader.buff - r.buff) << 3) + r.count - d->bits_reader.count;
		d->block_frames--;
		if (d->block_bits < 0 || (d->block_frames == 0 && d->block_bits > 7))
			goto error;
	} else {
		if (d->d->decoded_samples == (d->seek_table_size << d->seek_pwr) * MPC_FRAME_LENGTH) {
			d->seek_table[d->seek_table_size] = (mpc_uint32_t) mpc_demux_pos(d);
			d->seek_table_size ++;
		}
		mpc_demux_fill(d, MAX_FRAME_SIZE, MPC_BUFFER_FULL | MPC_BUFFER_SWAP);
		d->block_bits = (mpc_int_t) mpc_bits_read(&d->bits_reader, 20); // read frame size
		if (MPC_FRAME_LENGTH > d->d->samples - d->d->decoded_samples - 1) d->block_bits += 11; // we will read last frame size
		r = d->bits_reader;
		mpc_decoder_decode_frame(d->d, &d->bits_reader, i);
		if (i->bits != -1 && d->block_bits != ((d->bits_reader.buff - r.buff) << 3) + r.count - d->bits_reader.count)
			goto error;
	}
	if (i->bits != -1 && d->buffer + d->bytes_total < d->bits_reader.buff + ((8 - d->bits_reader.count) >> 3))
		goto error;

	return MPC_STATUS_OK;
error:
		i->bits = -1; // we pretend it's end of file
		return MPC_STATUS_INVALIDSV;
}

mpc_status mpc_demux_seek_second(mpc_demux * d, double seconds)
{
	return mpc_demux_seek_sample(d, (mpc_int64_t)(seconds * (double)d->si.sample_freq + 0.5));
}

mpc_status mpc_demux_seek_sample(mpc_demux * d, mpc_uint64_t destsample)
{
	mpc_uint32_t fwd, samples_to_skip, fpos, i;
	mpc_uint32_t block_samples = MPC_FRAME_LENGTH << d->si.block_pwr;

	destsample += d->si.beg_silence;
	if (destsample > d->si.samples) destsample = d->si.samples;
	fwd = (mpc_uint32_t) (destsample / block_samples);
	samples_to_skip = MPC_DECODER_SYNTH_DELAY +
			(mpc_uint32_t) (destsample % block_samples);
	if (d->si.stream_version == 7) {
		if (fwd > 32) {
			fwd -= 32;
			samples_to_skip += MPC_FRAME_LENGTH * 32;
		} else {
			samples_to_skip += MPC_FRAME_LENGTH * fwd;
			fwd = 0;
		}
	}

	i = fwd >> (d->seek_pwr - d->si.block_pwr);
	if (i >= d->seek_table_size)
		i = d->seek_table_size - 1;
	fpos = d->seek_table[i];
	i <<= d->seek_pwr - d->si.block_pwr;
	d->d->decoded_samples = i * block_samples;

	if (d->si.stream_version >= 8) {
		mpc_block b;
		int size;
		mpc_demux_seek(d, fpos, 11);
		size = mpc_bits_get_block(&d->bits_reader, &b);
		while(i < fwd) {
			if (memcmp(b.key, "AP", 2) == 0) {
				if (d->d->decoded_samples == (d->seek_table_size << d->seek_pwr) * MPC_FRAME_LENGTH) {
					d->seek_table[d->seek_table_size] = (mpc_uint32_t) mpc_demux_pos(d) - 8 * size;
					d->seek_table_size ++;
				}
				d->d->decoded_samples += block_samples;
				i++;
			}
			fpos += ((mpc_uint32_t)b.size + size) * 8;
			mpc_demux_seek(d, fpos, 11);
			size = mpc_bits_get_block(&d->bits_reader, &b);
		}
		d->bits_reader.buff -= size;
	} else {
		mpc_decoder_reset_scf(d->d, fpos != d->seek_table[0]);
		mpc_demux_seek(d, fpos, 4);
		for( ; i < fwd; i++){
			if (d->d->decoded_samples == (d->seek_table_size << d->seek_pwr) * MPC_FRAME_LENGTH) {
				d->seek_table[d->seek_table_size] = (mpc_uint32_t) mpc_demux_pos(d);
				d->seek_table_size ++;
			}
			d->d->decoded_samples += block_samples;
			fpos += mpc_bits_read(&d->bits_reader, 20) + 20;
			mpc_demux_seek(d, fpos, 4);
		}
	}
	d->d->samples_to_skip = samples_to_skip;
	return MPC_STATUS_OK;
}

void mpc_set_replay_level(mpc_demux * d, float level, mpc_bool_t use_gain,
						  mpc_bool_t use_title, mpc_bool_t clip_prevention)
{
	float peak = use_title ? d->si.peak_title : d->si.peak_album;
	float gain = use_title ? d->si.gain_title : d->si.gain_album;

	if(!use_gain && !clip_prevention)
		return;

	if(!peak)
		peak = 1.;
	else
		peak = (1 << 15) / pow(10.0, (int) (peak / (20 * 256)));

	if(!gain)
		gain = 1.;
	else
		gain = pow(10.0, (int) ((level - gain / 256) / 20));

	if(clip_prevention && (peak < gain || !use_gain))
		gain = peak;

	mpc_decoder_scale_output(d->d, gain);
}
