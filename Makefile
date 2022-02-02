CC=gcc
EXT=c
CFLAGS=-O3 -lm
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


.PHONY: all
all: $(EXEC)

.PHONY: clean
clean:
	rm -rf $(OBJECTS)
	rm -rf bin/uselinux
