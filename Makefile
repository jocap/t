CFLAGS = -O2
CFLAGS += -Wall -Wno-missing-braces -Wextra -Wpedantic

all: t

install:
	cp -p t /usr/local/bin
	cp -p t.1 /usr/local/man/man1

uninstall: 
	rm /usr/local/bin/t
	rm /usr/local/man/man1/t.1
