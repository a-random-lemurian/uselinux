CC=gcc
EXT=c
CFLAGS=-O3 -lm -Werror -Wall
LDFLAGS=-O3
SRCDIR:=src
BLDDIR:=build
INSTALLDIR=/usr/bin/
LIBS=$(OPENER_LIB)

# uselinux ####################################################################
USELINUX_EXEC=bin/uselinux
USELINUX_SRC=$(wildcard $(SRCDIR)/uselinux/*.$(EXT))
USELINUX_OBJ=$(patsubst $(SRCDIR)/uselinux/%.$(EXT),\
                        $(BLDDIR)/uselinux-%.o,\
                        $(USELINUX_SRC))

$(USELINUX_EXEC): $(USELINUX_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(BLDDIR)/uselinux-%.o: $(SRCDIR)/uselinux/%.$(EXT)
	$(CC) $(CFLAGS) -c $< -o $@

# stackov #####################################################################
STACKOV_EXEC=bin/stackov
STACKOV_SRC=$(wildcard $(SRCDIR)/stackov/*.$(EXT))
STACKOV_OBJ=$(patsubst $(SRCDIR)/stackov/%.$(EXT),\
                       $(BLDDIR)/stackov-%.o,\
                       $(STACKOV_SRC))

$(STACKOV_EXEC): $(STACKOV_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ -L./lib -lopener

$(BLDDIR)/stackov-%.o: $(SRCDIR)/stackov/%.$(EXT)
	$(CC) $(CFLAGS) -c $< -o $@

# opener ######################################################################
AR=ar
OPENER_SRC=$(SRCDIR)/opener/detect_os.c $(SRCDIR)/opener/opener.c
OPENER_OBJ=$(BLDDIR)/opener-detect_os.o $(BLDDIR)/opener-opener.o
OPENER_LIB=lib/libopener.a

$(OPENER_LIB): $(OPENER_OBJ)
	$(AR) rcs $(OPENER_LIB) $^

build/opener-%.o: $(SRCDIR)/opener/%.c
	$(CC) $(CFLAGS) -c $< -o $@
# phony rules #################################################################
.PHONY: install
EXECS=$(USELINUX_EXEC) $(STACKOV_EXEC)
install:
	@echo "make install may require sudo"
	cp $(EXECS) $(INSTALLDIR)

.PHONY: all
all: $(LIBS) $(EXECS) 

.PHONY: clean
clean:
	rm -rf opener/*.o
	rm -rf $(OBJECTS)
	rm -rf bin/uselinux
