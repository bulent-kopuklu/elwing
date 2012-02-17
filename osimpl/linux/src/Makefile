
ifeq ($(SOLUTIONDIR), )
	SOLUTIONDIR = ../../..
endif

PROJECT= elwosiml
TARGET = elwosimpl32
ifeq ($(CONFIG), debug)
	TARGET=elwosimpl32d
endif

SOURCES = MutexPolicyImpl.cpp \
	SpinLockPolicyImpl.cpp \
	ConditionPolicyImpl.cpp \
	AtomicIntegerPolicyImpl.cpp \
	ThreadPolicyImpl.cpp \
	FilePolicyImpl.cpp \
	SocketPolicyImpl.cpp \
	SharedLibraryPolicyImpl.cpp \
	Factory.cpp \
	

CCFLAGS = -I$(SOLUTIONDIR)/interface -I$(SOLUTIONDIR)/osimpl/linux/include -I$(SOLUTIONDIR)/osimpl/linux/src

all: compile lib

include $(SOLUTIONDIR)/build/compile.mk

