#
#  mips.linux.mk
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

TOOLCHAINHOME=/opt/toolchains/uclibc-crosstools-gcc-4.2.3-3/usr/bin
#TOOLCHAINHOME=/opt/uclibc-toolchain/ifx-lxdb26-1.0.2/gcc-3.4.4/toolchain-mips/bin-ccache
#TOOLCHAINHOME=/home/bulentk/Workspace/modem/modem/6271KN3G/toolchain/gcc-wrapper
CC	= $(TOOLCHAINHOME)/mips-linux-gcc
CXX = $(TOOLCHAINHOME)/mips-linux-g++
AR  = $(TOOLCHAINHOME)/mips-linux-ar -rcus
LD	= $(TOOLCHAINHOME)/mips-linux-g++ -o
