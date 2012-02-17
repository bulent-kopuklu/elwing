#
#  Makefile
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

ifeq ($(ARCH), )
	ARCH=x86
endif

ifeq ($(OS), )
	OS=linux
endif

MODULES = \
	osimpl/$(OS) \
	src \
	test

all: compile package


clean:
	@$(RM) -rf $(PWD)/output
	@true
	
compile:
	@$(MAKE) -s OS=linux ARCH=x86 debug
	@$(MAKE) -s OS=linux ARCH=x86 release
#	@$(MAKE) -s OS=linux ARCH=x86 LINKAGE=static debug
#	@$(MAKE) -s OS=linux ARCH=x86 LINKAGE=static release
#	@make -s OS=linux ARCH=mips LINKAGE=static debug
#	@make -s OS=linux ARCH=mips LINKAGE=static release
#	@make -s OS=linux ARCH=mips LINKAGE=dynamic debug
#	@make -s OS=linux ARCH=mips LINKAGE=dynamic release
	@echo

package:
	@echo "-----("$(OS)")("$(ARCH)")($@)-----"
	@echo
#	@for p in $(MODULES); do $(MAKE) -s -C $$p SOLUTIONDIR=$(PWD) install; echo; done

install:
	sudo cp -r ./include/elwing /usr/include/
	sudo cp -r ./include/elwing.h /usr/include/
	sudo rm /usr/include/elwing/elwos.h
	sudo cp -r ./interface/elwing /usr/include/
	sudo cp -r ./osimpl/linux/include/elwing /usr/include/
	@true

release debug:
	@echo "-----("$(OS)")("$(ARCH)")($@)-----"
	@echo
	@for p in $(MODULES); do $(MAKE) -s -C $$p SOLUTIONDIR=$(PWD) CONFIG=$@; echo; done

