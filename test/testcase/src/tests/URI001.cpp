/*
 * URI001.cpp
 *
 *  Created on: Dec 29, 2011
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
#include "URI001.h"

URI001::URI001()
{
}

URI001::~URI001()
{
}

std::string URI001::getDescription() const
{
    return "URI test";
}

bool URI001::run()
{
    elw::InetSocketAddress addr("192.168.1.1", 22000);
    std::stringstream strm;
    strm << "foo://" << addr.getAddress()->getHostAddress() << ":" << addr.getPort() << "/";
    elw::URI uri(strm.str());

    return true;
}


