#include "pfb.h"

// resolver angle data from controller parser

uint16_t get_pfb(char * buf)
{
	float offset, mphase;
	uint16_t offset_whole;
	char *token, pfb_ascii[BT_RX_PKT_SZ + 2], s[2] = " ";

	strcpy(pfb_ascii, buf);
	token = strtok(pfb_ascii, s); // start token search
	token = strtok(NULL, s); // look for the second number

	if (token != NULL) {
		mphase = atof(token);
		offset = ((MOTOR_POLES / MOTOR_PAIRS) * mphase) / 360.0;
		offset_whole = (int16_t) offset; // get the whole part with no rounding
		offset = (offset - (float) offset_whole)*360.0; // extract fractional part for angle offset
		/* need to round and convert data to integer */
		return(uint16_t) roundf(offset);
	} else
		return(666);
}
