
ifeq ($(SOLUTIONDIR), )
	SOLUTIONDIR = ../../..
endif

PROJECT = test-eng
TARGET = testeng32

LDFLAGS = -L$(OUTPUTDIR) -lelwing32  -ltestcase32 -s
ifeq ($(CONFIG), debug)
	TARGET = testeng32d
	LDFLAGS = -L$(OUTPUTDIR) -lelwing32d  -ltestcase32d
endif
 

SOURCES = main.cpp \
	TestEngine.cpp
	

CCFLAGS = -I$(SOLUTIONDIR)/include -I$(SOLUTIONDIR)/interface -I$(SOLUTIONDIR)/test/testcase/include


all: compile exe

include $(SOLUTIONDIR)/build/compile.mk
