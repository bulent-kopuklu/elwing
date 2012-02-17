/*
 * InetSocketAddress.h
 *
 *  Created on: Aug 24, 2011
 *      Author: Bulent.Kopuklu
 */

#ifndef ElwingInetSocketAddress_h__
#define ElwingInetSocketAddress_h__


BEGIN_ELW

class LIBELWING_API InetSocketAddress :
    public elw::ISocketAddress
{
    elw::SmartPtr<InetAddress> m_ptrAddr;
    union myinaddr
    {
        sockaddr_in  v4;
        sockaddr_in6 v6;
    }
    m_addr;

//public:
//    enum
//    {
//        SIZEOF = sizeof(myinaddr)
//    };
public:
    InetSocketAddress(word wPort);
    InetSocketAddress(const std::string& strAddr);
    InetSocketAddress(const std::string& str, word wPort);
    InetSocketAddress(const elw::SmartPtr<InetAddress>& addr, word wPort);
    InetSocketAddress(const sockaddr* pRawAddr);
    InetSocketAddress(const InetSocketAddress& rThat);

    const elw::SmartPtr<InetAddress> getAddress() const;
    word getPort() const;

    const sockaddr* getSockAddr() const;
    size_t          getSizeOfAddr() const;

    std::string toString() const;

protected:
    void init(const elw::SmartPtr<InetAddress>& addr, word wPort);
};

END_ELW

#endif /* ElwingInetSocketAddress_h__ */
