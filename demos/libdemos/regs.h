/*
 * $Id: regs.h,v 1.2 2000/09/13 08:00:17 konkers Exp $
 *
 * regs structure from pusha instruction
 */

#ifndef __lib_regs_h__
#define __lib_regs_h__

struct regs {
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
};

#endif
