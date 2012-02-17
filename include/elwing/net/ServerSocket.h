/*
 * ServerSocket.h
 *
 *  Created on: Aug 22, 2011
 *      Author: Bulent.Kopuklu
 */

#ifndef ElwingServerSocket_h__
#define ElwingServerSocket_h__

BEGIN_ELW

class ServerSocket
{
    elw::ISocketPolicy* m_pImpl;
    SockBase::Family m_f;
public:
    ServerSocket();
    virtual ~ServerSocket();

public:
    bool create(
            SockBase::Family f = SockBase::ipv4,
            SockBase::Type t = SockBase::stream,
            SockBase::Protocol p = SockBase::tcp
            );

    bool bind(
            word wPort,
            int iBacklog = 5
            );

    bool bind(
            const elw::SmartPtr<elw::InetAddress>& rInetAddr,
            word wPort,
            int iBacklog = 5
            );

    bool bind(
            const elw::InetSocketAddress& rSockAddr,
            int iBacklog = 5
            );

    elw::Socket* accept();

    int close();

    HSOCKET getSafeHandle() const;
};



END_ELW

#endif /* ElwingServerSocket_h__ */
