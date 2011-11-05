/* $Id: interrupt.c,v 1.2 2000/09/13 08:00:17 konkers Exp $
 *
 * handles interrupts and the IDT
 *
 */

#include "io.h"
#include "string.h"
#include "interrupt.h"


unsigned char IDT[ 8 * 48 ];  /* with a real malloc one could do the "right" thing here */

void init_idt( void )
{
	/* allocate IDT 
	 * 48 entries:
	 *  32 for exceptions 
	 *  16 for hardware interrupts 
	 */
    memset( IDT, 0x0, 8 * 48 );

}


void lidt( void * base, unsigned int limit )
{
        unsigned int i[2];
        
        i[0] = limit<<16;
        i[1] = (unsigned int) base;

	    /* lidt takes a memory location which has bits 0..15 as the limit
	     * and 16..47 as the base of the IDT
	     */
        asm( "lidt (%0)": :"a" (((char *) i)+2));
}


void load_idt( void )
{
    lidt( (void *) IDT, 8 * 48 ); /*0x7ff );*/
}

/* here we simply move all the bits into the right locations and
 * fill position i in the IDT 
 */
void set_idt_entry( int i, unsigned int offset, unsigned int seg,
		    int p, int dpl, int type )
{
    ((unsigned int *)IDT)[(i*2)+0] =
	(offset & 0x0000ffff) | 
	((seg & 0x0000ffff) << 16) ;
	 
    ((unsigned int *)IDT)[(i*2)+1] =
	((p & 0x1) << 15 ) |
	((dpl & 0x3 ) << 13) |
	((type & 0xf) << 8 ) |
	(((offset>>16) & 0x0000ffff) << 16);

}

