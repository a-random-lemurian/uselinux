CC=gcc
EXT=c
CFLAGS=-O3 -lm -Werror -Wall
LDFLAGS=-O3
SRCDIR:=src
BLDDIR:=build
SOURCES=$(wildcard $(SRCDIR)/*.$(EXT))
OBJECTS=$(patsubst $(SRCDIR)/%.$(EXT), $(BLDDIR)/%.o, $(SOURCES))
EXEC=bin/uselinux


$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@


$(BLDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<


STACKOV_SOURCES=$(wildcard opener/*.c)
STACKOV_OBJECTS=$(patsubst opener/%.c, $(BLDDIR)/%.o, $(STACKOV_SOURCES))

build/stackov.o: stackov_src/stackov.c
	$(CC) $(CFLAGS) -o $@ -c $< -I.

$(BLDDIR)/%.o: opener/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

bin/stackov: $(STACKOV_OBJECTS) build/stackov.o
	$(CC) $(LDFLAGS) $^ -o $@


INSTALLDIR=/usr/bin/
.PHONY: install
install: $(EXEC)
	cp $(EXEC) $(INSTALLDIR)

.PHONY: all
all: $(EXEC) bin/stackov

.PHONY: clean
clean:
	rm -rf opener/*.o
	rm -rf $(OBJECTS)
	rm -rf bin/uselinux
