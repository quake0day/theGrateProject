/*
 * $Id: ctype.h,v 1.2 2000/09/13 08:00:17 konkers Exp $
 * 
 * varios character type checks
 */

#ifndef __CTYPE_H_
#define __CTYPE_H_

#define _U      0x01 // upper
#define _L      0x02 // lower
#define _N      0x04 // number
#define _S      0x08 // space - blank and more...
#define _P      0x10 // punct
#define _C      0x20 // control
#define _X      0x40 // hex
#define _B      0x80 // blank - ' ' or '\t'

extern char __ctype[];

#define __is_char( c, type )  ( __ctype[c+1] & (type) )

#define isalnum( c )    __is_char( c, _U|_L|_N )
#define isalpha( c )    __is_char( c, _U|_L )
#define isascii( c )    __is_char( c, _U|_L|_N|_P|_B )
#define isblank( c )    __is_char( c, _B )
#define iscntrl( c )    __is_char( c, _C )
#define isdigit( c )    __is_char( c, _N )
#define islower( c )    __is_char( c, _L )
#define isprint( c )    __is_char( c, _U|_L|_N|_P|_B )
#define ispunct( c )    __is_char( c, _P )
#define isspace( c )    __is_char( c, _S )
#define isupper( c )    __is_char( c, _U )
#define isxdigit( c )   __is_char( c, _N|_X )

#endif
