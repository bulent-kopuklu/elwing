/*
 * File006.cpp
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
#include "tests/File006.h"

std::string File006::getDescription() const
{
    return "elw::File() test. dir copy";
}

bool File006::run()
{
    elw::File fSrcDir("file006");
    elw::File fDstDir("file006.cp");
    std::vector<elw::File> lst;

    if (!fSrcDir.mkdir())
        goto _ERROR;
    if (!elw::File(fSrcDir.getPath() + '/' + '0').create())
        goto _ERROR;
    if (!elw::File(fSrcDir.getPath() + '/' + '1').mkdir())
        goto _ERROR;
    if (!elw::File(fSrcDir.getPath() + '/' + '1' + '/' + '2').create())
        goto _ERROR;
    if (!elw::File(fSrcDir.getPath() + '/' + '3').mklink("1/2"))
        goto _ERROR;

    if (!fDstDir.mkdir())
        goto _ERROR;

    fSrcDir.list(lst);
    for (uint i = 0; i < lst.size(); ++i)
    {
        elw::File f(fDstDir.getPath() + "/" + lst[i].getName());
        if (!copy(lst[i], f))
            goto _ERROR;
    }

    if (!compare(fSrcDir, fDstDir))
        goto _ERROR;


    fSrcDir.remove(true);
    fDstDir.remove(true);
    return true;

_ERROR:
    fSrcDir.remove(true);
    fDstDir.remove(true);
    return false;
}

bool File006::copy(elw::File& src, elw::File& dst)
{
//    std::cout << src.getPath() << " d:" << src.isDirectory() << " f:" << src.isFile() << " l:" << src.isLink();
//    if (src.isLink())
//        std::cout << " ->" << src.link() << " " << src.getAbsolutePath() << " " << src.getCanonicalPath();
//    std::cout << std::endl;
    if (!src.exists())
        return false;
    if (dst.exists())
        dst.remove(dst.isDirectory());

    if (src.isLink())
    {
        dst.mklink(src.link());
//            throw elw::SystemErrorException(dst.getPath());
    }
    else if (src.isDirectory())
    {
        if (!dst.mkdir())
            return false;
        std::vector<elw::File> lst;
        src.list(lst);
        for (uint i = 0; i < lst.size(); ++i)
        {
            elw::File f(dst.getPath() + "/" + lst[i].getName());
            if (!copy(lst[i], f))
                return false;
        }
    }
    else if (src.isFile())
    {
        if (!dst.create())
            return false;
        elw::OutputStream os(dst.openOutputChannel());
        elw::InputStream is(src.openInputChannel());
        elw::Buffer buff;
        for ( ; ; )
        {
            is >> buff;
            if (is.eof() || is.fail())
                break;
            os << buff;
        }

        os.close();
        is.close();
    }

    return true;
}

bool File006::compare(elw::File& src, elw::File& dst)
{
    std::vector<elw::File> lst0, lst1;
    src.list(lst0);
    dst.list(lst1);
    if (lst0.size() != lst1.size())
        return false;
    for (uint i = 0; i < lst0.size(); ++i)
    {
//        std::cout << lst0[i].getPath() << " " << lst1[i].getPath() << std::endl;
        if (lst0[i].isLink())
        {
            if (!lst1[i].isLink())
                return false;
            if (lst0[i].link() != lst1[i].link())
                return false;
        }
        else if (lst0[i].isDirectory())
        {
            if (!lst1[i].isDirectory())
                return false;
            if (!compare(lst0[i], lst1[i]))
                return false;
        }
        else if (lst0[i].isFile())
        {
            if (!lst1[i].isFile())
                return false;
            if (lst1[i].length() != lst0[i].length())
                return false;
        }

        if (lst0[i].canRead() != lst1[i].canRead())
            return false;
        if (lst0[i].canWrite() != lst1[i].canWrite())
            return false;
        if (lst0[i].canExecute() != lst1[i].canExecute())
            return false;
    }

    return true;
}
