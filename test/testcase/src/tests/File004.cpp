/*
 * File004.cpp
 *
 *  Created on: Oct 17, 2011
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
#include "tests/File004.h"

std::string File004::getDescription() const
{
    return "elw::File() test. file move";
}

bool File004::run()
{
    elw::File f("file004.txt");
    elw::File f0("15.txt");
    f.create();
    elw::OutputStream os(f.openOutputChannel());
    for (int i = 0; i < 100000; ++i)
        os << i;
    os.close();
    dword dwSize = f.length();
    if (!f.move(f.getPath() + ".mv"))
        goto _ERROR;
    if (f.getPath() != "file004.txt.mv")
        goto _ERROR;
    if (f.length() != dwSize)
        goto _ERROR;
    if (f0.exists())
        goto _ERROR;

    f.remove();
    return true;

_ERROR:
    f.remove();
    return false;
}
