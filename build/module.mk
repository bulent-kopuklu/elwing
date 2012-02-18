#
#  module.mk
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

all:
	@for m in $(MODULES); do $(MAKE) -s -C $$m SOLUTIONDIR=$(SOLUTIONDIR) all; done

clean:
	@for m in $(MODULES); do $(MAKE) -s -C $$m SOLUTIONDIR=$(SOLUTIONDIR) clean; done

install:
	@for m in $(MODULES); do $(MAKE) -s -C $$m SOLUTIONDIR=$(SOLUTIONDIR) install; done