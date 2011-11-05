/*
 * $Id: interrupt.h,v 1.3 2000/09/13 08:03:23 konkers Exp $
 *
 */

#include "regs.h"


/* there are the stub macros for wrapping our interrupt/exception
 * handers
 */

/* this one is for an exceptions handler which gets and error code */
#define EXC_ERR_STUB( name, func )  \
void name( void );\
 asm(".text\n" \
 ".globl " #name "\n" \
 #name ":\n"\
 "  pusha\n" /* push registers onto stack */ \
 "  call " #func "\n" /* call the handler */ \
 "  popa\n" /* pop regisers off of stack */ \
 "  add $4, %esp\n" /* take the error code off the stack */ \
 "  iret")

/* this one is for an exceptions handler which does not get and error code */
#define EXC_STUB( name, func )  \
void name( void );\
 asm(".text\n" \
 ".globl " #name "\n" \
 #name ":\n"\
 "  pusha\n"\
 "  call " #func "\n"\
 "  popa\n"\
 "  iret")

/* this one is for a interrupt handler */
#define INT_STUB( i, name, func )  \
void name( void );\
 asm(".text\n" \
 ".globl " #name "\n" \
 #name ":\n"\
 "  pusha\n"\
 "  push $" #i "\n" \
 "  call " #func "\n"\
 "  add $4, %esp\n"\
 "  popa\n"\
 "  iret")


void init_idt( void );
int init_interrupt( void );
void load_idt( void );
void set_idt_entry(int i, unsigned int offset, unsigned int seg,
		    int p, int dpl, int type );

