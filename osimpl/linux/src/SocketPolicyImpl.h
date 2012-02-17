/*
 * SocketPolicyImpl.h
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

#ifndef ElwingSocketPolicyImpl_h__
#define ElwingSocketPolicyImpl_h__

BEGIN_ELW

class SocketPolicyImpl :
    public elw::ISocketPolicy
{
private:
    HSOCKET m_hSocket;

public:
    SocketPolicyImpl();
    virtual ~SocketPolicyImpl();

public:
    void attach(
            HSOCKET hSocket
            );

    bool socket(
            SockFamily iFamily,
            SockType iType,
            SockProto iProtocol
            );

    int connect(
            const sockaddr* pAddr,
            socklen_t nSizeOfAddr
            );

    int bind(
            const sockaddr* pAddr,
            socklen_t nSizeOfAddr
            );

    HSOCKET accept(
            sockaddr* pAddr,
            socklen_t* pnSizeOfAddr
            );

    int listen(
            int iBacklog
            );

    int recv(
            char* pchBuff,
            size_t nSizeOf,
            SockFlag eFlags
            );

    int send(
            const char* pchBuff,
            size_t nSizeOf,
            SockFlag eFlags
            );

    int shutdown(
            SockShutmode sm
            );

    int close();

    int setOption(
            int iLevel,
            int iOption,
            const void* pvValue,
            size_t nSizeOf
            );

    HSOCKET getSafeHandle() const { return m_hSocket; }
};

END_ELW

#endif /* ElwingSocketPolicyImpl_h__ */
