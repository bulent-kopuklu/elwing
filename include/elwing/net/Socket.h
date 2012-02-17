/*
 * Socket.h
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

#ifndef ElwingSocket_h__
#define ElwingSocket_h__

BEGIN_ELW

class Socket
{
    elw::SmartPtr<elw::ISocketPolicy> m_ptrImpl;
    bool m_fConnected;

    elw::SmartPtr<elw::InetSocketAddress> m_ptrExtAddr;
    elw::SmartPtr<elw::InetSocketAddress> m_ptrIntAddr;

    elw::SmartPtr<elw::IInputChannel> m_ptrInCh;
    elw::SmartPtr<elw::IOutputChannel> m_ptrOutCh;
public:
    Socket();

    Socket(HSOCKET hSocket,
            const elw::InetSocketAddress& addr
            );

    Socket(const Socket& sock);

    virtual ~Socket();

    bool create(
            elw::SockBase::Family f = elw::SockBase::ipv4,
            elw::SockBase::Type t = elw::SockBase::stream,
            elw::SockBase::Protocol p = elw::SockBase::tcp
            );

    bool connect(
            const std::string& strAddr,
            word wPort
            );
    bool connect(
            elw::SmartPtr<elw::InetAddress>& rInetAddr,
            word wPort
            );
    bool connect(
            const elw::InetSocketAddress& rSockAddr
            );
    bool bind(
            word wPort
            );
    bool bind(
            elw::SmartPtr<elw::InetAddress>& rInetAddr,
            word wPort
            );
    bool bind(
            const elw::InetSocketAddress& rSockAddr,
            int iBacklog = 5
            );

    int recv(
            char* pchBuffer,
            size_t nSizeOf,
            elw::SockBase::Flag f = elw::SockBase::none
            );

    int send(
            const char* pchBuffer,
            size_t nSizeOf,
            elw::SockBase::Flag f = elw::SockBase::none
            );

    virtual int shutdown(
            elw::SockBase::Shutmode sm = elw::SockBase::rw
            );

    virtual int close();

    virtual int setOption(
            int iLevel,
            int iOption,
            const void* pvValue,
            size_t nSizeOf
            );

    virtual HSOCKET getSafeHandle() const;

    bool isConnected() const;

    elw::SmartPtr<elw::IInputChannel> getInputChannel();
    elw::SmartPtr<elw::IOutputChannel> getOutputChannel();

    std::string toString() const;
//    {
//        std::stringstream strm;
//        strm << m_ptrExtAddr->toString();
//
//        return strm.str();
//    }
};

END_ELW

#endif /* ElwingSocket_h__ */
