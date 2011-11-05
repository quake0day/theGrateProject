/*
 * Week 1: Hello World
 * 
 * $Id: main.c,v 1.2 2000/09/13 08:00:17 konkers Exp $
 */

#include "boot.h"
#include "printf.h"
#include "io.h"

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
    printf( " Week 1: " );
    set_attrib( ATTRIB_RED | ATTRIB_BLACK_BG );
    printf( "Getting Started\n\n" );
    set_attrib( ATTRIB_WHITE | ATTRIB_BLACK_BG );
    
    printf( "Hello World!\n" );

    asm("hlt");

}
