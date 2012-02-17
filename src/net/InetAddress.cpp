/*
 * InetAddress.cpp
 *
 *  Created on: Aug 24, 2011
 *      Author: Bulent.Kopuklu
 */

#include "stdafx.h"

BEGIN_ELW

// TODO
#ifndef AI_ALL
#define AI_ALL 0x0000
#endif

#ifndef AI_ADDRCONFIG
#define AI_ADDRCONFIG  0x0000
#endif

bool InetAddress::getAllByName(const std::string& strName, std::vector<elw::SmartPtr<InetAddress> >& lst, const std::string& strService)
{
    struct addrinfo hints = { 0 };
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_ALL | AI_ADDRCONFIG | AI_CANONNAME;
    struct addrinfo* pRslt = { 0 };
    if (0 != ::getaddrinfo(strName.c_str(), (strService.empty() ? NULL : strService.c_str()), &hints, &pRslt))
        return false;
    lst.clear();
    struct addrinfo* p = pRslt;
    while(NULL != p)
    {
//        std::cout << strName << "-" << (p->ai_canonname == NULL ? "null" : p->ai_canonname) << " family:" << p->ai_family << " proto:" << p->ai_protocol << " sock:" << p->ai_socktype << std::endl;
        InetAddress* pAddr = NULL;
        if (p->ai_family == AF_INET)
        {
            struct sockaddr_in* psin = (struct sockaddr_in*)p->ai_addr;
            pAddr = new Inet4Address(psin->sin_addr, strName);
        }
        else if (p->ai_family == AF_INET6)
        {
            struct sockaddr_in6* psin = (struct sockaddr_in6*)pRslt->ai_addr;
            pAddr = new Inet6Address(psin->sin6_addr, strName);
        }

        lst.push_back(pAddr);
        p = p->ai_next;
    }

    freeaddrinfo(pRslt);

    return true;
}

InetAddress* InetAddress::getByName(const std::string& strName, const std::string& strService)
{
    struct addrinfo hints = { 0 };
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_ALL;
    struct addrinfo* pRslt = { 0 };
    if (0 != ::getaddrinfo(strName.c_str(), (strService.empty() ? NULL : strService.c_str()), &hints, &pRslt))
        return NULL;
    InetAddress* pAddr = NULL;
    if (pRslt->ai_family == AF_INET)
    {
        struct sockaddr_in* psin = (struct sockaddr_in*)pRslt->ai_addr;
        pAddr = new Inet4Address(psin->sin_addr, strName);
    }
    else if (pRslt->ai_family == AF_INET6)
    {
        struct sockaddr_in6* psin = (struct sockaddr_in6*)pRslt->ai_addr;
        pAddr = new Inet6Address(psin->sin6_addr, strName);
    }

    freeaddrinfo(pRslt);

    return pAddr;
}

InetAddress* InetAddress::getAnyLocalAddr()
{
    return new Inet4Address();
}

InetAddress* InetAddress::getByAddr(const sockaddr* pRawAddr)
{
    InetAddress* pAddr = NULL;
    if (SockBase::ipv4 == pRawAddr->sa_family)
    {
        struct sockaddr_in* psin = (struct sockaddr_in*)pRawAddr;
        pAddr = new Inet4Address(psin->sin_addr);
    }
    else if (SockBase::ipv6 == pRawAddr->sa_family)
    {
        struct sockaddr_in6* psin = (struct sockaddr_in6*)pRawAddr;
        pAddr = new Inet6Address(psin->sin6_addr);
    }

    return pAddr;
}

END_ELW
