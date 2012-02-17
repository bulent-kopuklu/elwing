/*
 * SocketInputChannel.h
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

#ifndef ElwingSocketInputChannel_h__
#define ElwingSocketInputChannel_h__

BEGIN_ELW

class SocketInputChannel :
    public elw::IInputChannel
{
    elw::Socket m_sock;
public:
    SocketInputChannel(
            const elw::Socket& rSock
            );

    std::streamsize read(
            char* pchBuff,
            std::streamsize nSize
            );

    bool isOpenned() const;

    void close();

    std::streamoff seek(
            std::streamoff lSeek,
            std::ios_base::seekdir pos
            );
};

END_ELW

#endif /* ElwingSocketInputChannel_h__ */
