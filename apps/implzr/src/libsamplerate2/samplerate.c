/*
** Copyright (C) 2002-2004 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"config.h"

#include	"samplerate2.h"
#include	"common.h"
#include	"float_cast.h"

static long SR2_(psrc_set_converter) (SR2_(SRC_PRIVATE)	*psrc, long converter_type) ;


SR2_(SRC_STATE) *
SR2_(src_new) (long converter_type, long channels, long *error)
{	SR2_(SRC_PRIVATE)	*psrc ;

	if (error)
		*error = SRC_ERR_NO_ERROR ;

	if (channels < 1)
	{	if (error)
			*error = SRC_ERR_BAD_CHANNEL_COUNT ;
		return NULL ;
		} ;

	if ((psrc = calloc (1, sizeof (*psrc))) == NULL)
	{	if (error)
			*error = SRC_ERR_MALLOC_FAILED ;
		return NULL ;
		} ;

	psrc->channels = channels ;
	psrc->mode = SRC_MODE_PROCESS ;

	if (SR2_(psrc_set_converter) (psrc, converter_type) != SRC_ERR_NO_ERROR)
	{	if (error)
			*error = SRC_ERR_BAD_CONVERTER ;
		free (psrc) ;
		psrc = NULL ;
		} ;

	SR2_(src_reset) ((SR2_(SRC_STATE)*) psrc) ;

	return (SR2_(SRC_STATE)*) psrc ;
} /* src_new */

SR2_(SRC_STATE)*
SR2_(src_callback_new) (SR2_(src_callback_t) func, long converter_type, long channels, long *error, void* cb_data)
{	SR2_(SRC_STATE)	*src_state ;

	if (func == NULL)
	{	if (error)
			*error = SRC_ERR_BAD_CALLBACK ;
		return NULL ;
		} ;

	if (error != NULL)
		*error = 0 ;

	src_state = SR2_(src_new) (converter_type, channels, error) ;

	SR2_(src_reset) (src_state) ;

	((SR2_(SRC_PRIVATE)*) src_state)->mode = SRC_MODE_CALLBACK ;
	((SR2_(SRC_PRIVATE)*) src_state)->callback_func = func ;
	((SR2_(SRC_PRIVATE)*) src_state)->user_callback_data = cb_data ;

	return src_state ;
} /* src_callback_new */

SR2_(SRC_STATE) *
SR2_(src_delete) (SR2_(SRC_STATE) *state)
{	SR2_(SRC_PRIVATE) *psrc ;

	psrc = (SR2_(SRC_PRIVATE)*) state ;
	if (psrc)
	{	if (psrc->private_data)
			free (psrc->private_data) ;
		memset (psrc, 0, sizeof (SR2_(SRC_PRIVATE))) ;
		free (psrc) ;
		} ;

	return NULL ;
} /* src_state */

long SR2_(src_process) (SR2_(SRC_STATE) *state, SR2_(SRC_DATA) *data)
{	SR2_(SRC_PRIVATE) *psrc ;
	long error ;

	psrc = (SR2_(SRC_PRIVATE)*) state ;

	if (psrc == NULL)
		return SRC_ERR_BAD_STATE ;
	if (psrc->process == NULL)
		return SRC_ERR_BAD_PROC_PTR ;

	if (psrc->mode != SRC_MODE_PROCESS)
		return SRC_ERR_BAD_MODE ;

	/* Check for valid SR2_(SRC_DATA) first. */
	if (data == NULL)
		return SRC_ERR_BAD_DATA ;

	/* Check src_ratio is in range. */
	if (data->src_ratio < (1.0 / SRC_MAX_RATIO) || data->src_ratio > (1.0 * SRC_MAX_RATIO))
		return SRC_ERR_BAD_SRC_RATIO ;

	/* And that data_in and data_out are valid. */
	if (data->data_in == NULL || data->data_out == NULL)
		return SRC_ERR_BAD_DATA_PTR ;

	if (data->data_in == NULL)
		data->input_frames = 0 ;

	if (data->input_frames < 0)
		data->input_frames = 0 ;
	if (data->output_frames < 0)
		data->output_frames = 0 ;

	if (data->data_in < data->data_out)
	{	if (data->data_in + data->input_frames * psrc->channels > data->data_out)
		{	/*-printf ("\n\ndata_in: %p    data_out: %p\n",
				(void*) (data->data_in + data->input_frames * psrc->channels), (void*) data->data_out) ;-*/
			return SRC_ERR_DATA_OVERLAP ;
			} ;
		}
	else if (data->data_out + data->output_frames * psrc->channels > data->data_in)
	{	/*-printf ("\n\ndata_in : %p   ouput frames: %ld    data_out: %p\n", (void*) data->data_in, data->output_frames, (void*) data->data_out) ;

		printf ("data_out: %p (%p)    data_in: %p\n", (void*) data->data_out,
			(void*) (data->data_out + data->input_frames * psrc->channels), (void*) data->data_in) ;-*/
		return SRC_ERR_DATA_OVERLAP ;
		} ;

	/* Set the input and output counts to zero. */
	data->input_frames_used = 0 ;
	data->output_frames_gen = 0 ;

	/* Special case for when last_ratio has not been set. */
	if (psrc->last_ratio < (1.0 / SRC_MAX_RATIO))
		psrc->last_ratio = data->src_ratio ;

	/* Now process. */
	error = psrc->process (psrc, data) ;

	return error ;
} /* src_process */

long
SR2_(src_callback_read) (SR2_(SRC_STATE) *state, double src_ratio, long frames, sr2_float_t *data)
{	SR2_(SRC_PRIVATE)	*psrc ;
	SR2_(SRC_DATA)	src_data ;

	long	output_frames_gen ;
	long 	error = 0 ;

	if (state == NULL)
		return 0 ;

	if (frames <= 0)
		return 0 ;

	psrc = (SR2_(SRC_PRIVATE)*) state ;

	if (psrc->mode != SRC_MODE_CALLBACK)
	{	psrc->error = SRC_ERR_BAD_MODE ;
		return 0 ;
		} ;

	if (psrc->callback_func == NULL)
	{	psrc->error = SRC_ERR_NULL_CALLBACK ;
		return 0 ;
		} ;

	memset (&src_data, 0, sizeof (src_data)) ;

	/* Check src_ratio is in range. */
	if (src_ratio < (1.0 / SRC_MAX_RATIO) || src_ratio > (1.0 * SRC_MAX_RATIO))
	{	psrc->error = SRC_ERR_BAD_SRC_RATIO ;
		return 0 ;
		} ;

	/* Switch modes temporarily. */
	src_data.src_ratio = src_ratio ;
	src_data.data_out = data ;
	src_data.output_frames = frames ;

	src_data.data_in = psrc->saved_data ;
	src_data.input_frames = psrc->saved_frames ;

	output_frames_gen = 0 ;
	while (output_frames_gen < frames)
	{
		if (src_data.input_frames == 0)
		{	sr2_float_t *ptr ;

			src_data.input_frames = psrc->callback_func (psrc->user_callback_data, &ptr) ;
			src_data.data_in = ptr ;

			if (src_data.input_frames == 0)
				src_data.end_of_input = 1 ;
			} ;

		/*
		** Now call process function. However, we need to set the mode
		** to SRC_MODE_PROCESS first and when we return set it back to
		** SRC_MODE_CALLBACK.
		*/
		psrc->mode = SRC_MODE_PROCESS ;
		error = SR2_(src_process) (state, &src_data) ;
		psrc->mode = SRC_MODE_CALLBACK ;

		if (error != 0)
			break ;

		src_data.data_in += src_data.input_frames_used * psrc->channels ;
		src_data.input_frames -= src_data.input_frames_used ;

		src_data.data_out += src_data.output_frames_gen * psrc->channels ;
		src_data.output_frames -= src_data.output_frames_gen ;

		output_frames_gen += src_data.output_frames_gen ;

		if (src_data.end_of_input == SRC_TRUE && src_data.output_frames_gen == 0)
			break ;
		} ;

	psrc->saved_data = src_data.data_in ;
	psrc->saved_frames = src_data.input_frames ;

	if (error != 0)
	{	psrc->error = error ;
	 	return 0 ;
		} ;

	return output_frames_gen ;
} /* src_callback_read */

/*==========================================================================
*/

long SR2_(src_set_ratio) (SR2_(SRC_STATE) *state, double new_ratio)
{	SR2_(SRC_PRIVATE) *psrc ;

	psrc = (SR2_(SRC_PRIVATE)*) state ;

	if (psrc == NULL)
		return SRC_ERR_BAD_STATE ;
	if (psrc->process == NULL)
		return SRC_ERR_BAD_PROC_PTR ;

	psrc->last_ratio = new_ratio ;

	return SRC_ERR_NO_ERROR ;
} /* src_set_ratio */

long SR2_(src_reset) (SR2_(SRC_STATE) *state)
{	SR2_(SRC_PRIVATE) *psrc ;

	if ((psrc = (SR2_(SRC_PRIVATE)*) state) == NULL)
		return SRC_ERR_BAD_STATE ;

	if (psrc->reset != NULL)
		psrc->reset (psrc) ;

	psrc->last_position = 0.0 ;
	psrc->last_ratio = 0.0 ;

	psrc->saved_data = NULL ;
	psrc->saved_frames = 0 ;

	psrc->error = SRC_ERR_NO_ERROR ;

	return SRC_ERR_NO_ERROR ;
} /* src_reset */

/*==============================================================================
**	Error reporting functions.
*/

long SR2_(src_error) (SR2_(SRC_STATE) *state)
{	if (state)
		return ((SR2_(SRC_PRIVATE)*) state)->error ;
	return SRC_ERR_NO_ERROR ;
} /* src_error */

/*==============================================================================
**	Simple interface for performing a single conversion from input buffer to
**	output buffer at a fixed conversion ratio.
*/

long SR2_(src_simple) (SR2_(SRC_DATA) *src_data, long converter, long channels)
{	SR2_(SRC_STATE)	*src_state ;
	long 		error ;

	if ((src_state = SR2_(src_new) (converter, channels, &error)) == NULL)
		return error ;

	src_data->end_of_input = 1 ; /* Only one buffer worth of input. */

	error = SR2_(src_process) (src_state, src_data) ;

	src_state = SR2_(src_delete) (src_state) ;

	return error ;
} /* src_simple */

/*==============================================================================
**	Private functions.
*/

static long SR2_(psrc_set_converter)(SR2_(SRC_PRIVATE) *psrc, long converter_type)
{
	if (SR2_(sinc_set_converter) (psrc, converter_type) == SRC_ERR_NO_ERROR)
		return SRC_ERR_NO_ERROR ;

	if (SR2_(zoh_set_converter) (psrc, converter_type) == SRC_ERR_NO_ERROR)
		return SRC_ERR_NO_ERROR ;

	if (SR2_(linear_set_converter) (psrc, converter_type) == SRC_ERR_NO_ERROR)
		return SRC_ERR_NO_ERROR ;

	return SRC_ERR_BAD_CONVERTER ;
} /* psrc_set_converter */
