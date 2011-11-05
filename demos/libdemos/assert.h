/*
 * $Id: assert.h,v 1.2 2000/09/13 08:00:17 konkers Exp $
 *
 * simple assert macro
 */

#ifndef __lib_assert_h__
#define __lib_assert_h__

#ifdef ASSERT

void print_assert( char *msg, char * file, char *bfile, int line );

#define assert(msg) if(msg) ; \
else print_assert( #msg, __FILE__, __BASE_FILE__, __LINE__ )

#else
#define assert(msg)
#endif 


#endif
