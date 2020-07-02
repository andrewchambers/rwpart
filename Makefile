.POSIX:

PREFIX=/usr/local
BINDIR=$(PREFIX)/bin

CFLAGS+=-Wall -Wpedantic
LDFLAGS=
LDLIBS=-l fdisk

BIN=\
	rwpart-write\
	rwpart-read\
	rwpart-size\
	rwpart-offset

OBJ=\
	src/rwpart-write.o\
	src/rwpart-read.o\
	src/rwpart-size.o\
	src/rwpart-offset.o

.PHONY: all
all: $(BIN)

rwpart-write: src/rwpart-write.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

rwpart-read: src/rwpart-read.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

rwpart-size: src/rwpart-size.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

rwpart-offset: src/rwpart-offset.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

.PHONY: install
install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(BIN) $(DESTDIR)$(BINDIR)

.PHONY: clean
clean:
	rm -f $(BIN) $(OBJ)
