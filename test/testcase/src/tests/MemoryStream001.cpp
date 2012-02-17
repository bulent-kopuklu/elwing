/*
 * MemoryStream001.cpp
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
#include "MemoryStream001.h"

std::string MemoryStream001::getDescription() const
{
    return "MemoryInputStream & MemoryInputStream test";
}

bool MemoryStream001::run()
{
    elw::MemoryOutputStream os(64);
    for (int i = 0; i < 10; ++i)
    {
        os << "1234567890";
        os << "1";
        os << "234567890";
        os << "1234567890";
        os.flush();

        elw::SmartPtr<elw::Buffer> b = os.getBuffer();

        std::string str0(b->ptr(), b->length());
        std::string str1;

        elw::MemoryInputStream is(os.getBuffer());
        elw::Buffer b0(5);
        for ( ; ; )
        {
            is >> b0;
            if (b0.length() == 0)
                break;

            str1 += std::string(b0.ptr(), b0.length());
        }

        if (str0 != str1)
            return false;
    }

    return true;
}
