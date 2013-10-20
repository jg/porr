NLIBNAMES=linbcg.c gauss_jordan.c nrutil.c atimes.c snrm.c asolve.c dsprstx.c dsprsax.c sprsin.c
NLIBDIR=lib
NLIBPATHS=$(patsubst %,$(NLIBDIR)/%,$(NLIBNAMES))

LIBNAMES=reader.c command_line_options.c
LIBPATHS=$(LIBNAMES)

CFLAGS=-std=c99 -fopenmp

LINK=-largtable2 -lm

CHECK_PATH=check/check-0.9.10

all:
	gcc $(CFLAGS) $(NLIBPATHS) $(LIBPATHS) main.c $(LINK)

check: test/suite.c
	libtool --mode=link gcc -I$(CHECK_PATH)/src -I$(CHECK_PATH) test/suite.c  -lm -lpthread -lrt  -o test/suite $(CHECK_PATH)/src/libcheck.la && test/suite
# gcc -I$(CHECK_PATH)/src -I$(CHECK_PATH) test/suite.c $(CHECK_PATH)/src/*.o -lm -lpthread -lrt -o test/suite && test/suite
