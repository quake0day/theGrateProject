/* $Id: printf.c,v 1.2 2000/09/13 08:00:17 konkers Exp $ 
 * 
 * a simple inplemention of many of the printf functions and 
 * simple VGA screen manipulation.
 */


/* no bounds checking so be careful!!!!! */
 
#include "stdlib.h"
#include "stdarg.h"
#include "printf.h"
#include "ctype.h"
#include "io.h"

#define _print_hex( str, len, hex )  _print_hex_common( str, len, hex, 0 )

static void _print_char( char **str, int *len, char c );
static void _print_str( char **str, int *len, char * pstr );
static void _print_int( char **str, int *len, int num );
static void _print_hex_common( char **str, int *len, unsigned int hex, int padded );
static void _va_printf( char **str, int *len, char *fmt, va_list pvar );
static unsigned char getchar( int x, int y );
static unsigned char getattrib( int x, int y );
static void scrollup( void );
static void _write_char( char c );


// Video Card I/O ports
#define TEXT_INDEX      0x03D4
#define TEXT_DATA       0x03D5

// Video Card Index Registers
#define TEXT_CURSOR_LO  0x0F
#define TEXT_CURSOR_HI  0x0E

static unsigned char * vidmem;
static int vidx;
static int vidy;
static unsigned char cur_attrib;

/* 
 * console output functions
 */

void print_char( char c )
{
    int i = -1;
    _print_char( NULL, &i, c );
}

void print_str( char * str )
{
    int i = -1;
    _print_str( NULL, &i, str );
}

void print_int( int num )
{
    int i = -1;
    _print_int( NULL, &i, num );
}

void print_hex_common( unsigned int hex, int padded )
{
    int i = -1;
    _print_hex_common( NULL, &i, hex, padded );
}

void va_printf( char *fmt, va_list pvar )
{
    int i = -1;
    _va_printf( NULL, &i, fmt, pvar );
}

void printf( char *fmt, ...)
{
    int i = -1;
    va_list pvar;    
    va_start(pvar,fmt);
    _va_printf(NULL, &i, fmt,pvar);
    va_end(pvar); 
}



void sprintf( char *str, char *fmt, ... )
{
    int i = -1;
  
    va_list pvar;    
    va_start(pvar,fmt);
    _va_printf( &str, &i, fmt,pvar);
    va_end(pvar);   
}

void va_sprintf( char *str, char *fmt, va_list pvar )
{
    int i = -1;
  
    _va_printf( &str, &i, fmt,pvar);
}
 

void snprintf( char *str, int len, char *fmt, ... )
{
    va_list pvar;    
    va_start(pvar,fmt);
    _va_printf( &str, &len, fmt,pvar);
    va_end(pvar);   
}

void va_snprintf( char *str, int len, char *fmt, va_list pvar )
{
    _va_printf( &str, &len, fmt,pvar);
}
 
/* 
 * core functions
 */
static void _print_char( char **str, int *len, char c )
{
    if( str )
    {
	if( *len != 0 )
	{
	    *(*str)++ = c;
	    (*len)--;
	}
    }
    else
    {
	_write_char( c );
    }
}

static void _print_str( char **str, int *len, char * pstr )
{
    while( *pstr )
    {
        _print_char( str, len, *pstr );
        pstr++;
    }
}

static void _print_int( char **str, int *len, int num )
{
    char nstr[12];
    int i=10;
    
    if( num == 0 )
    {
        _print_char(str, len, '0');
    }

    if( num < 0 )
    {
        _print_char(str, len, '-');
        _print_int(str, len,  -1 * num );
        return;
    }
    nstr[11]='\0';
    
    while( (i>0) && num )
    {
        nstr[i] = '0' + (num % 10);
        num /= 10;
        i--;
    }

    _print_str(str, len, nstr + i+1);
}

static void _print_hex_common( char **str, int *len, unsigned int hex, int pad )
{
    char nstr[14];
    int i=12,j;
    nstr[13]='\0';

    pad--;

    for( j=0 ; j < 8  ; j++ )
    {
        if( (hex % 16) < 10 )
            nstr[i] = '0' + (hex % 16);
        else
            nstr[i] = 'a' + ((hex%16)-10);
        hex /= 16;
        i--;
	if( (j>=pad)  && (hex <= 0 ) )
	    break;
    }

    _print_str( str, len, nstr + i + 1 );

}

static void _va_printf( char **str, int *len, char *fmt, va_list pvar )
{
    while( *fmt )
    {
	if( *fmt == '%' )
	{
	    fmt++;
	    if( ! *fmt )
		return;

	    switch( *fmt )
	    {
		case 's':
		    _print_str( str, len, va_arg( pvar, char * ) );
		    break;
		    
		case 'c':
		    _print_char( str, len, va_arg( pvar, char ) );
		    break;
		    
		case 'd':
		    _print_int( str, len, va_arg( pvar, int ) );
		    break;
		    
		case 'x':
		    _print_hex( str, len, va_arg( pvar, unsigned int ) );
		    break;
		    
		case '0':
		    fmt++;
 		    if(*fmt == 'x') {
		        _print_hex_common( str, len, 
			    va_arg(pvar, unsigned int), 8);
		    } else {
			int pad = 0;
			int col = 0;
			while (isdigit(*fmt)) {
			    pad *= (col * 10);
			    pad += (*fmt) - '0';
			    col++;
			    fmt++;
			}
			if (*fmt != 'x')
			    break;

			_print_hex_common( str, len, 
			    va_arg(pvar, unsigned int), pad);
		    }
		    break;

		default:
		    if (isdigit(*fmt)) {
		        int pad = 0;
		        int col = 0;
			while (isdigit(*fmt)) {
			    pad *= (col * 10);
			    pad += (*fmt) - '0';
			    col++;
			    fmt++;
			}
			if( *fmt != 'x' )
			    break;

			_print_hex_common( str, len, 
				va_arg(pvar, unsigned int), pad);
		    }
		    break;
	    }
	}
	else
	{
	    _print_char( str, len, *fmt );
	}
	fmt++;
    }

}


void screen_init( void )
{
    
    int i,j;

    vidmem = (unsigned char *) 0xb8000;

    set_attrib( ATTRIB_WHITE | ATTRIB_BLACK_BG  );

    for( i=0; i<80 ; i++)
    {
	for( j=0; j<25 ; j++ )
	{
	    screen_putchar(i,j,' ', cur_attrib);
	}
    }
    screen_gotoxy(0,0);
}

void screen_gotoxy( int x, int y )
{
    short pos=y*80+x;
    vidx = x;
    vidy = y;

    outb(TEXT_CURSOR_LO,TEXT_INDEX);        // access lo cursor data reg
    outb((char)pos,TEXT_DATA);
    outb(TEXT_CURSOR_HI,TEXT_INDEX);        // access hi cursor data reg
    outb((unsigned char)(pos >> 8),TEXT_DATA);
}

void screen_putchar( int x, int y, unsigned char c, unsigned char attrib )
{
    vidmem[((x) + (y)*80)*2]=c;
    vidmem[(((x) + (y)*80)*2)+1]=attrib;
}

static unsigned char getchar( int x, int y )
{
    return vidmem[((x) + (y)*80)*2];
}

static unsigned char getattrib( int x, int y )
{
    return vidmem[(((x) + (y)*80)*2)+1];
}

static void scrollup( void )
{
     int i,j;
    for( j=1; j<24;j++)
    {
	for( i=0; i<80 ; i++)
	{
	    screen_putchar(i,j,getchar(i,j+1),getattrib(i,j+1));
	}
    }
    for( i=0;i<80;i++)
    {
	screen_putchar(i,24,' ', cur_attrib);
    }
}

static void _write_char( char c )
{
    if( c == '\n' )
    {
	screen_gotoxy( 0, ++vidy );
    }
    else
    {
	screen_putchar( vidx, vidy, (unsigned char) c, cur_attrib);
	screen_gotoxy( ++vidx, vidy );
    }
    
	// off right edge
    if( vidx > 79 )
    {
	screen_gotoxy( 0, ++vidy );
    }
    
	// off bottom
    if( vidy > 24 )
    {
	scrollup();
	screen_gotoxy( vidx, 24 );
    }
}

void set_attrib( unsigned char attrib )
{
    cur_attrib = attrib;
}
