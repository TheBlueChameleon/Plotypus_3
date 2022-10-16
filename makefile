# ============================================================================ #
# user variables setup.
# feel free to adjust to your requirements

# ---------------------------------------------------------------------------- #
# Compiler setup

CXX      = g++
CXXFLAGS = -std=c++20 -O3 -Wextra -Wall -Wpedantic -Wimplicit-fallthrough -I$(LIBDIR) -fPIC
LDFLAGS  = -lm -lstdc++fs

LIBDIR = lib
SRCDIR = src
INCDIR = src
OBJDIR = obj
EXEDIR = bin
SHOWCASEDIR = unittest

# ---------------------------------------------------------------------------- #
# Project Data setup

EXTENSION_CODE   = .cpp
EXTENSION_HEADER = .h
EXTENSION_OBJECT = .o

EXENAME = Plotypus-Showcase
LIBNAME = plotypus

# ============================================================================ #
# Path Setup. Be sure that you really understand what you're doing if you edit anything below this line

DIRECTORIES = $(subst $(SRCDIR),$(OBJDIR),$(shell find $(SRCDIR) -type d))
	# paths for files to be included into the compile/link procedure.
	# subst: "substitute PARAMETER_1 by PARAMETER_2 in PARAMETER_3.
	# shell find -type d lists only directories. find works recursively.
	# => load from SRCDIR and OBJDIR with all subdirectories

SRC     = $(wildcard $(SRCDIR)/*$(EXTENSION_CODE)) $(wildcard $(SRCDIR)/**/*$(EXTENSION_CODE))
	# list of all files in src, including subdirectories
INC     = $(wildcard $(INCDIR)/*$(EXTENSION_HEADER)) $(wildcard $(INCDIR)/**/*$(EXTENSION_HEADER))
	# same for includes
OBJ     = $(SRC:$(SRCDIR)/%$(EXTENSION_CODE)=$(OBJDIR)/%$(EXTENSION_OBJECT))
	# defines analogy relation (object file is source file with replaced extension)

OBJ_SHOWCASE = $(wildcard $(OBJDIR)/$(SHOWCASEDIR)/*$(EXTENSION_OBJECT)) $(wildcard $(OBJDIR)/$(SHOWCASEDIR)/**/*$(EXTENSION_OBJECT))
OBJ_LIB      = $(filter-out $(OBJ_SHOWCASE), $(OBJ))

LIBNAME_STATIC = $(EXEDIR)/lib$(LIBNAME).a
LIBNAME_SHARED = $(EXEDIR)/lib$(LIBNAME).so

EXENAME_FULL = $(EXEDIR)/$(EXENAME)

# ---------------------------------------------------------------------------- #
# Colour constants

COLOR_END	= \033[m

COLOR_RED	= \033[0;31m
COLOR_GREEN	= \033[0;32m
COLOR_YELLOW	= \033[0;33m
COLOR_BLUE	= \033[0;34m
COLOR_PURPLE	= \033[0;35m
COLOR_CYAN	= \033[0;36m
COLOR_GREY	= \033[0;37m

COLOR_LRED	= \033[1;31m
COLOR_LGREEN	= \033[1;32m
COLOR_LYELLOW	= \033[1;33m
COLOR_LBLUE	= \033[1;34m
COLOR_LPURPLE	= \033[1;35m
COLOR_LCYAN	= \033[1;36m
COLOR_LGREY	= \033[1;37m

MSG_OK		= $(COLOR_LGREEN)[SUCCES]$(COLOR_END)
MSG_WARNING	= $(COLOR_LYELLOW)[WARNING]$(COLOR_END)
MSG_ERROR	= $(COLOR_LRED)[ERROR]$(COLOR_END)

# ============================================================================ #
# procs

define fatboxtop
	@printf "$(COLOR_BLUE)"
	@printf "#=============================================================================#\n"
	@printf "$(COLOR_END)"
endef
# ............................................................................ #
define fatboxbottom
	@printf "$(COLOR_BLUE)"
	@printf "#=============================================================================#\n"
	@printf "$(COLOR_END)"
endef
# ............................................................................ #
define fatboxtext
	@printf "$(COLOR_BLUE)"
	@printf "# "
	@printf "$(COLOR_LGREY)"
	@printf "%-75b %s" $(1)
	@printf "$(COLOR_BLUE)"
	@printf "#\n"
	@printf "$(COLOR_END)"

endef
# ---------------------------------------------------------------------------- #
define boxtop
	@printf "$(COLOR_BLUE)"
	@printf "+-----------------------------------------------------------------------------+\n"
	@printf "$(COLOR_END)"
endef
# ............................................................................ #
define boxbottom
	@printf "$(COLOR_BLUE)"
	@printf "+-----------------------------------------------------------------------------+\n"
	@printf "$(COLOR_END)"
endef
# ............................................................................ #
define boxtext
	@printf "$(COLOR_BLUE)"
	@printf "| "
	@printf "$(COLOR_LGREY)"
	@printf "%-75b %s" $(1)
	@printf "$(COLOR_BLUE)"
	@printf "|\n"
	@printf "$(COLOR_END)"
endef
# ---------------------------------------------------------------------------- #
define fatbox
	$(call fatboxtop)
	$(call fatboxtext, $(1))
	$(call fatboxbottom)
endef
# ............................................................................ #
define box
	$(call boxtop)
	$(call boxtext, $(1))
	$(call boxbottom)
endef

# ============================================================================ #
# targets

.PHONY: intro

# ---------------------------------------------------------------------------- #
# default target

help:
	$(call fatbox, "PLOTYPUS MAKEFILE")
	@echo
	@echo "Please type one of the following:"
	@echo "$(COLOR_YELLOW)Executable generation $(COLOR_END)"
	@echo "    $(COLOR_LCYAN)make all$(COLOR_END)"
	@echo "      compiles, links the static and dynamic library and creates the showcase executable"
	@echo "    $(COLOR_LCYAN)make static$(COLOR_END)"
	@echo "      compiles, links the static library only and creates the showcase executable"
	@echo "    $(COLOR_LCYAN)make shared$(COLOR_END)"
	@echo "      compiles, links the shared library only and creates the showcase executable"
	@echo "    $(COLOR_LCYAN)make new$(COLOR_END)"
	@echo "      same as $(COLOR_LCYAN)make all$(COLOR_END), but invokes $(COLOR_LCYAN)make clean$(COLOR_END) beforehand"
	@echo "    $(COLOR_LCYAN)make run$(COLOR_END)"
	@echo "      same as $(COLOR_LCYAN)make all$(COLOR_END), but also executes the generated showcase file after linking"
	@echo "    $(COLOR_LCYAN)make grind$(COLOR_END)"
	@echo "      same as $(COLOR_LCYAN)make all$(COLOR_END), but also executes the generated showcase file with $(COLOR_LCYAN)valgrind$(COLOR_END) after linking"
	@echo
	@echo "$(COLOR_YELLOW)Specific output selection$(COLOR_END)"
	@echo "    $(COLOR_LCYAN)make compile$(COLOR_END)"
	@echo "      compiles all source code files to object files"
	@echo "    $(COLOR_LCYAN)make linklib_static$(COLOR_END)"
	@echo "      links all library object files to a static library. $(COLOR_LCYAN)make compile$(COLOR_END) must have been invoked before."
	@echo "    $(COLOR_LCYAN)make linklib_shared$(COLOR_END)"
	@echo "      links all library object files to a shared library. $(COLOR_LCYAN)make compile$(COLOR_END) must have been invoked before."
	@echo "    $(COLOR_LCYAN)make linkshowcase_default$(COLOR_END)"
	@echo "      links the showcase object files and the library to an executable."
	@echo "      uses the shared library if present, otherwise defaults to the static library."
	@echo "    $(COLOR_LCYAN)make linkshowcase_static$(COLOR_END)"
	@echo "      same as $(COLOR_LCYAN)make linkshowcase_default$(COLOR_END), but always links against the static library version"
	@echo
	@echo "$(COLOR_YELLOW)Misc$(COLOR_END)"
	@echo "    $(COLOR_LCYAN)make clean$(COLOR_END)"
	@echo "      removes $(OBJDIR) and its contents."
	@echo "    $(COLOR_LCYAN)make vars$(COLOR_END)"
	@echo "      show variables generated and set by this script"
	@echo "    $(COLOR_LCYAN)make help$(COLOR_END)"
	@echo "      show this help"
	@echo
	@echo "Note that you can create compound targets such as:"
	@echo "   $(COLOR_LCYAN)make clean run$(COLOR_END)"

# ---------------------------------------------------------------------------- #
# compound targets

all:            intro binaries extro
new:      clean intro binaries extro
run:            intro binaries extro execute
grind:          intro binaries extro valgrind
binaries: compile linklib_static linklib_shared linkshowcase_default
static:   compile linklib_static                linkshowcase_static
shared:   compile                linklib_shared linkshowcase_shared

# ---------------------------------------------------------------------------- #
# visual feedback

intro:
	@clear
	$(call fatbox, "attempting to make")
	@printf "$(COLOR_GREY)  "
	@date
	@echo ""

# ............................................................................ #
extro:
	$(call fatbox, "make done")
	@printf "$(COLOR_GREY)  "
	@date
	@echo ""


# ---------------------------------------------------------------------------- #
# compile

compile: $(OBJ)
# ............................................................................ #
$(OBJDIR)/%$(EXTENSION_OBJECT): $(SRCDIR)/%$(EXTENSION_CODE)
	$(call boxtop)
	$(call boxtext, "attempting to compile...")

	@mkdir -p $(DIRECTORIES)

	@printf "$(COLOR_BLUE)"
	@printf "| "
	@printf "$(COLOR_LBLUE)"
	@printf "%-85b %s" "  Compiling:  $(COLOR_LYELLOW)$<$(COLOR_END)"
	@printf "$(COLOR_BLUE)|\n"

	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(INCDIR) \
		|| (echo "$(MSG_ERROR)"; exit 1)

	$(call boxtext, "done.")
	$(call boxbottom)

# ---------------------------------------------------------------------------- #
# link libs

linklib_static: $(LIBNAME_STATIC)
linklib_shared: $(LIBNAME_SHARED)
# ............................................................................ #
$(LIBNAME_STATIC):
	$(call boxtop)
	$(call boxtext, "attempting to create static lib...")

	@mkdir -p $(EXEDIR)
	@ar rcs $@ $(OBJ_LIB)

	$(call boxtext, "done.")
	$(call boxbottom)
# ............................................................................ #
$(LIBNAME_SHARED):
	$(call boxtop)
	$(call boxtext, "attempting to create shared lib...")

	@mkdir -p $(EXEDIR)
	@$(CXX) -shared $(OBJ_LIB) -o $@

	$(call boxtext, "done.")
	$(call boxbottom)

# ---------------------------------------------------------------------------- #
# link executable

linkshowcase_default:
	$(call boxtop)
	$(call boxtext, "attempting to link showcase binary...")

	$(eval LDFLAGS += "-l$(LIBNAME)")
	$(eval LDFLAGS += "-L$(EXEDIR)")
	$(call linkBinary)

	$(call boxtext, "done.")
	$(call boxbottom)

linkshowcase_static:
	$(call boxtop)
	$(call boxtext, "attempting to link showcase binary with static library...")

	$(eval LDFLAGS += "$(LIBNAME_STATIC)")
	$(call linkBinary)

	$(call boxtext, "done.")
	$(call boxbottom)

linkshowcase_shared:
	$(call boxtop)
	$(call boxtext, "attempting to link showcase binary with shared library...")

	$(eval LDFLAGS += "$(abspath $(LIBNAME_SHARED))")
	$(call linkBinary)

	$(call boxtext, "done.")
	$(call boxbottom)
# ............................................................................ #
define linkBinary
	@mkdir -p $(EXEDIR)
	@$(CXX) $(OBJ_SHOWCASE) $(LDFLAGS) -o $(EXENAME_FULL)  \
		|| (echo "$(MSG_ERROR)"; exit 1)

	$(call boxtext, "successfully created executable in $(EXENAME_FULL)")
endef

# ---------------------------------------------------------------------------- #
# execute

execute:
	$(call fatbox, "Executing showcase code")
	$(call boxtop)
	$(call boxtext, "launching $(EXENAME_FULL) ...")

	@cd $(EXEDIR); ./$(EXENAME)

	$(call boxtext, "done!")
	$(call boxbottom)
valgrind:
	$(call fatbox, "Executing showcase code with valgrind analysis")
	$(call boxtop)
	$(call boxtext, "launching $(EXENAME_FULL) ...")

	@cd $(EXEDIR); valgrind ./$(EXENAME)

	$(call boxtext, "done!")
	$(call boxbottom)
# ---------------------------------------------------------------------------- #
# delete the object directory

clean:
	@printf "$(COLOR_LCYAN)"
	@echo "#=============================================================================#"
	@echo "# attempting to clean...                                                      #"

	@rm -rf $(OBJDIR)
	@rm -f $(EXEDIR)/$(EXENAME)

	@echo "# done.                                                                       #"
	@echo "#=============================================================================#"
	@echo ""

# ---------------------------------------------------------------------------- #
# help section

vars:
	@clear
	$(call fatbox, "variables dump:")

	@echo "source code extension    : $(EXTENSION_CODE)"
	@echo "header files extension   : $(EXTENSION_HEADER)"
	@echo ""

	@echo "executable file name     : $(EXENAME)"
	@echo ""
	@echo "source code  directory   : $(SRCDIR)"
	@echo "include file directory   : $(INCDIR)"
	@echo "object file  directory   : $(OBJDIR)"
	@echo "binaries     directory   : $(EXEDIR)"
	@echo ""

	@echo "object file directories  :"
	@echo "   $(DIRECTORIES)"
	@echo "source code files        :"
	@echo "   $(SRC)"
	@echo "header files             :"
	@echo "   $(INC)"
	@echo "object code files        :"
	@echo "   $(OBJ)"
	@echo "showcase objects         :"
	@echo "   $(OBJ_SHOWCASE)"
	@echo "library objects          :"
	@echo "   $(OBJ_LIB)"
	@echo ""

	$(call fatbox, "done.")
