/*
 * MemoryInputStream.h
 *
 *  Created on: Dec 20, 2011
 *      Author: Bulent.Kopuklu
 *
 *  Copyright (C) 2010 by Bulent Kopuklu (bulent.kopuklu@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ElwingMemoryInputStream_h__
#define ElwingMemoryInputStream_h__

BEGIN_ELW

class MemoryInputStream :
    public std::istream
{
public:
    MemoryInputStream(const elw::Buffer& rBuffer);
    MemoryInputStream(const elw::SmartPtr<elw::Buffer>& ptrBuffer);

    virtual ~MemoryInputStream();

    void dump();
};

END_ELW

#endif /* ElwingMemoryInputStream_h__ */
