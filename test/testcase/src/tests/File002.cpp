/*
 * File002.cpp
 *
 *  Created on: Oct 14, 2011
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
#include "tests/File002.h"

std::string File002::getDescription() const
{
    return "elw::File() test. input output stream read write";
}

bool File002::run()
{

    elw::File file("file002.txt");
    file.create();
    elw::OutputStream os(file.openOutputChannel());
    elw::InputStream is(file.openInputChannel());

    int i = 0;

    if (!os.isOpened())
        goto _ERROR;

    for (i = 0; i < 1000; ++i)
    {
        char psz[5] = { 0 };
        sprintf(psz, "%03d.", i);
        os << psz;
        for (int l = 0; l < 10; ++l)
            os << l;
        os << '\n';
    }
    os.close();

    if (!is.isOpened())
        goto _ERROR;
    for ( ; ; )
    {
        char ch[15] = { 0 };
        is.getline(ch, sizeof(ch));
        if (is.eof() || is.fail())
            break;
        --i;
    }

    is.close();

    if (i != 0)
        goto _ERROR;

    file.remove();
    return true;

_ERROR:
    file.remove();
    return false;
}
