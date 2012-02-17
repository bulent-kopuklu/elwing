/*
 * InetAddress001.cpp
 *
 *  Created on: Oct 24, 2011
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
#include "InetAddress001.h"

std::string InetAddress001::getDescription() const
{
    return"elw::InetAddress() test. www.sf.net";
}

bool InetAddress001::run()
{
    const std::string strHost0("www.sf.net");
    const std::string strHost1("www.sourceforge.net");

    elw::SmartPtr<elw::InetAddress> ptrAddr0 = elw::InetAddress::getByName(strHost0);
    if (ptrAddr0 == NULL)
        return false;
    elw::SmartPtr<elw::InetAddress> ptrAddr1 = elw::InetAddress::getByName(strHost1);
    if (ptrAddr1 == NULL)
        return false;
    if (ptrAddr0->getHostName() != strHost0)
        return false;
    if (ptrAddr1->getHostName() != strHost1)
        return false;
    if (ptrAddr1->getCanonicalHostName() != ptrAddr0->getCanonicalHostName())
        return false;
    if (ptrAddr1->getHostAddress() != ptrAddr0->getHostAddress())
        return false;
    if (ptrAddr1->getFamily() != ptrAddr0->getFamily())
        return false;
    return true;
}
