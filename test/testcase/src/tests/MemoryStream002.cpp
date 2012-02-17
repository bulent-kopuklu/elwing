/*
 * MemoryStream002.cpp
 *
 *  Created on: Dec 26, 2011
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

#include "stdafx.h"
#include "MemoryStream002.h"

std::string MemoryStream002::getDescription() const
{
    return "MemoryInputStream & MemoryInputStream test";
}

bool MemoryStream002::run()
{
    elw::MemoryOutputStream os0;
    const char* data = "This is a test";
    os0 << data;
    os0.flush();
    elw::MemoryInputStream istr1(os0.getBuffer());

    int c = istr1.get();
    if (c != 'T')
        return false;
    c = istr1.get();
    if (c != 'h')
        return false;

    std::string str;
    istr1 >> str;
    if (str != "is")
        return false;

    char buffer[32];
    istr1.read(buffer, sizeof(buffer));
    if (istr1.gcount() != 10)
        return false;
    buffer[istr1.gcount()] = 0;
    if (std::string(" is a test") != buffer)
        return false;

//    elw::Buffer b;
//    strcpy(b.ptr(), "123");
//    b.count(3);
//
//    elw::MemoryInputStream istr2(b);
//    c = istr2.get();
//    if (c != '1')
//        return false;
//    if (!istr2.good())
//        return false;
//    c = istr2.get();
//    if (c != '2')
//        return false;
//    istr2.unget();
//    c = istr2.get();
//    if (c != '2')
//        return false;
//    if (!istr2.good())
//        return false;
//    c = istr2.get();
//    if (c != '3')
//        return false;
//    if (!istr2.good())
//        return false;
//    c = istr2.get();
//    if (c != -1)
//        return false;
//    if (!istr2.eof())
//        return false;
    return true;
}
