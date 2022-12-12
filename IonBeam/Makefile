#OS_DEFS SOEXE,SOFLAGS,DEFS
PACKAGE=$(shell basename `pwd`)
UNAME= $(shell uname)
ifeq ($(UNAME), Linux)
SOFLAGS     = -shared
DEFS        = -DOS_LINUX
LIB_EXT    := .so
endif
ifeq ($(UNAME), Darwin)
SOFLAGS     = -dynamiclib
DEFS        = -DOS_DARWIN
LIB_EXT    := .dylib
endif
#AR           = ar
#LD_SHARED    = g++


ARFLAGS      = r
CXX	     = g++
CC           = gcc
ROOTCINT     = $(ROOTSYS)/bin/rootcint

DEFS        += -DUNIX -DLINUX -DCERNLIB_TYPE -DCERNLIB_LINUX -DCERNLIB_UNIX -DHEP_SHORT_NAMES


CXX_SOURCES  = $(wildcard src/*.cc)
CXX_DICT     = $(wildcard include/*LinkDef.h)
CXX_DICTSRC  = $(CXX_DICT:include/%LinkDef.h=src/%Dict.cxx)
CXX_OBJECTS  = $(filter-out %Dict.o,$(CXX_SOURCES:src/%.cc=tmp/%.o))
CXX_DICTOBJ  = $(CXX_DICTSRC:src/%.cxx=tmp/*.o)

CXXFLAGS     = -fPIC -Wall
CXXFLAGS    += $(shell $(ROOTSYS)/bin/root-config --cflags)
CXXFLAGS    += -g -fmessage-length=0 -fpermissive #-O2

#LIBS        += -lcaenhvwrapper -lncurses -lpthread -ldl -lm
LIBS        += -lncurses -lpthread -ldl -lm


LIBS        += $(shell $(ROOTSYS)/bin/root-config --glibs) -lEG -lGeom

INCLUDEDIR  += .  ./include
INCLUDEDIR  += $(ROOTSYS)/include

INCLUDES     = $(INCLUDEDIR:%=-I%)

COMPILE_CC  := $(CC)  -c $(DEFS) $(INCLUDES) $(CFLAGS)
COMPILE_CXX := $(CXX) -c $(DEFS) $(INCLUDES) $(CXXFLAGS)
DEPEND_CC   := $(CC) -MM $(DEFS) $(INCLUDES) $(filter-out -fPIC, $(CFLAGS))
DEPEND_CXX  := $(CC) -MM $(DEFS) $(INCLUDES) $(filter-out -fPIC, $(CXXFLAGS))
LINK_CC     := $(CC)
LINK_CXX    := $(CXX)

TARGET_SRC   = $(wildcard *.cc)
TARGET_BIN   = $(TARGET_SRC:%.cc=bin/%)

all: rootDict makelib target

target: $(TARGET_BIN)
	@ basename `pwd`
makelib: $(CXX_OBJECTS)
	@ echo $(ROOTSYS)
	@ echo $(CXX_OBJECTS)
	@[ -d ./lib ] || mkdir -p ./lib
	$(CXX) $(SOFLAGS) -o lib/lib$(PACKAGE)$(LIB_EXT) $(CXX_OBJECTS) $(CXX_DICTSRC) $(CXXFLAGS) $(INCLUDES) $(LIBS)
	@ echo "make library"
rootDict:
ifneq "$(shell ls ./include/*LinkDef.h 2>/dev/null)" ""
	@ echo making rootdicts
	@ for i in `ls ./include/*LinkDef.h | sed -n "s/\(.*\)LinkDef.h/\1.h/p"`;do \
	j=`basename $$i .h`; \
	$(ROOTCINT) -f src/$${j}Dict.cxx -c $(INCLUDES) ./include/$${j}.h ./include/$${j}LinkDef.h; \
	echo $$i ./include/$${j}LinkDef.h; \
	done;
	@ echo End making rootdicts
endif

bin/%: tmp/%.o $(CXX_OBJECTS)
	@ echo making $(@F)
	@ [ -d ./bin ] || mkdir -p ./bin
	@ echo "##########################################################"
	@ echo COMPILE $(@F)
	@ echo "##########################################################"
	$(CXX) -o $@ $^ $(filter-out -fPIC,$(CXXFLAGS)) $(CXX_DICTSRC) $(INCLUDES) $(LIBS)
	@ echo "##########################################################"

tmp/%.o: src/%.c
	@ [ -d ./tmp ] || mkdir -p ./tmp
	@ echo making $(@F) with $(<F) and $(^F)
	@ $(COMPILE_CC) -c $< $(CXXFLAGS) -o $@

tmp/%.d: src/%.c
	@ [-d ./tmp ] || mkdir -p ./tmp
	@ echo making dependencies of $(<F)
	@ $(SHELL) -ec '$(DEPEND_CXX) $< | sed -e "s/$*\.o[ :]*/tmp\/$(@F) tmp\/&/g" > $@'

tmp/%.o: src/%.cc
	@ [ -d ./tmp ] || mkdir -p ./tmp
	@ echo making $(@F) with $(<F) and $(^F)
	@ $(COMPILE_CXX) $<  $(INCLUDES) -o $@

tmp/%.d: src/%.cc
	@ [ -d ./tmp ] || mkdir -p ./tmp
	@ echo making dependencies of $(<F)
	@ $(SHELL) -ec '$(DEPEND_CXX) $< | sed -e "s/$*\.o[ :]*/tmp\/$(@F) tmp\/&/g" > $@'


tmp/%.o: %.cc
	@ echo $(INCLUDEDIR)
	@ [ -d ./tmp ] || mkdir -p ./tmp
	@ echo making $(@F)
	$(COMPILE_CXX) $< -o $@

tmp/%.d: %.cc
	@ [ -d ./tmp ] || mkdir -p ./tmp
	@ echo making dependencies of $(@F)
	@ $(SHELL) -ec '$(DEPEND_CXX) $< | sed -e "s/$*\.o[ :]*/tmp\/$(@F) tmp\/&/g" > $@'




.PHONY: clean
clean:
	rm -f $(TARGET_BIN)
	rm -rf ./lib/*
	rm -f ./tmp/*.d
	rm -f ./src/*Dict.*
	rm -f ./tmp/*.o
	rm -f $(TARGET_OBJS)
