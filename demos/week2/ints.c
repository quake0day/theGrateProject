/*
 * $Id: ints.c,v 1.1 2000/09/13 07:45:36 konkers Exp $
 */

#include <interrupt.h>
#include <printf.h>

#include "ints.h"

void exc0(struct regs r, unsigned int eip,
	  unsigned int cs, unsigned int eflags);  
void exc1(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags);  
void exc2(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags);  
void exc3(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags);  
void exc4(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags);  
void exc5(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags);  
void exc6(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags);  
void exc7(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags);  
void exc8(struct regs r, unsigned int eip, unsigned int errcode, 
	  unsigned int cs, unsigned int eflags);  
void exc9(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags);  
void exc10(struct regs r, unsigned int eip, unsigned int errcode,
	   unsigned int cs, unsigned int eflags);  
void exc11(struct regs r, unsigned int eip, unsigned int errcode,
	   unsigned int cs, unsigned int eflags);  
void exc12(struct regs r, unsigned int eip, unsigned int errcode,
	   unsigned int cs, unsigned int eflags);  
void exc13(struct regs r, unsigned int eip, unsigned int errcode,
	   unsigned int cs, unsigned int eflags);  
void exc14(struct regs r, unsigned int eip, unsigned int errcode,
	   unsigned int cs, unsigned int eflags);  
void exc15(struct regs r, unsigned int eip, 
	   unsigned int cs, unsigned int eflags);  
void exc16(struct regs r, unsigned int eip, 
	   unsigned int cs, unsigned int eflags);  
void exc17(struct regs r, unsigned int eip, 
	   unsigned int cs, unsigned int eflags);  
void exc18(struct regs r, unsigned int eip, 
	   unsigned int cs, unsigned int eflags);  


EXC_STUB( exc0_stub, exc0 );
EXC_STUB( exc1_stub, exc1 );
EXC_STUB( exc2_stub, exc2 );
EXC_STUB( exc3_stub, exc3 );
EXC_STUB( exc4_stub, exc4 );
EXC_STUB( exc5_stub, exc5 );
EXC_STUB( exc6_stub, exc6 );
EXC_STUB( exc7_stub, exc7 );
EXC_ERR_STUB( exc8_stub, exc8 );
EXC_STUB( exc9_stub, exc9 );
EXC_ERR_STUB( exc10_stub, exc10 );
EXC_ERR_STUB( exc11_stub, exc11 );
EXC_ERR_STUB( exc12_stub, exc12 );
EXC_ERR_STUB( exc13_stub, exc13 );
EXC_ERR_STUB( exc14_stub, exc14 );
EXC_STUB( exc15_stub, exc15 );
EXC_STUB( exc16_stub, exc16 );
EXC_STUB( exc17_stub, exc17 );
EXC_STUB( exc18_stub, exc18 );

void init_ints( void )
{
    init_idt();

    set_idt_entry( 0, (unsigned int)exc0_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 1, (unsigned int)exc1_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 2, (unsigned int)exc2_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 3, (unsigned int)exc3_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 4, (unsigned int)exc4_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 5, (unsigned int)exc5_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 6, (unsigned int)exc6_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 7, (unsigned int)exc7_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 8, (unsigned int)exc8_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 9, (unsigned int)exc9_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 10, (unsigned int)exc10_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 11, (unsigned int)exc11_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 12, (unsigned int)exc12_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 13, (unsigned int)exc13_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 14, (unsigned int)exc14_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 15, (unsigned int)exc15_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 16, (unsigned int)exc16_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 17, (unsigned int)exc17_stub, 0x08, 1, 0, 15 );
    set_idt_entry( 18, (unsigned int)exc18_stub, 0x08, 1, 0, 15 );

    load_idt();
}

void dump_regs( struct regs *r )
{
    printf( "eax: 0x%08x  ebx: 0x%08x  ecx: 0x%08x  edx: 0x%08x\n",
	    r->eax, r->ebx, r->ecx, r->edx);
    printf( "esi: 0x%08x  edi: 0x%08x  esp: 0x%08x  ebp: 0x%08x\n",
	    r->esi, r->edi, r->esp, r->ebp);

}
void exc0(struct regs r, unsigned int eip,
	  unsigned int cs, unsigned int eflags)
{
    printf( "Divide by zero exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc1(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags) 
{
    printf( "Debug exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc2(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags)
{
    printf( "Non-Maskable Interrupt:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}
 
void exc3(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags)
{
    printf( "Breakpoint exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc4(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags)
{
    printf( "Overflow exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}
  
void exc5(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags)
{
    printf( "Bound exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc6(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags)
{
    printf( "Invalid Opcode exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}
  
void exc7(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags)
{
    printf( "FPU not available exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc8(struct regs r, unsigned int eip, unsigned int errcode, 
	  unsigned int cs, unsigned int eflags)
{
    printf( "Bound exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x  errcode: 0x%08x\n",
	    eip, cs, eflags, errcode); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc9(struct regs r, unsigned int eip, 
	  unsigned int cs, unsigned int eflags)
{
    printf( "Coprocessor segement overrun exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}
  
void exc10(struct regs r, unsigned int eip, unsigned int errcode,
	   unsigned int cs, unsigned int eflags)
{
    printf( "Invalid TSS exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x  errcode: 0x%08x\n",
	    eip, cs, eflags, errcode); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc11(struct regs r, unsigned int eip, unsigned int errcode,
	   unsigned int cs, unsigned int eflags)
{
    printf( "Segment not present exceoption:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x  errcode: 0x%08x\n",
	    eip, cs, eflags, errcode); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc12(struct regs r, unsigned int eip, unsigned int errcode,
	   unsigned int cs, unsigned int eflags)
{
    printf( "Stack exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x  errcode: 0x%08x\n",
	    eip, cs, eflags, errcode); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc13(struct regs r, unsigned int eip, unsigned int errcode,
	   unsigned int cs, unsigned int eflags)
{
    printf( "General protection exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x  errcode: 0x%08x\n",
	    eip, cs, eflags, errcode); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc14(struct regs r, unsigned int eip, unsigned int errcode,
	   unsigned int cs, unsigned int eflags)
{
    printf( "Page fault:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x  errcode: 0x%08x\n",
	    eip, cs, eflags, errcode); 
    dump_regs( &r );
    asm("cli;hlt");
}

/* for compleatness sake */
void exc15(struct regs r, unsigned int eip, 
	   unsigned int cs, unsigned int eflags)
{
    printf( "reserved exception 15:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc16(struct regs r, unsigned int eip, 
	   unsigned int cs, unsigned int eflags)
{
    printf( "Floatting point error:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc17(struct regs r, unsigned int eip, 
	   unsigned int cs, unsigned int eflags)
{
    printf( "Alignment check exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}

void exc18(struct regs r, unsigned int eip, 
	   unsigned int cs, unsigned int eflags)
{
    printf( "Machine check exception:\n" );
    printf( "EIP: 0x%08x  CS: 0x%08x  EFLAGS: 0x%08x\n", eip, cs, eflags); 
    dump_regs( &r );
    asm("cli;hlt");
}
