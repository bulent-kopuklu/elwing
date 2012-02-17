/*
 * File001.cpp
 *
 *  Created on: Oct 11, 2011
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
#include "tests/File001.h"

std::string File001::getDescription() const
{
    return "elw::File() test.";
}

bool File001::run()
{
    elw::File f("file001");

    if ("file001" != f.getName())
        return false;
    if (f.getCanonicalPath() != elw::File::getwd() + '/' + f.getName())
        return false;

    if (!f.create())
        return false;
    if (!f.isFile())
        return false;
    if (!f.remove())
        return false;

    if (!f.mklink("/var"))
        return false;
    if (!f.isLink())
        return false;
    if (!f.isDirectory())
        return false;
    if (!f.remove())
        return false;

    if (!f.mkdir())
        return false;
    if (!f.isDirectory())
        return false;
    if (!f.remove())
        return false;

    if (!f.mkdir())
        return false;
    if (!f.isDirectory())
        return false;

    elw::File f0(f.getPath() + '/' + "file");
    if (!f0.create())
        return false;
    if (f.remove())
        return false;
    elw::File f1(f.getPath() + '/' + "dir");
    if (!f1.mkdir())
        return false;
    elw::File f3(f1.getPath() + '/' + "file");
    if (!f3.create())
        return false;
    elw::File f2(f.getPath() + '/' + "link");
    f2.mklink(f1.getName() + '/' + f3.getName());

    if (!f.remove(true))
        return false;

    return true;
}
