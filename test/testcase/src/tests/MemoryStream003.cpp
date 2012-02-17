/*
 * MemoryStream003.cpp
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
#include "MemoryStream003.h"

class Request
{
    elw::SmartPtr<elw::MemoryInputStream> m_is;
public:
    Request(elw::SmartPtr<elw::MemoryInputStream>& is) :
        m_is(is)
    {
    }

    elw::MemoryInputStream& getStream()
    {
        return *m_is;
    }
};

std::string MemoryStream003::getDescription() const
{
    return "MemoryInputStream & MemoryInputStream test";
}

bool MemoryStream003::run()
{
    elw::SmartPtr<Request> p = NULL;

    {
        elw::MemoryOutputStream os0;
        os0 << "01234567890";
        os0.write("01234567890", 10).flush();
        elw::SmartPtr<elw::MemoryInputStream> is0(
                new elw::MemoryInputStream(os0.getBuffer())
                );
        int c0 = is0->get();
        if (c0 != '0')
            return false;
        c0 = is0->get();
        if (c0 != '1')
            return false;

        p = new Request(is0);
    }

    int c = p->getStream().get();
    std::cout << c << ":" << (int)'2' << std::endl;
    if (c != '2')
        return false;

    return true;
}
