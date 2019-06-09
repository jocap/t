CFLAGS = -O2
CFLAGS += -Wall -Wno-missing-braces -Wextra -Wpedantic

all: t README.md

install:
	cp -p t /usr/local/bin
	cp -p t.1 /usr/local/man/man1

uninstall: 
	rm /usr/local/bin/t
	rm /usr/local/man/man1/t.1

README.md: t.1
	mandoc -T markdown t.1 | sed s/^#/###/ > README.md
