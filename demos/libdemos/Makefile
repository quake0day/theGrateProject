include ../MDEF

# uncomment for assert
ASSERT = -DASSERT

CXXFLAGS =  -O2 -g -nostdinc -fno-builtin -DDEBUG -DSBBB ${REMDEBUG} ${ASSERT} -I. -Wall -W -DASM_OPT
CFLAGS = ${CXXFLAGS}

OBJS=printf.o ctype.o string.o interrupt.o assert.o

all: libdemos

libdemos: ${OBJS}
	${AR} r libdemos.a ${OBJS}

clean:
	-rm ${OBJS} libdemos.a

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
