/*
 * Socket.cpp
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

Socket::Socket() :
    m_fConnected(false)
{
//    m_ptrImpl = elw::ClassFactory::instantiate<elw::ISocketPolicy>(ELW_SOCKET_POLICY_IMPL_KEYWORD);
    m_ptrImpl = (elw::ISocketPolicy*)elw::CreatePolicyImpl(ELW_SOCKET_POLICY_IMPL_KEYWORD);
//    if (m_ptrImpl == NULL)
//        throw elw::ClassNotFoundException(ELW_SOCKET_POLICY_IMPL_KEYWORD);
//    if (!m_ptrImpl->socket(SockBase::ipv4, SockBase::stream, SockBase::tcp))
//        throw elw::SystemErrorException("::socket()");
}

Socket::Socket(HSOCKET hSocket, const elw::InetSocketAddress& addr) :
    m_fConnected(false)
{
    if (hSocket != SockBase::invalid)
    {
        m_ptrImpl = (elw::ISocketPolicy*)elw::CreatePolicyImpl(ELW_SOCKET_POLICY_IMPL_KEYWORD);
//        if (m_ptrImpl == NULL)
//            throw elw::ClassNotFoundException(ELW_SOCKET_POLICY_IMPL_KEYWORD);
        m_ptrImpl->attach(hSocket);
        m_ptrExtAddr = new elw::InetSocketAddress(addr);
        m_fConnected = true;
    }
}

Socket::Socket(const elw::Socket& sock) :
    m_ptrImpl(sock.m_ptrImpl),
    m_fConnected(sock.m_fConnected),
    m_ptrExtAddr(sock.m_ptrExtAddr),
    m_ptrIntAddr(sock.m_ptrIntAddr),
    m_ptrInCh(sock.m_ptrInCh),
    m_ptrOutCh(sock.m_ptrOutCh)

{
//    if (m_ptrImpl == NULL)
//        ;
//    if (m_ptrImpl->getSafeHandle() == elw::SockBase::invalid)
//        ;
}

Socket::~Socket()
{
    std::cout << "Socket::~Socket()" << std::endl;
}

bool Socket::create(elw::SockBase::Family f, elw::SockBase::Type t, elw::SockBase::Protocol p)
{
    if (0 > m_ptrImpl->socket(f, t, p))
        return false;
    return true;
}

bool Socket::isConnected() const
{
    return m_fConnected;
}

bool Socket::connect(const std::string& strAddr, word wPort)
{
    return connect(InetSocketAddress(strAddr, wPort));
}

bool Socket::connect(elw::SmartPtr<elw::InetAddress>& rInetAddr, word wPort)
{
    return connect(InetSocketAddress(rInetAddr, wPort));
}

bool Socket::connect(const elw::InetSocketAddress& rSockAddr)
{
    if (0 > m_ptrImpl->connect(rSockAddr.getSockAddr(), rSockAddr.getSizeOfAddr()))
        return false;
//        throw elw::SystemErrorException(
//                MKSTR("Failed to connect to remote address. " << rSockAddr.toString())
//                );
    m_ptrExtAddr = new elw::InetSocketAddress(rSockAddr);
    m_fConnected = true;
    return true;
}

bool Socket::bind(word wPort)
{
    return bind(elw::InetSocketAddress(wPort));
}

bool Socket::bind(elw::SmartPtr<elw::InetAddress>& rInetAddr, word wPort)
{
    return bind(elw::InetSocketAddress(rInetAddr, wPort));
}

bool Socket::bind(const elw::InetSocketAddress& rSockAddr, int iBacklog)
{
    if (0 > m_ptrImpl->bind(rSockAddr.getSockAddr(), rSockAddr.getSizeOfAddr()))
        return false;
    return true;
//        throw elw::SystemErrorException(
//                MKSTR("Failed to bind to local port. " << rSockAddr.toString())
//                );
}

int Socket::recv(char* pchBuffer, size_t nSizeOf, elw::SockBase::Flag f)
{
    if (!isConnected())
        return 0;
    return m_ptrImpl->recv(pchBuffer, nSizeOf, f);
}

int Socket::send(const char* pchBuffer, size_t nSizeOf, elw::SockBase::Flag f)
{
    if (!isConnected())
        return 0;
    return m_ptrImpl->send(pchBuffer, nSizeOf, f);
}

int Socket::shutdown(SockShutmode sm)
{
    int iRslt = m_ptrImpl->shutdown(sm);
    if (0 == iRslt)
        m_fConnected = false;
    return iRslt;
}

int Socket::close()
{
    int iRslt = m_ptrImpl->close();
    if (0 == iRslt)
        m_fConnected = false;
    return iRslt;
}

int Socket::setOption(int iLevel, int iOption, const void* pvValue, size_t nSize)
{
    return m_ptrImpl->setOption(iLevel, iOption, pvValue, nSize);
}

HSOCKET Socket::getSafeHandle() const
{
    if (!isConnected())
        return elw::SockBase::invalid;
    return m_ptrImpl->getSafeHandle();
}

elw::SmartPtr<elw::IInputChannel> Socket::getInputChannel()
{
    if (NULL == m_ptrInCh && isConnected())
        m_ptrInCh = new elw::SocketInputChannel(*this);
    return m_ptrInCh;
}

elw::SmartPtr<IOutputChannel> Socket::getOutputChannel()
{
    if (NULL == m_ptrOutCh && isConnected())
        m_ptrOutCh = new elw::SocketOutputChannel(*this);
    return m_ptrOutCh;
}

std::string Socket::toString() const
{
    std::stringstream strm;
    strm << m_ptrExtAddr->toString();

    return strm.str();
}

END_ELW
