/*
 * File005.cpp
 *
 *  Created on: Oct 18, 2011
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
#include "tests/File005.h"

std::string File005::getDescription() const
{
    return "elw::File() test. file copy";
}

bool File005::run()
{
    elw::File f("file005.txt");
    f.create();
    elw::OutputStream os(f.openOutputChannel());
    for (int i = 0; i < 100000; ++i)
        os << i;
    os.close();
    elw::File fd(f.getPath() + ".copy");
    fd.create();
    elw::OutputStream osd(fd.openOutputChannel());
    elw::InputStream is(f.openInputChannel());
    elw::Buffer buff(4096);

    if (!osd.isOpened() || !is.isOpened())
        goto _ERROR;

    while (!is.eof())
    {
        is >> buff;
        osd << buff;
        if (os.fail())
            break;
    }

    is.close();
    osd.close();

    fd.setExecutable(f.canExecute());
    fd.setReadable(f.canRead());
    fd.setWritable(f.canWrite());

    if (f.canExecute() != fd.canExecute())
        goto _ERROR;
    if (f.canRead() != fd.canRead())
        goto _ERROR;
    if (f.canWrite() != fd.canWrite())
        goto _ERROR;
    if (f.length() != fd.length())
        goto _ERROR;

    f.remove();
    fd.remove();
    return true;

_ERROR:
    f.remove();
    fd.remove();
    return false;
}

