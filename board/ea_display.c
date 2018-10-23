#include "ea_display.h"

static const char d_reset[] = "\eR";
static const char d_version[] = "\eV";
static const char d_ff[] = "\x0C";
static const char d_cur_off[] = "\eC0";

void display_ea_init(uint16_t pause)
{
	printf("%s", d_reset);
	WaitMs(pause);
}

void display_ea_version(uint16_t pause)
{
	printf("%s", d_version);
	WaitMs(pause);
}

void display_ea_ff(uint16_t pause)
{
	printf("%s", d_ff);
	WaitMs(pause);
}

void display_ea_cursor_off(uint16_t pause)
{
	printf("%s", d_cur_off);
	WaitMs(pause);
}

void display_ea_line(char * line)
{
	printf("%s", line);
}
