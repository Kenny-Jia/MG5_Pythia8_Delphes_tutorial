# Makefile is a part of the PYTHIA event generator.
# Copyright (C) 2024 Torbjorn Sjostrand.
# PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
# Please respect the MCnet Guidelines, see GUIDELINES for details.
# Author: Philip Ilten, September 2014.
#
# This is is the Makefile used to build PYTHIA examples on POSIX systems.
# Example usage is:
#     make main01
# For help using the make command please consult the local system documentation,
# i.e. "man make" or "make --help".

################################################################################
# VARIABLES: Definition of the relevant variables from the configuration script.
################################################################################

# Set the shell.
SHELL=/usr/bin/env bash

# Include the configuration.
-include $(PYTHIA_BASE_DIR)/share/Pythia8/examples/Makefile.inc

# hardcode pythia include path
PREFIX_LIB=$(PYTHIA_BASE_DIR)/lib
PREFIX_INCLUDE=$(PYTHIA_BASE_DIR)/include

CXX_COMMON:=$(OBJ_COMMON) -I$(PREFIX_INCLUDE) $(CXX_COMMON) $(GZIP_LIB)
CXX_COMMON+= -L$(PREFIX_LIB) -Wl,-rpath,$(PREFIX_LIB) -lpythia8 -ldl
PYTHIA=$(PREFIX_LIB)/libpythia8$(LIB_SUFFIX)

# Fix missing runtime paths from RIVET and determine C++ standard used.
ifeq ($(RIVET_USE),true)
  COMMA=,
  RIVET_LPATH=$(filter -L%,$(shell $(RIVET_BIN)$(RIVET_CONFIG) --ldflags))
  RIVET_RPATH=$(subst -L,-Wl$(COMMA)-rpath$(COMMA),$(RIVET_LPATH))
  RIVET_FLAGS=-DRIVET
  RIVET_VERSION=$(shell $(RIVET_BIN)$(RIVET_CONFIG) --version)
  RIVET_CSTD=c++14
  ifeq ("4.0.0","$(word 1, $(sort 4.0.0 $(RIVET_VERSION)))")
    RIVET_CSTD=c++17
  endif
  DTAGS=$(shell echo "int main(){}" | $(CXX) -Wl,--disable-new-dtags -o \
     /dev/null -xc - 2>&1)
  ifeq ($(DTAGS),)
    RIVET_FLAGS+= -Wl,--disable-new-dtags
  endif
endif

################################################################################
# RULES: Definition of the rules used to build the PYTHIA examples.
################################################################################

# Rules without physical targets (secondary expansion for specific rules).
.SECONDEXPANSION:
.PHONY: all clean

# All targets (no default behavior).
all:
	$(info Usage: make mainXX)

info-pythia:
	$(info PREFIX_LIB is: $(PREFIX_LIB))
	$(info PYTHIA is: $(PYTHIA))

# PYTHIA library.
$(PYTHIA):
	$(error Error: PYTHIA must be built, please run "make"\
                in the top PYTHIA directory)

generatePUHemc: $(PYTHIA) $$@.cc
ifeq ($(HEPMC3_USE),true)
	$(CXX) $@.cc -o $@ $(CXX_COMMON) $(HEPMC3_INCLUDE) $(HEPMC3_LIB)\
	 -DHEPMC3
else ifeq ($(HEPMC2_USE),true)
	$(CXX) $@.cc -o $@ $(CXX_COMMON) $(HEPMC2_INCLUDE) $(HEPMC2_LIB)\
	 -DHEPMC2
else
	$(error Error: $@ requires HEPMC2 or HEPMC3)
endif

# # Clean.
# clean:
# 	@rm -f main[0-9][0-9]; rm -f out[0-9][0-9];\
# 	rm -f main[0-9][0-9][0-9]; rm -f out[0-9][0-9][0-9];\
# 	rm -f mymain[0-9][0-9]; rm -f myout[0-9][0-9];\
# 	rm -f test[0-9][0-9][0-9]; rm -f *.dat;\
# 	rm -f weakbosons.lhe; rm -f hist.root;\
# 	rm -f *~; rm -f \#*; rm -f core*; rm -f *Dct.*; rm -f *.so;\
# 	rm -f *.log; rm -f *plot.py; rm -f *.pcm; rm -f *.mpi;\
# 	rm -f *.hepmc; rm -f *.yoda; rm -f *.root;
