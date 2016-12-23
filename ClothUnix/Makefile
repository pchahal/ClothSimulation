#############################################################################
#
# Makefile.SGI for CMPT461 95-1
# Written David J. Cowperthwaite 25/01/95
# Revised                        29/01/95
# 
# Either rename this file to Makefile or compile with make -f Makefile.SGI
#
# Please see the instructions below on how to modify this file for your
# own personal use.  
# There will also be available an example available in (in the next day or two)
# cowperth/ta/461/example/ex_make.tgz on the CSIL net.  The example will use 
# this Makefile (customized) to compile an example gl program.  To use it 
# copy it to one of your own directories and then uncompress it with the 
# command 
# 	gzip -d ex_make.tgz
# then unpack the archive file with 
# 	tar -xvf ex_make.tar
# then... compile the example 
# 	make all
# then you should have the executable file sgiflag in that directory.
#
#############################################################################
# operating system:     IRIX5.3
              LEX = lex
             YACC = yacc
           RANLIB = true
               RM = rm -f
      CDEBUGFLAGS = -g
        CCOPTIONS = 
    ANSICCOPTIONS =
         INCLUDES = -I/usr/local/include/X11 -I/usr/local/include -I.
   FORMS_INCLUDES = -I/usr/local2/xforms/FORMS
   EXTRA_INCLUDES = $(FORMS_INCLUDES)	
      ALLINCLUDES = $(INCLUDES) $(EXTRA_INCLUDES) 
      STD_DEFINES = 
    EXTRA_DEFINES = 
       ALLDEFINES = $(ALLINCLUDES) $(STD_DEFINES) $(EXTRA_DEFINES) 
           CFLAGS = $(ANSICCOPTIONS) $(CDEBUGFLAGS) $(CCOPTIONS) $(ALLDEFINES)
          GL_LIBS = /gfs1/CMPT/461/libaux.a -lgl -lGLU -lXirisw -lGL #-lglx 
         X11_LIBS = -lXt $(GL_LIBS) -lX11
       MOTIF_LIBS = -lMrm -lXm
       FORMS_LIBS = -L/usr/local2/xforms/FORMS -lforms
        FONT_LIBS = -lfm
 EXTRA_LOAD_FLAGS = 
  EXTRA_LIBRARIES = 
           LDLIBS = $(MOTIF_LIBS) $(X11_LIBS) -lm -lc -lPW $(FORMS_LIBS) $(FONT_LIBS) $(EXTRA_LIBRARIES) -s -L/usr/lib $(EXTRA_LOAD_FLAGS)
        LDOPTIONS = $(ANSICCOPTIONS) $(CDEBUGFLAGS) $(CCOPTIONS) $(LOCAL_LDFLAGS) -L$(USRLIBDIR)
           RM_CMD = $(RM) *.CKP *.ln *.BAK *.bak *.o core errs ,* *~ *.a .emacs_* tags TAGS make.log MakeOut
            UIL = uil
##############################################################################
#
# This is the only section you should have to modify much for now, later 
# as you write more code you may have more libraries you need to link in
# EXTRA_LIBRARIES, more defines to list in EXTRA_DEFINES, or include 
# directories to add to EXTRA_INCLUDES
#
# For now I haven't found a good solution to getting the SGI make to recognize
# a rule for compiling .cc (C++) files similar to the .c.o file for 
# compilation of .c files to .o.  
# The best interim solution I can offer is to replace the standard .cc 
# extension used to denote a C++ source file with the .c extension and then
# comment out the line CC = cc (the std C compiler) and then uncomment the 
# line CC = CC (the SGI C++ compiler).
#
##############################################################################

#
# uncomment only one, depending on whether your code is in 
# C or C++ 
#
               CC = cc  # for std C
#               CC = CC  # for C++

#
# replace with CMD = <final exetuable name(s)>
#
CMD = cloth

#
# replace with all:: 
#
all:: $(CMD)

#
# for example
#
# all:: clothhow  

#
# replace with SRCS = <space separated list of all .c files to be compiled>
#
SRCS = cloth.c 

#
# replace with OBJS = <space separated list of all .o files, same as .c list>
#
OBJS = cloth.o

#
# this is the make rule for compiling .c files to .o assembled files, ready
# for linking by ld
#
.c.o:
	$(RM) $@
	$(CC) -c $(CFLAGS) $*.c

$(CMD): $(OBJS)
	$(RM) $@
	$(CC) -o $@ $(OBJS) $(LDOPTIONS) $(DEPS) $(LOCAL_LIBRARIES) $(LDLIBS) 

clean::
	$(RM) $(CMD) $(OBJS)

##############################################################################
#
#	If you are using Motif and .uil files to construct an interface, 
#  	rather than forms, then put them here.  
#
##############################################################################

#
# replace with UIDS = <list the uid files to be compiled>
#

#UIDS = 

#all:: $(UIDS)
# all:: curve.uid

#
# uncomment the following section and make a copy of it for each of
# the <file>.uid entries in the "UIDS =" list.
#

#<file>.uid: <file>.uil
#	$(RM) $@
#	$(UIL) -o $@ <file>.uil
#clean::
#	$(RM) <file>.uid

#
# for example
#curve.uid: curve.uil
#	$(RM) $@
#	$(UIL) -o $@ curve.uil
#clean::
#	$(RM) curve.uid
