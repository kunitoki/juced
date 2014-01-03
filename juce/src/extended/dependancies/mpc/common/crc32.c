/*
*  C Implementation: crc32
*
*  code from http://www.w3.org/TR/PNG/#D-CRCAppendix
*
*/

/* Table of CRCs of all 8-bit messages. */
static unsigned long mpc_crc_table[256];

/* Flag: has the table been computed? Initially false. */
static int mpc_crc_table_computed = 0;

/* Make the table for a fast CRC. */
static void make_crc_table(void)
{
	unsigned long c;
	int n, k;

	for (n = 0; n < 256; n++) {
		c = (unsigned long) n;
		for (k = 0; k < 8; k++) {
			if (c & 1)
				c = 0xedb88320L ^ (c >> 1);
			else
				c = c >> 1;
		}
		mpc_crc_table[n] = c;
	}
	mpc_crc_table_computed = 1;
}


/* Update a running CRC with the bytes buf[0..len-1]--the CRC
	should be initialized to all 1's, and the transmitted value
	is the 1's complement of the final running CRC (see the
	crc() routine below). */

static unsigned long update_crc(unsigned long crc, unsigned char *buf, int len)
{
	unsigned long c = crc;
	int n;

	if (!mpc_crc_table_computed)
		make_crc_table();
	for (n = 0; n < len; n++) {
		c = mpc_crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
	}
	return c;
}

/* Return the CRC of the bytes buf[0..len-1]. */
static unsigned long crc32(unsigned char *buf, int len)
{
	return update_crc(0xffffffffL, buf, len) ^ 0xffffffffL;
}
