.POSIX:

PREFIX=/usr/local
BINDIR=$(PREFIX)/bin

CFLAGS+=-Wall -Wpedantic
LDLIBS=-l fdisk

BIN=\
	acpart-write\
	acpart-read\
	acpart-size\
	acpart-offset

OBJ=\
	src/acpart-write.o\
	src/acpart-read.o\
	src/acpart-size.o\
	src/acpart-offset.o

.PHONY: all
all: $(BIN)

acpart-write: src/acpart-write.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

acpart-read: src/acpart-read.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

acpart-size: src/acpart-size.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

acpart-offset: src/acpart-offset.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

.PHONY: install
install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(BIN) $(DESTDIR)$(BINDIR)

.PHONY: clean
clean:
	rm -f $(BIN) $(OBJ)
