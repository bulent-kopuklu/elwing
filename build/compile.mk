#
#  compile.mk
#
#  Created on: Sep 27, 2011
#      Author: Bulent.Kopuklu
#
#  Copyright (C) 2010 by Bulent Kopuklu (bulent.kopuklu@gmail.com)
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#


ifeq ($(OS),)
    OS=linux
endif

ifeq ($(ARCH),)
	ARCH=x86
endif

ifeq ($(LINKAGE),)
	LINKAGE=dynamic
endif

ifeq ($(CONFIG),)
	CONFIG=debug
endif

include $(SOLUTIONDIR)/build/$(ARCH).$(OS).mk

#OUTPUTDIR = $(SOLUTIONDIR)/output/$(ARCH)/$(OS)/$(LINKAGE)/$(CONFIG)
OUTPUTDIR = $(SOLUTIONDIR)/output/$(ARCH)/$(OS)
#INTERMEDIATEDIR = $(OUTPUTDIR)/$(LINKAGE)/$(CONFIG)
INTERMEDIATEDIR = $(OUTPUTDIR)/obj/$(CONFIG)
#OBJDIR=$(INTERMEDIATEDIR)/obj/$(PROJECTNAME)
OBJDIR=$(INTERMEDIATEDIR)/$(PROJECT)

#####################################################################
## PREPROCESSOR

#USAGE_ELWING = USE_LIBELWING_STATIC
#ifeq ($(LINKAGE), dynamic)
#	USAGE_ELWING = USE_LIBELWING_DYNAMIC
#endif

#TARGET_TYPE =_CONSOLE
#ifeq ($(PROJECTTYPE), LIB)
#	TARGETTYPE = _LIB
#endif 
#ifeq ($(PROJECTTYPE), USRDLL)
#	TARGETTYPE = _USRDLL
#endif 

DBGDEF = _DEBUG
ifeq ($(CONFIG), release)
	DBGDEF = _NDEBUG
endif

.PREPROCESSOR = -DLINUX -DPOSIX -D$(DBGDEF) $(PREPROCESSOR)

#####################################################################
## OPTIMIZATION

.OPTIMIZATION = -O0
ifeq ($(CONFIG), release)
	.OPTIMIZATION = -O2
endif

#####################################################################
## DEBUGING

.DEBUGING = -g3 -ggdb
ifeq ($CONFIG, release)
	.DEBUGING =
endif


#####################################################################
## WARNING

.WARNING = -Wall

#####################################################################
## MISC

.MISC = -fmessage-length=0 -fPIC -fno-strict-aliasing -fno-rtti -fno-exceptions

#####################################################################

.CCFLAGS = $(CCFLAGS) $(.OPTIMIZATION) $(.DEBUGING) $(.WARNING) $(.PREPROCESSOR) $(.MISC)

#####################################################################


#ifeq ($(TARGET_TYPE), USRDLL)
#	.LDFLAGS = -shared
#endif

#ifneq ($(TARGET_TYPE), LIB)
#	.LDFLAGS += -L$(OUTPUTDIR) -lpthread -ldl
#endif
  
#ifeq ($(CONFIG), release)
#	.LDFLAGS += -s
#endif
#
#.LDFLAGS += $(LDFLAGS) 

#####################################################################

#ifeq ($(COMPILER),)
#	COMPILER = $(CXX)
#endif
#
#ifeq ($(LINKER),)
#LINKER = $(LD)
#ifeq ($(TARGET_TYPE), LIB)
#	LINKER = $(AR)
#endif
#endif

#####################################################################

#ifeq ($(TARGET),)
#	TARGET_PREFIX=lib
#	ifeq ($(TARGET_TYPE), CONSOLE)
#		TARGET_PREFIX=
#	endif
#    TARGET_EXT=
#    ifeq ($(TARGET_TYPE), LIB)
#    	TARGET_EXT=.a
#    endif
#    ifeq ($(TARGET_TYPE), USRDLL)
#    	TARGET_EXT=.so
#    endif
#    
#    TARGET=$(TARGET_PREFIX)$(TARGET_NAME)$(TARGET_EXT)
#endif

#####################################################################

OBJS= \
	$(foreach \
		s, \
		$(SOURCES), \
		$(addprefix $(OBJDIR)/, $(addsuffix .o, $(s))) \
	)

DEPS= \
	$(foreach \
		s, \
		$(SOURCES), \
		$(addprefix $(OBJDIR)/, $(addsuffix .d, $(s))) \
	)
	
#####################################################################

$(OBJDIR)/%.cpp.o: %.cpp
	if [ ! -d $(@D) ] ; then mkdir -p $(@D); fi
	echo "["$(PROJECT)"] Compiling ... " $<
	$(CXX) $(.CCFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" $< -o $@

compile: $(OBJS)

exe:
	echo "["$(PROJECT)"] Linking   ... " $(TARGET)
	$(LD) $(OUTPUTDIR)/$(TARGET) $(OBJS) $(LDFLAGS) -lpthread -ldl

dll:
	echo "["$(PROJECT)"] Linking   ... " lib$(TARGET).so
	$(LD) $(OUTPUTDIR)/lib$(TARGET).so -shared $(OBJS) $(LDFLAGS) -lpthread -ldl

lib:
	echo "["$(PROJECT)"] Linking   ... " lib$(TARGET).a
	$(AR) $(OUTPUTDIR)/lib$(TARGET).a $(OBJS)

clean:
	echo "Cleaning" $(TARGET)
	rm -rf $(OBJDIR)
	rm -f $(OUTPUTDIR)/$(TARGET)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(DEPS),)
-include $(DEPS)
endif
endif

