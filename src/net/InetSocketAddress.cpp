/*
 * SocketAddress.cpp
 *
 *  Created on: Aug 24, 2011
 *      Author: Bulent.Kopuklu
 */

#include "stdafx.h"

BEGIN_ELW

InetSocketAddress::InetSocketAddress(word wPort)
{
    init(InetAddress::getAnyLocalAddr(), wPort);
}

InetSocketAddress::InetSocketAddress(const std::string& str, word wPort)
{
    init(InetAddress::getByName(str), wPort);
}

InetSocketAddress::InetSocketAddress(const elw::SmartPtr<InetAddress>& addr, word wPort)
{
    init(addr, wPort);
}

InetSocketAddress::InetSocketAddress(const sockaddr* pRawAddr)
{
    if (pRawAddr->sa_family == SockBase::ipv4)
    {
        memcpy(&m_addr.v4, pRawAddr, sizeof(m_addr.v4));
    }
    else if (pRawAddr->sa_family == SockBase::ipv6)
    {
        memcpy(&m_addr.v6, pRawAddr, sizeof(m_addr.v6));
    }

    m_ptrAddr = InetAddress::getByAddr(pRawAddr);
}

InetSocketAddress::InetSocketAddress(const InetSocketAddress& rThat)
{
    m_addr = rThat.m_addr;
    m_ptrAddr = rThat.m_ptrAddr;
}

const elw::SmartPtr<InetAddress> InetSocketAddress::getAddress() const
{
    return m_ptrAddr;
}

word InetSocketAddress::getPort() const
{
    word wPort = m_ptrAddr->getFamily() == SockBase::ipv4 ? m_addr.v4.sin_port : m_addr.v6.sin6_port;
    return ntohs(wPort);
}

const sockaddr* InetSocketAddress::getSockAddr() const
{
    if (m_ptrAddr->getFamily() == SockBase::ipv4)
        return reinterpret_cast<const sockaddr*>(&m_addr.v4);
    return reinterpret_cast<const sockaddr*>(&m_addr.v6);
}

size_t InetSocketAddress::getSizeOfAddr() const
{
    if (m_ptrAddr->getFamily() == SockBase::ipv4)
        return sizeof(m_addr.v4);
    return sizeof(m_addr.v6);
}

void InetSocketAddress::init(const elw::SmartPtr<InetAddress>& ptr, word wPort)
{
    SockBase::Family f = ptr->getFamily();
    if (SockBase::ipv4 == f)
    {
//        Inet4Address* pv4 = ptr.ptr_dynamic_cast<Inet4Address>();
//        if (NULL == pv4)
//            throw elw::Exception("invalid InetAddress type !!!");
        m_addr.v4.sin_family = SockBase::ipv4;
        m_addr.v4.sin_addr = (in_addr)*((Inet4Address*)&(*ptr));
        m_addr.v4.sin_port = htons(wPort);
    }
    else if (SockBase::ipv6 == f)
    {
//        Inet6Address* pv6 = ptr.ptr_dynamic_cast<Inet6Address>();
//        if (NULL == pv6)
//            throw elw::Exception("invalid InetAddress type !!!");
    }

    m_ptrAddr = ptr;
}

std::string InetSocketAddress::toString() const
{
    word wPort = m_ptrAddr->getFamily() == SockBase::ipv4 ? m_addr.v4.sin_port : m_addr.v6.sin6_port;
    std::stringstream strm;
    strm << m_ptrAddr->toString() << ':' << ntohs(wPort);
    return strm.str();
}

END_ELW
