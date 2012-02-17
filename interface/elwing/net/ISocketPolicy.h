/*
 * ISocketPolicy.h
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

#ifndef ElwingISocketPolicy_h__
#define ElwingISocketPolicy_h__

BEGIN_ELW

enum SockFamily { };
enum SockType { };
enum SockProto { };
enum SockShutmode { };
enum SockFlag { };
enum SockAddr { };
enum SockHandle { };

class ISocketPolicy :
    public elw::IInterface
{
public:
    virtual void attach(
            HSOCKET hSocket
            ) = 0;

    virtual bool socket(
            SockFamily eFamily,
            SockType eType,
            SockProto eProtocol
            ) = 0;

    virtual int connect(
            const sockaddr* pAddr,
            socklen_t nSizeOfAddr
            ) = 0;

    virtual int bind(
            const sockaddr* pAddr,
            socklen_t nSizeOfAddr
            ) = 0;

    virtual HSOCKET accept(
            sockaddr* pAddr,
            socklen_t* pnSizeOfAddr
            ) = 0;

    virtual int listen(
            int iBacklog
            ) = 0;

    virtual int recv(
            char* pchBuff,
            size_t nSizeOf,
            SockFlag eFlags
            ) = 0;

    virtual int send(
            const char* pchBuff,
            size_t nSizeOf,
            SockFlag eFlags
            ) = 0;

    virtual int shutdown(
            SockShutmode sm
            ) = 0;

    virtual int close() = 0;

    virtual int setOption(
            int iLevel,
            int iOption,
            const void* pvValue,
            size_t nSizeOf
            ) = 0;

    virtual HSOCKET getSafeHandle() const = 0;
};

struct SockBase :
    public elw::IInterface
{
    typedef SockFamily      Family;
    typedef SockType        Type;
    typedef SockProto       Protocol;
    typedef SockShutmode    Shutmode;
    typedef SockFlag        Flag;
    typedef SockAddr        Address;
    typedef SockHandle      Handle;

    static const Family ipv4;
    static const Family ipv6;
    static const Family local;
    static const Family netlink;
    static const Family packet;

    static const Type stream;
    static const Type datagram;
    static const Type raw;
    static const Type rdm;
    static const Type seqpacket;

    static const Protocol tcp;
    static const Protocol udp;

    static const Shutmode r;
    static const Shutmode w;
    static const Shutmode rw;

    static const Flag none;
    static const Flag oob;
    static const Flag dontroute;
    static const Flag dontwait;
    static const Flag nosignal;
    static const Flag peek;
    static const Flag waitall;
    static const Flag trunc;
    static const Flag errqueue;

    static const Address any;
    static const Address loopback;

    static const Handle invalid;
};

#define ELW_SOCKET_POLICY_IMPL_KEYWORD ("elw::net::SocketPolicyImpl")
#define REGISTER_ELW_SOCKET_POLICY_IMPL(__impl) \
    REGISTER_CLASS(\
        ELW_SOCKET_POLICY_IMPL_KEYWORD,\
        ISocketPolicy,\
        __impl,\
        false,\
        ClassFactory::eStandart\
        )


END_ELW

#endif /* ElwingISocketPolicy_h__ */
