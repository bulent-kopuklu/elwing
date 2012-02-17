/*
 * SocketOutputChannel.cpp
 *
 *  Created on: Oct 13, 2011
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

SocketOutputChannel::SocketOutputChannel(const elw::Socket& rSockImpl) :
    m_sock(rSockImpl)
{
//    if (!isOpenned())
//        throw elw::Exception("");
}

std::streamsize SocketOutputChannel::write(const char* pchBuff, std::streamsize nSize)
{
    if (!isOpenned())
        return 0;
    return m_sock.send(pchBuff, nSize);
}

std::streamoff SocketOutputChannel::seek(std::streamoff lSeek,std::ios_base::seekdir pos)
{
    return 0;
}

void SocketOutputChannel::close()
{
    if (isOpenned())
        m_sock.close();
}

bool SocketOutputChannel::isOpenned() const
{
    return m_sock.isConnected();
}

END_ELW
