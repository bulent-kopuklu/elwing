/*
 * File003.cpp
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
#include "tests/File003.h"

std::string File003::getDescription() const
{
    return "elw::File() test. input output stream seek";
}

bool File003::run()
{
    elw::File file("file003.txt");
    file.create();
    elw::OutputStream os(file.openOutputChannel());
    elw::InputStream is(file.openInputChannel());

    std::string str;
    char psz[10] = { 0 };
    std::streampos pos;

    if (!os.isOpened())
        goto _ERROR;

    for (int i = 0; i < 16000; ++i)
    {
        sprintf(psz, "%05d\n", i);
        os << psz;
    }
    os.close();

    if (!is.isOpened())
        goto _ERROR;

    is.seekg(6*1000, std::ios::cur);
    is.getline(psz, sizeof(psz));
    str = psz;
    if (str != "01000")
        goto _ERROR;

    is.seekg(0, std::ios::beg);
    is.getline(psz, sizeof(psz));
    str = psz;
    if (str != "00000")
        goto _ERROR;

    is.seekg(6*999, std::ios::cur);
    is.getline(psz, sizeof(psz));
    str = psz;
    if (str != "01000")
        goto _ERROR;

    is.seekg(6*9, std::ios::cur);
    is.getline(psz, sizeof(psz));
    str = psz;
    if (str != "01010")
        goto _ERROR;

    is.seekg(-6*11, std::ios::cur);
    pos = is.tellg();
    is.getline(psz, sizeof(psz));
    str = psz;
    if (str != "01000")
        goto _ERROR;

    is.seekg(-6*1001, std::ios::cur);
    is.getline(psz, sizeof(psz));
    str = psz;
    if (str != "00000")
        goto _ERROR;

    is.seekg(pos, std::ios::beg);
    is.getline(psz, sizeof(psz));
    str = psz;
    if (str != "01000")
        goto _ERROR;

    is.close();
    file.remove();
    return true;

_ERROR:
    file.remove();
    return false;
}
