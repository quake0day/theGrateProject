/*
 * $Id: boot.h,v 1.2 2000/09/13 08:00:17 konkers Exp $
 *
 * struct definitions of the boot image file
 */

#ifndef __boot__
#define __boot__

typedef struct {
    char be_name[32]; /* name of loaded object, zero terminated             */
    unsigned int  be_offset;   /* offset of object relative to the start of boot_dir */
    unsigned int  be_type;     /* object type designator                             */
    unsigned int  be_size;     /* size of loaded object (pages)                      */
    unsigned int  be_vsize;    /* size loaded object should occupy when mapped in    */
    unsigned int  be_extra0;
    unsigned int  be_extra1;
    unsigned int  be_extra2;
    unsigned int  be_extra3;
} boot_entry;


typedef struct {
    boot_entry bd_entry[64];
} boot_dir;

/* void _start(uint32 mem, char *params, boot_dir *bd); */

#define BE_TYPE_NONE         0  /* empty entry                              */
#define BE_TYPE_DIRECTORY    1  /* directory (entry 0)                      */
#define BE_TYPE_BOOTSTRAP    2  /* bootstrap code object (entry 1)          */
#define BE_TYPE_CODE         3  /* executable code object                   */
#define BE_TYPE_DATA         4  /* raw data object                          */
#define BE_TYPE_ELF32        5  /* 32bit ELF object                         */

/* for BE_TYPE_CODE */
#define be_code_vaddr be_extra0 /* virtual address (rel offset 0)           */
#define be_code_ventr be_extra1 /* virtual entry point (rel offset 0)       */

#endif
