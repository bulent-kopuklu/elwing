/*
 * Inet4Address.h
 *
 *  Created on: Aug 24, 2011
 *      Author: Bulent.Kopuklu
 */

#ifndef ElwingInet4Address_h__
#define ElwingInet4Address_h__

BEGIN_ELW

class LIBELWING_API Inet4Address :
    public elw::InetAddress
{
    in_addr m_addr;
    std::string m_strHost;
public:
    Inet4Address();
    Inet4Address(const std::string& strName);
    Inet4Address(in_addr addr, const std::string& strName = "");

public:
    std::string getHostName() const;
    std::string getCanonicalHostName() const;
    std::string getHostAddress() const;

    operator in_addr() const { return m_addr; }

    SockBase::Family getFamily() const;

    void getAddress(std::vector<uint8>& lst) const;

    std::string toString() const;
};

END_ELW

#endif /* ElwingInet4Address_h__ */
