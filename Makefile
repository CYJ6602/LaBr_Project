########################################################################
#
##              --- CAEN SpA - Computing Division ---
#
##   CAENDigitizer Software Project
#
##   Created  :  October    2009      (Rel. 1.0)
#
##   Auth: A. Lucchesi
#
#########################################################################
ARCH	=	`uname -m`

# OUTDIR  =    	./bin/$(ARCH)/Release/
OUTNAME =    	V1730_DPP_PSD
# OUT     =    	$(OUTDIR)/$(OUTNAME)
OUT     =    	$(OUTNAME)

CC	=	g++

CXXOPTS	=	-fPIC -DLINUX -O2  

ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS   := $(shell root-config --libs)
ROOTGLIBS   := $(shell root-config --glibs)
ROOTINC := -I$(shell root-config --incdir)

#FLAGS	=	-soname -s
#FLAGS	=       -Wall,-soname -s
#FLAGS	=	-Wall,-soname -nostartfiles -s
#FLAGS	=	-Wall,-soname

DEPLIBS	=	-lCAENDigitizer -lCAENVME

LIBS	=	-L..	-lc -lm -lstdc++ $(ROOTLIBS) $(ROOTGLIBS)

INCLUDEDIR =	-I./include		-I/usr/include/ $(ROOTINC)

OBJS	=	src/V1730_DPP_PSD.o src/keyb.o src/Functions.o 

INCLUDES =	./include/*

#########################################################################

all	:	$(OUT)

clean	:
		/bin/rm -f $(OBJS) $(OUT)

$(OUT)	:	$(OBJS)
		/bin/rm -f $(OUT)
########if [ ! -d $(OUTDIR) ]; then mkdir -p $(OUTDIR); fi
		$(CC) $(CXXOPTS) $(ROOTCFLAGS) -o $(OUT) $(OBJS) $(DEPLIBS) $(LIBS)

# $(OBJS)	:	$(INCLUDES) $(INCLUDEDIR) Makefile

%.o	:	%.cpp
		$(CC) $(CXXOPTS) $(ROOTCFLAGS) $(INCLUDEDIR) -c -o $@ $<

