#include "ea_display.h"

const char d_reset[] = "\eR";
const char d_version[]= "\eV";
const char d_ff[]= "\x0C";

void display_ea_init(uint16_t pause)
{
	printf("%s",d_reset);
	WaitMs(pause);
}

void display_ea_version(uint16_t pause)
{
	printf("%s",d_version);
	WaitMs(pause);
}

void display_ea_ff(uint16_t pause)
{
	printf("%s",d_ff);
	WaitMs(pause);
}

void display_ea_line(char * line)
{
	printf("%s",line);
}
