.DEFAULT_GOAL := all

CC=gcc
EXT=c
CFLAGS=-O3 -Werror -Wall -I./src/common
LDFLAGS=-O3 -lm
SRCDIR:=src
BLDDIR:=build
INSTALLDIR=/usr/bin/
LIBS=$(OPENER_LIB) $(COMMON_LIB) $(PENGUINSPAM_LIB)


ifndef V
	QUIET_CC  =@echo '    ' CC '    ' $(<F);
	QUIET_AR  =@echo '    ' AR '    ' $(@F);
	QUIET_LINK=@echo '    ' LINK '  ' $(@F);
endif

# uselinux ####################################################################
USELINUX_EXEC=bin/uselinux
USELINUX_SRC=$(wildcard $(SRCDIR)/uselinux/*.$(EXT))
USELINUX_OBJ=$(patsubst $(SRCDIR)/uselinux/%.$(EXT),\
                        $(BLDDIR)/uselinux-%.o,\
                        $(USELINUX_SRC))

$(USELINUX_EXEC): $(USELINUX_OBJ)
	$(QUIET_LINK)$(CC) $(LDFLAGS) $^ -o $@ -L./lib -lcommon

$(BLDDIR)/uselinux-%.o: $(SRCDIR)/uselinux/%.$(EXT)
	$(QUIET_CC)$(CC) $(CFLAGS) -c $< -o $@

# stackov #####################################################################
STACKOV_EXEC=bin/stackov
STACKOV_SRC=$(wildcard $(SRCDIR)/stackov/*.$(EXT))
STACKOV_OBJ=$(patsubst $(SRCDIR)/stackov/%.$(EXT),\
                       $(BLDDIR)/stackov-%.o,\
                       $(STACKOV_SRC))

$(STACKOV_EXEC): $(STACKOV_OBJ)
	$(QUIET_LINK)$(CC) $(LDFLAGS) $^ -o $@ -L./lib -lopener

$(BLDDIR)/stackov-%.o: $(SRCDIR)/stackov/%.$(EXT)
	$(QUIET_CC)$(CC) $(CFLAGS) -c $< -o $@

# opener ######################################################################
AR=ar
OPENER_SRC=$(SRCDIR)/opener/detect_os.c $(SRCDIR)/opener/opener.c
OPENER_OBJ=$(BLDDIR)/opener-detect_os.o $(BLDDIR)/opener-opener.o
OPENER_LIB=lib/libopener.a

$(OPENER_LIB): $(OPENER_OBJ)
	$(QUIET_AR)$(AR) rcs $(OPENER_LIB) $^

build/opener-%.o: $(SRCDIR)/opener/%.c
	$(QUIET_CC)$(CC) $(CFLAGS) -c $< -o $@

# common ######################################################################
COMMON_SRC=$(SRCDIR)/common/mtwister.c $(SRCDIR)/common/utils.c
COMMON_OBJ=$(BLDDIR)/common-mtwister.o $(BLDDIR)/common-utils.o
COMMON_LIB=lib/libcommon.a

$(COMMON_LIB): $(COMMON_OBJ)
	$(QUIET_AR)$(AR) rcs $(COMMON_LIB) $^

build/common-%.o: $(SRCDIR)/common/%.c
	$(QUIET_CC)$(CC) $(CFLAGS) -c $< -o $@

# penguinspam (lib) ###########################################################
PENGUINSPAM_SRC=$(SRCDIR)/penguinspam/penguinspam.c
PENGUINSPAM_OBJ=$(BLDDIR)/penguinspam-penguinspam.o
PENGUINSPAM_LIB=lib/libpenguinspam.a

$(PENGUINSPAM_LIB): $(PENGUINSPAM_OBJ)
	$(QUIET_AR)$(AR) rcs $(PENGUINSPAM_LIB) $^

build/penguinspam-%.o: $(SRCDIR)/penguinspam/%.c
	$(QUIET_CC)$(CC) $(CFLAGS) -c $< -o $@

# penguinspamcli #############################################################
PENGUINSPAMCLI_SRC=$(SRCDIR)/penguinspam/penguinspamcli.c
PENGUINSPAMCLI_OBJ=$(BLDDIR)/penguinspam-penguinspamcli.o
PENGUINSPAMCLI_EXEC=bin/penguinspammer

$(PENGUINSPAMCLI_EXEC): $(PENGUINSPAMCLI_OBJ)
	$(QUIET_LINK)$(CC) $(LDFLAGS) $^ -o $@ -L./lib -lcommon -lpenguinspam

$(BLDDIR)/penguinspam-%.o: $(SRCDIR)/penguinspam/%.$(EXT)
	$(QUIET_CC)$(CC) $(CFLAGS) -c $< -o $@
# phony rules #################################################################
.PHONY: install
EXECS=$(USELINUX_EXEC) $(STACKOV_EXEC) $(PENGUINSPAMCLI_EXEC)
install:
	@echo "make install may require sudo"
	cp $(EXECS) $(INSTALLDIR)

.PHONY: all

$(EXECS): $(LIBS)

all: $(LIBS) $(EXECS)

.PHONY: clean
clean:
	rm lib/*.a
	rm build/*.o
	rm bin/uselinux
