/*
 * ServerSocket.cpp
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

ServerSocket::ServerSocket() :
    m_pImpl(NULL)
{
//    m_pImpl = elw::ClassFactory::instantiate<elw::ISocketPolicy>(ELW_SOCKET_POLICY_IMPL_KEYWORD);
    m_pImpl = (elw::ISocketPolicy*)elw::CreatePolicyImpl(ELW_SOCKET_POLICY_IMPL_KEYWORD);
//    if (NULL == m_pImpl)
//        throw elw::ClassNotFoundException(ELW_SOCKET_POLICY_IMPL_KEYWORD);
//    if (!m_pImpl->socket(SockBase::ipv4, SockBase::stream, SockBase::tcp))
//        throw elw::SystemErrorException("::socket()");
}

//ServerSocket::ServerSocket(SockBase::Family f, SockBase::Type t, SockBase::Protocol p)
//{
////    m_pImpl = elw::ClassFactory::instantiate<elw::ISocketPolicy>(ELW_SOCKET_POLICY_IMPL_KEYWORD);
//    m_pImpl = (elw::ISocketPolicy*)elw::CreatePolicyImpl(ELW_SOCKET_POLICY_IMPL_KEYWORD);
//    if (m_pImpl == NULL)
//        throw elw::ClassNotFoundException(ELW_SOCKET_POLICY_IMPL_KEYWORD);
//    if (!m_pImpl->socket(f, t, p))
//        throw elw::SystemErrorException("::socket()");
//}

ServerSocket::~ServerSocket()
{
    if (NULL != m_pImpl)
        delete m_pImpl;
}

bool ServerSocket::create(SockBase::Family f, SockBase::Type t, SockBase::Protocol p)
{
    if (!m_pImpl->socket(SockBase::ipv4, SockBase::stream, SockBase::tcp))
        return false;
    return true;
}

bool ServerSocket::bind(word wPort, int iBacklog)
{
    return bind(InetSocketAddress(wPort), iBacklog);
}

bool ServerSocket::bind(const elw::SmartPtr<elw::InetAddress>& rInetAddr, word wPort, int iBacklog)
{
    return bind(InetSocketAddress(rInetAddr, wPort), iBacklog);
}

bool ServerSocket::bind(const elw::InetSocketAddress& rSockAddr, int iBacklog)
{
    if (0 > m_pImpl->bind(rSockAddr.getSockAddr(), rSockAddr.getSizeOfAddr()))
        return false;
//        throw elw::SystemErrorException(
//                MKSTR("Failed to bind to local port. " << rSockAddr.toString())
//                );
    if (0 > m_pImpl->listen(iBacklog))
        return false;
//        throw elw::SystemErrorException(
//                MKSTR("Failed to listen local port. " << rSockAddr.toString())
//                );
    return true;
}

Socket* ServerSocket::accept()
{
    size_t iLen = SockBase::ipv4 == m_f ? sizeof(in_addr) : sizeof(in6_addr);
    char pch[iLen];
    sockaddr* paddr = (sockaddr*)pch;
    HSOCKET hSocket = m_pImpl->accept(paddr, &iLen);
    if (-1 == hSocket)
        return NULL;

    InetSocketAddress addr(paddr);
    return new Socket(hSocket, addr);
}

int ServerSocket::close()
{
    m_pImpl->shutdown(elw::SockBase::rw);
    return m_pImpl->close();
}

HSOCKET ServerSocket::getSafeHandle() const
{
    return m_pImpl->getSafeHandle();
}

END_ELW
