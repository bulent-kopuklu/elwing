
ifeq ($(SOLUTIONDIR), )
	SOLUTIONDIR = ../../..
endif

PROJECT=test-case

TARGET = testcase32
ifeq ($(CONFIG), debug)
	TARGET=testcase32d
endif


SOURCES = testcase.cpp \
    tests/Sleep001.cpp \
    tests/Thread001.cpp \
    tests/Runnable001.cpp \
    tests/AtomicInteger001.cpp \
    tests/AtomicCounter001.cpp \
    tests/SmartPointer001.cpp \
    tests/SmartPointer002.cpp \
    tests/SmartPointer003.cpp \
    tests/MemoryStream001.cpp \
	tests/MemoryStream002.cpp \
	tests/MemoryStream003.cpp \
    tests/ThreadQueue001.cpp \
    tests/ThreadQueue002.cpp \
    tests/ThreadQueue003.cpp \
    tests/ThreadQueue004.cpp \
    tests/ThreadPool001.cpp \
    tests/File001.cpp \
    tests/File002.cpp \
    tests/File003.cpp \
    tests/File004.cpp \
    tests/File005.cpp \
    tests/File006.cpp \
    tests/InetAddress001.cpp \
    tests/TCPSocket001.cpp \
    tests/URI001.cpp \
	

CCFLAGS = -I$(SOLUTIONDIR)/include -I$(SOLUTIONDIR)/interface -I$(SOLUTIONDIR)/test/testcase/include -I$(SOLUTIONDIR)/test/testcase/src

all: compile lib 

include $(SOLUTIONDIR)/build/compile.mk
