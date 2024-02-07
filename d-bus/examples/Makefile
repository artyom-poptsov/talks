CFLAGS=$(shell pkg-config --cflags glib-2.0)
LIBS=$(shell pkg-config --libs glib-2.0 gio-2.0)

all: server client

server: server.c
	gcc -g -o $@ ${CFLAGS} server.c ${LIBS}

client: client.c
	gcc -g -o $@ ${CFLAGS} client.c ${LIBS}

.PHONY: clean
clean:
	rm client server
