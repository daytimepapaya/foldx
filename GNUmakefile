.POSIX:
CROSS   =
CC      = $(CROSS)gcc -std=c99
CFLAGS  = -O2 -Wall -Wformat -Wformat=2 -Wconversion -Wimplicit-fallthrough -Werror=format-security -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 -D_GLIBCXX_ASSERTIONS -fstrict-flex-arrays=3 -fstack-clash-protection -fstack-protector-strong -Wl,--as-needed -Wl,--no-copy-dt-needed-entries
LDFLAGS = 
LDLIBS  = 

foldx.exe: foldx.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ foldx.c $(LDLIBS)

all: foldx.exe

clean:
	rm -f foldx.exe
