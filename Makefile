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


stackov: opener/opener.c opener/detect_os.c stackov_src/stackov.c
	$(CC) $(CFLAGS) $^ -o $@ -I.



INSTALLDIR=/usr/bin/
.PHONY: install
install: $(EXEC)
	cp $(EXEC) $(INSTALLDIR)

.PHONY: all
all: $(EXEC) stackov

.PHONY: clean
clean:
	rm -rf opener/*.o
	rm -rf $(OBJECTS)
	rm -rf bin/uselinux
