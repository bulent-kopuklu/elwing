/*
 * FileInputChannel.cpp
 *
 *  Created on: Sep 27, 2011
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

BEGIN_ELW

FileInputChannel::FileInputChannel(const elw::File& f) :
    m_pfd(NULL)
{
    if (f.exists() && f.isFile() && f.canRead())
        m_pfd = ::fopen(f.getPath().c_str(), "rb");
}

std::streamsize FileInputChannel::read(char* pchBuff, std::streamsize nSize)
{
    if (!isOpenned())
        return -1;
    if (::feof(m_pfd))
        return 0;

    return (std::streamsize) ::fread(pchBuff, 1, nSize, m_pfd);
}

bool FileInputChannel::isOpenned() const
{
    return m_pfd != NULL;
}

std::streamoff FileInputChannel::seek(std::streamoff off, std::ios::seekdir origin)
{
    if (!isOpenned())
        return -1;
    int iOrigin = -1;
    if (origin == std::ios::beg)
        iOrigin = SEEK_SET;
    else if (std::ios::cur)
        iOrigin = SEEK_CUR;
    else if (origin == std::ios::end)
        iOrigin = SEEK_END;
    if (iOrigin == -1)
        return -1;
    if (-1 == ::fseek(m_pfd, off, iOrigin))
        return -1;
    return ::ftell(m_pfd);
}

void FileInputChannel::close()
{
    if (!isOpenned())
        return;

    ::fclose(m_pfd);
    m_pfd = NULL;
}

END_ELW
