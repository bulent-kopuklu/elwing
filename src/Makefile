
ifeq ($(SOLUTIONDIR), )
	SOLUTIONDIR = ..
endif

PROJECT=elwing

ELWOSIMPL=$(OUTPUTDIR)/libelwosimpl32d.a
ifeq ($(CONFIG), release)
	ELWOSIMPL=$(OUTPUTDIR)/libelwosimpl32.a
endif

TARGET = elwing32d
ifeq ($(CONFIG), release)
	TARGET = elwing32
	LDFLAGS = -s
endif
#	io/InputChannel.cpp
#	io/OutputChannel.cpp
# stdafx.cpp \

SOURCES = thread/Mutex.cpp \
	thread/SpinLock.cpp \
	thread/Condition.cpp \
	thread/AtomicInteger.cpp \
	thread/Event.cpp \
	thread/Thread.cpp \
	lang/ClassFactory.cpp\
	io/File.cpp \
	io/FileInputChannel.cpp \
	io/FileOutputChannel.cpp \
	io/InputStream.cpp \
	io/OutputStream.cpp \
	io/MemoryInputStream.cpp \
	io/MemoryOutputStream.cpp \
	net/Inet4Address.cpp \
	net/Inet6Address.cpp \
	net/InetAddress.cpp \
	net/InetSocketAddress.cpp \
	net/Socket.cpp \
	net/ServerSocket.cpp \
	net/SocketInputChannel.cpp \
	net/SocketOutputChannel.cpp \
	net/URI.cpp \
	system/SharedLibrary.cpp

CCFLAGS = -I$(SOLUTIONDIR)/include -I$(SOLUTIONDIR)/interface -I$(SOLUTIONDIR)/src
LDFLAGS += -Wl,--whole-archive $(ELWOSIMPL) -Wl,--no-whole-archive
ifeq ($(CONFIG), release)
	LDFLAGS+=-s
endif

all: compile dll

install:
	

include $(SOLUTIONDIR)/build/compile.mk
