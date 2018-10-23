/* 
 * File:   ea_display.h
 * Author: root
 *
 * Created on October 9, 2018, 8:04 AM
 */

#ifndef EA_DISPLAY_H
#define	EA_DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "../app.h"

	void display_ea_init(uint16_t);
	void display_ea_version(uint16_t);
	void display_ea_ff(uint16_t);
	void display_ea_cursor_off(uint16_t);
	void display_ea_line(char *);

#ifdef	__cplusplus
}
#endif

#endif	/* EA_DISPLAY_H */

