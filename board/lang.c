// Display, command/response strings
#include "../app.h"
static const struct CR_DATA CrData[] = {
	{
		.headder = "MCHP Tech MP V",
		.bootb = "Boot Button Pressed ",
		.buttonp = "When done press OK  ",
		.done = "Resolver value SET  ",
		.blank = "                    ",
		.c1 = "booting...",
		.r1 = "booting...",
		.c2 = "HVER\r\n",
		.r2 = "Drive 70",
		.c3 = "MPOLES\r\n",
		.r3 = "24",
		.angle = ".",
		.diskmove = "Wait, moving",
		.error = "Reboot SPIN AMP\r\n",
		.s1 = "Press Clear Error on",
		.w1 = "Spin Motor SCREEN   ",
		.s2 = "Press FLIP UP on    ",
		.w2 = "MID LEVEL SCREEN    ",
		.s3 = "Power Cycle Spin AMP",
		.w3 = "with Scan Safety Key",
		.dis = "DIS\r\n",
		.msg2 = "MSG 2\r\n",
		.mpoles0 = "MPOLES 0\r\n",
		.mphase90 = "MPHASE 90\r\n",
		.opmode2 = "OPMODE 2\r\n",
		.opmode3 = "OPMODE 3\r\n",
		.en = "EN\r\n",
		.t35 = "T 35\r\n",
		.pfb = "PFB\r\n",
		.msg0 = "MSG 0\r\n",
		.mnumber0 = "MNUMBER 0\r\n",
		/* CHANGE THIS TO THE REAL 'SAVE' COMMAND 
		 * in the production version.
		 */
#ifdef	PRODUCTION
		.save_parm = "SAVE\r\n",
#else
		.save_parm = "XXXXX\r\n",
#endif
		.line1 = "\eO\x01\x01%s",
		.line2 = "\eO\x01\x02%s",
		.line3 = "\eO\x01\x03%s",
		.line4 = "\eO\x01\x04%s",
		.line_d = "\eO\x01\x01%s %d ",
		.line_h = "\eO\x01\x04%s%s",
	},
	{
		.headder = " ",
	}
};

static const struct RS_DATA RsData[] = {
	{
		.line_m = " MPHASE SAVED %d     \r\n",
		.line_ms = "MPHASE  %d\r\n",
		.line_o = "\eO\x01\x02 offset %d",
		.line_s = "%s",
		.line_b0 = "remove X6 plug\r\n",
		.line_b1 = "power cycle spin amp\r\n",
	},
	{
		.line_m = " ",
	}
};

// set strings to the proper controller
const struct CR_DATA *cr_text = &CrData[MC_SS600];
const struct RS_DATA *rs_text = &RsData[MC_SS600];