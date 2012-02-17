/*
 * Inet6Address.cpp
 *
 *  Created on: Aug 24, 2011
 *      Author: Bulent.Kopuklu
 */

#include "stdafx.h"

BEGIN_ELW

Inet6Address::Inet6Address(const std::string& str)
{
    if (1 == inet_pton(AF_INET6, str.c_str(), &m_addr))
        m_strHost = str;
}

Inet6Address::Inet6Address(in6_addr addr, const std::string& str) :
    m_addr(addr),
    m_strHost(str)
{
}

std::string Inet6Address::getHostAddress() const
{
    char sz[INET6_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET6, const_cast<in6_addr*>(&m_addr), sz, INET6_ADDRSTRLEN);
    return sz;
}

void Inet6Address::getAddress(std::vector<uint8>& lst) const
{
    uint8 b[sizeof(m_addr)] = { 0 };
    memcpy(b, &m_addr, sizeof(b));
    for (int i = 0; i < 4; ++i)
        lst.push_back((int)b[i]);
}

std::string Inet6Address::getHostName() const
{
    return m_strHost;
}

std::string Inet6Address::getCanonicalHostName() const
{
    sockaddr_in6 a;
    a.sin6_family = AF_INET6;
    a.sin6_addr = m_addr;
    char sz[1024];
    getnameinfo((sockaddr*)&a, sizeof(a), sz, sizeof(sz), NULL, 0, 0);
    return sz;
}

std::string Inet6Address::toString() const
{
    std::stringstream strm;
    strm << getHostName() << " IPv6 (" << getHostAddress() << ")";
    return strm.str();
}

SockBase::Family Inet6Address::getFamily() const
{
    return SockBase::ipv6;
}

END_ELW
