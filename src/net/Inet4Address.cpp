/*
 * Inet4Address.cpp
 *
 *  Created on: Aug 24, 2011
 *      Author: Bulent.Kopuklu
 */

#include "stdafx.h"

BEGIN_ELW

Inet4Address::Inet4Address()
{
    m_addr.s_addr = SockBase::any;
    m_strHost = "0.0.0.0";
}

Inet4Address::Inet4Address(const std::string& str)
{
    if (1 != ::inet_pton(SockBase::ipv4, str.c_str(), &m_addr))
    {
        m_addr.s_addr = SockBase::any;
        m_strHost = "0.0.0.0";
    }
    else
        m_strHost = str;
}

Inet4Address::Inet4Address(in_addr addr, const std::string& strHost) :
    m_addr(addr),
    m_strHost(strHost)
{
}

void Inet4Address::getAddress(std::vector<uint8>& lst) const
{
    uint8 b[4] = { 0 };
    ::memcpy(b, &m_addr, sizeof(b));
    for (int i = 0; i < 4; ++i)
        lst.push_back(b[i]);
}

std::string Inet4Address::getCanonicalHostName() const
{
    sockaddr_in a;
    a.sin_family = SockBase::ipv4;
    a.sin_addr = m_addr;
    char sz[1024];
    ::getnameinfo((sockaddr*)&a, sizeof(a), sz, sizeof(sz), NULL, 0, 0);
    return sz;
}

std::string Inet4Address::getHostName() const
{
    return m_strHost;
}

std::string Inet4Address::getHostAddress() const
{
    char sz[INET_ADDRSTRLEN] = {0};
    ::inet_ntop(AF_INET, const_cast<in_addr*>(&m_addr), sz, INET_ADDRSTRLEN);
    return sz;
}

std::string Inet4Address::toString() const
{
    std::stringstream strm;
    strm << getHostName() << " IPv4 (" << getHostAddress() << ")";
    return strm.str();
}

SockBase::Family Inet4Address::getFamily() const
{
    return SockBase::ipv4;
}

END_ELW
