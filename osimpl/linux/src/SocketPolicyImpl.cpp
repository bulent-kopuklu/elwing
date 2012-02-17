/*
 * SocketPolicyImpl.cpp
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
#include "SocketPolicyImpl.h"

BEGIN_ELW

SocketPolicyImpl::SocketPolicyImpl() :
    m_hSocket(-1)
{
    std::cout << "SocketPolicyImpl::SocketPolicyImpl()" << std::endl;
}

SocketPolicyImpl::~SocketPolicyImpl()
{
    std::cout << "SocketPolicyImpl::~SocketPolicyImpl()" << std::endl;
}

void SocketPolicyImpl::attach(HSOCKET hSocket)
{
    m_hSocket = hSocket;
}

bool SocketPolicyImpl::socket(SockFamily eFamily, SockType eType, SockProto eProtocol)
{
    m_hSocket = ::socket(eFamily, eType, eProtocol);
    return m_hSocket != -1;
}


int SocketPolicyImpl::connect(const sockaddr* pAddr, socklen_t nSizeOfAddr)
{
    return ::connect(m_hSocket, pAddr, nSizeOfAddr);
}

int SocketPolicyImpl::listen(int iBacklog)
{
    return ::listen(m_hSocket, iBacklog);
}

int SocketPolicyImpl::bind(const sockaddr* pAddr, socklen_t nSizeOfAddr)
{
    return ::bind(m_hSocket, pAddr, nSizeOfAddr);
}

int SocketPolicyImpl::accept(sockaddr* pAddr, socklen_t* pnSizeOfAddr)
{
    return ::accept(m_hSocket, pAddr, pnSizeOfAddr);
}

int SocketPolicyImpl::recv(char* pchBuff, size_t nSizeOf, SockFlag eFlags)
{
    return ::recv(m_hSocket, pchBuff, nSizeOf, eFlags);
}

int SocketPolicyImpl::send(const char* pchBuff, size_t nSizeOf, SockFlag eFlags)
{
    int iRslt = -1;
    do
    {
        iRslt = ::send(m_hSocket, pchBuff, nSizeOf, eFlags);
    }
    while (iRslt < 0 && errno == EINTR);
    return iRslt;
}

int SocketPolicyImpl::shutdown(SockShutmode sm)
{
    return ::shutdown(m_hSocket, sm);
}

int SocketPolicyImpl::close()
{
    int iRslt = ::close(m_hSocket);
    if (iRslt > 0)
        m_hSocket = -1;
    return iRslt;
}

int SocketPolicyImpl::setOption(int iLevel, int iOption, const void* pvValue, size_t nSizeOf)
{
    return ::setsockopt(m_hSocket, iLevel, iOption, pvValue, nSizeOf);
}


const elw::SockBase::Family SockBase::ipv4     = elw::SockBase::Family(PF_INET);
const elw::SockBase::Family SockBase::ipv6     = elw::SockBase::Family(PF_INET6);
const elw::SockBase::Family SockBase::local    = elw::SockBase::Family(PF_LOCAL);
const elw::SockBase::Family SockBase::netlink  = elw::SockBase::Family(PF_NETLINK);
const elw::SockBase::Family SockBase::packet   = elw::SockBase::Family(PF_PACKET);

const elw::SockBase::Type SockBase::stream     = elw::SockBase::Type(SOCK_STREAM);
const elw::SockBase::Type SockBase::datagram   = elw::SockBase::Type(SOCK_DGRAM);
const elw::SockBase::Type SockBase::raw        = elw::SockBase::Type(SOCK_RAW);
const elw::SockBase::Type SockBase::rdm        = elw::SockBase::Type(SOCK_RDM);
const elw::SockBase::Type SockBase::seqpacket  = elw::SockBase::Type(SOCK_SEQPACKET);

const elw::SockBase::Protocol SockBase::tcp    = elw::SockBase::Protocol(IPPROTO_TCP);
const elw::SockBase::Protocol SockBase::udp    = elw::SockBase::Protocol(IPPROTO_UDP);

const elw::SockBase::Shutmode SockBase::r      = elw::SockBase::Shutmode(SHUT_RD);
const elw::SockBase::Shutmode SockBase::w      = elw::SockBase::Shutmode(SHUT_WR);
const elw::SockBase::Shutmode SockBase::rw     = elw::SockBase::Shutmode(SHUT_RDWR);

const elw::SockBase::Flag SockBase::none       = elw::SockBase::Flag(0);
const elw::SockBase::Flag SockBase::oob        = elw::SockBase::Flag(MSG_OOB);
const elw::SockBase::Flag SockBase::dontroute  = elw::SockBase::Flag(MSG_DONTROUTE);
const elw::SockBase::Flag SockBase::dontwait   = elw::SockBase::Flag(MSG_DONTWAIT);
const elw::SockBase::Flag SockBase::nosignal   = elw::SockBase::Flag(MSG_NOSIGNAL);
const elw::SockBase::Flag SockBase::peek       = elw::SockBase::Flag(MSG_PEEK);
const elw::SockBase::Flag SockBase::waitall    = elw::SockBase::Flag(MSG_WAITALL);
const elw::SockBase::Flag SockBase::trunc      = elw::SockBase::Flag(MSG_TRUNC);
const elw::SockBase::Flag SockBase::errqueue   = elw::SockBase::Flag(MSG_ERRQUEUE);

const elw::SockBase::Address SockBase::any     = elw::SockBase::Address(INADDR_ANY);
const elw::SockBase::Address SockBase::loopback= elw::SockBase::Address(INADDR_LOOPBACK);

const elw::SockBase::Handle SockBase::invalid  = elw::SockBase::Handle(-1);

//REGISTER_ELW_SOCKET_POLICY_IMPL(SocketPolicyImpl);

END_ELW
