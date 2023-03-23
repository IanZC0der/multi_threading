CC = gcc

CFLAGS = -g \
	 -Wall \
	 -Wshadow \
	 -Wextra \
	 -Wunreachable-code \
	 -Wredundant-decls \
	 -Wmissing-declarations \
	 -Wold-style-definition \
	 -Wmissing-prototypes \
	 -Wdeclaration-after-statement \
	 -Wno-return-local-addr \
	 -Wunsafe-loop-optimizations \
	 -Wuninitialized \
	 -pthread

all: primesMT

primesMT: primesMT.o -lm

primesMT.o: primesMT.h

tar: clean
	tar cvfa primesMT.tar.gz *.[ch] ?akefile

clean:
	rm -f primesMT *.txt.gz *.err *.log *.txt *.o *~ \#*
