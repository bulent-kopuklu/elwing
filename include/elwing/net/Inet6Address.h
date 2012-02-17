/*
 * Inet6Address.h
 *
 *  Created on: Aug 24, 2011
 *      Author: Bulent.Kopuklu
 */

#ifndef ElwingInet6Address_h__
#define ElwingInet6Address_h__

BEGIN_ELW

class LIBELWING_API Inet6Address :
    public elw::InetAddress
{
    in6_addr m_addr;
    std::string m_strHost;
public:
    Inet6Address(const std::string& strName);
    Inet6Address(in6_addr addr, const std::string& strName = "");
public:

    std::string getHostName() const;
    std::string getCanonicalHostName() const;
    std::string getHostAddress() const;

    SockBase::Family getFamily() const;

    void getAddress(std::vector<uint8>& lst) const;

    std::string toString() const;
};

END_ELW

#endif /* ElwingInet6Address_h__ */
