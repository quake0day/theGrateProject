/*
 * Week 2: Debugging
 * 
 * $Id: main.c,v 1.2 2000/09/13 08:00:17 konkers Exp $
 */

#include <boot.h>
#include <printf.h>
#include <io.h>
#include <assert.h>

#include "ints.h"

void _start( unsigned int memSize,
                        char *params,
			boot_dir *bd )
{
    screen_init();
    set_attrib( ATTRIB_BRIGHT | ATTRIB_BLUE | ATTRIB_BLACK_BG );
    printf( "Dem" );
    set_attrib( ATTRIB_BRIGHT | ATTRIB_GREEN | ATTRIB_BLACK_BG );
    printf( "OS" );
    set_attrib( ATTRIB_WHITE | ATTRIB_BLACK_BG );
    printf( " Week 2: " );
    set_attrib( ATTRIB_RED | ATTRIB_BLACK_BG );
    printf( "Debugging Methods\n\n" );
    set_attrib( ATTRIB_WHITE | ATTRIB_BLACK_BG );

    printf( "Initializing Exceptions: " );
    init_ints();
    printf( "done\n" );

    printf( "Triggering Divide by Zero: " );
    if( 1 )
    {
	    /* trigger a div 0 excpetions */
	printf( "dividing by zero %d\n", 1/0 ); 
    }
    else
    {
	printf( "skipped\n" );
    }

    printf( "Triggering assert: " );
    if( 1 )
    {
	assert( 1 == 0 );
    }
    else
    {
	printf( "skipped\n" );
    }
    
    printf( "Halting..." );
    asm("hlt");

}
