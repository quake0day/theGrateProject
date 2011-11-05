/*
 * $Id: assert.c,v 1.2 2000/09/13 08:00:17 konkers Exp $
 *
 * simple assert handler#
 */

#include "printf.h"
#include "string.h"
#include "assert.h"

void print_assert( char *msg, char * file, char *bfile, int line )
{
    asm("cli");
    
    printf( "ASSERT( %s ) in file %s", msg, file );

    if( strcmp( file, bfile ) )
    {
	printf( " (included from %s)", bfile );
    }

    printf( ", line %d\n", line );

	/* some of the below are possible things to do here */
/*    asm("sti"); */
/*    asm("hlt"); */
}
