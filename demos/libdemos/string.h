/*
 * $Id: string.h,v 1.1 2000/09/13 07:45:36 konkers Exp $
 */

#ifndef __lib_string_h__
#define __lib_string_h__

#include "stdlib.h"

int strlen( char * str );
int strcmp( char * str1, char *str2 );
char *strcpy( char *str1, char *str2 );
char *strncpy( char *str1, char *str2, int len );
char *strcat( char *str1, char *str2 );
int strncmp( unsigned char *str1, unsigned char *str2, int n );
void memcpy( void *reg2, const void *reg1, unsigned int n);
void memset( void *mem, int c, size_t n );
int memcmp(const void *s1, const void *s2, size_t n);


#endif
