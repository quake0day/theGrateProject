# $Id: Makefile,v 1.3 2000/09/13 08:04:39 konkers Exp $

include ../MDEF.$(OSTYPE)

# uncomment for assert
ASSERT = -DASSERT

CXXFLAGS =  -O2 -fno-builtins -nostdinc -DDEBUG -DSBBB ${REMDEBUG} ${ASSERT} -I. -I../libdemos -Wall
CFLAGS = ${CXXFLAGS}

OBJS=main.o ints.o

all: demos

demos: ${OBJS}
	$(LD) -o $@ ${OBJS} ${LIBGCC2} ../libdemos/libdemos.a -dN -Ttext 0x101080
	${BOOTMAKER} bootfile.desc -o bootimg

dis: demos
	$(OBJDUMP) --disassemble demos

clean:
	-rm ${OBJS} demos bootimg

.cc.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.cc.s:
	$(CXX) $(CXXFLAGS) -S -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.c.s:
	$(CC) $(CFLAGS) -S -o $@ $<

.S.o:
	$(CC) $(CFLAGS) -c -o $@ $<
