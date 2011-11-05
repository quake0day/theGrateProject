/*
 * $Id: printf.h,v 1.2 2000/09/13 08:00:17 konkers Exp $
 *
 * a simple printf
 *
 * understood printf escape chars:
 * %c = char     %d = signed int    %x = unpaded hex
 * %s = string   %0x = padded hex
 */

#ifndef __PRINTF_H_
#define __PRINTF_H_

#include <stdarg.h>

enum { 
	ATTRIB_BLACK = 0x0,
	ATTRIB_BLUE = 0x1,
	ATTRIB_GREEN = 0x2,
	ATTRIB_CYAN = 0x3,
	ATTRIB_RED = 0x4,
	ATTRIB_MAGENTA = 0x5,
	ATTRIB_YELLOW = 0x6,
	ATTRIB_WHITE = 0x7,
	
	ATTRIB_BRIGHT = 0x8,
	
	ATTRIB_BLACK_BG = 0x00,
	ATTRIB_BLUE_BG = 0x10,
	ATTRIB_GREEN_BG = 0x20,
	ATTRIB_CYAN_BG = 0x30,
	ATTRIB_RED_BG = 0x40,
	ATTRIB_MAGENTA_BG = 0x50,
	ATTRIB_YELLOW_BG = 0x60,
	ATTRIB_WHITE_BG = 0x70,
	
	ATTRIB_BLINK = 0x80

 };

void screen_init( void );
void screen_gotoxy( int x, int y );
void screen_putchar( int x, int y, unsigned char c, unsigned char attrib );
void set_attrib( unsigned char attrib );



#define print_hex( hex )  print_hex_common( hex, 0 )
#define print_padded_hex( hex )  print_hex_common( hex, 8 )

void print_char( char c );
void print_str( char * str );
void print_int( int num );
void print_hex_common( unsigned int hex, int padded );
void va_printf( char *fmt, va_list pvar );
void printf( char *fmt, ...);

void sprintf( char *str, char *fmt, ... );
void va_sprintf( char *str, char *fmt, va_list pvar );

void snprintf( char *str, int len, char *fmt, ... );
void va_snprintf( char *str, int len, char *fmt, va_list pvar );


#endif
