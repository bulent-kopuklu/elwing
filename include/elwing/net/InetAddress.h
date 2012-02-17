/*
 * InetAddress.h
 *
 *  Created on: Aug 24, 2011
 *      Author: Bulent.Kopuklu
 */

#ifndef ElwingInetAddress_h__
#define ElwingInetAddress_h__

BEGIN_ELW

class LIBELWING_API InetAddress
{
public:
    virtual std::string getHostName() const = 0;
    virtual std::string getCanonicalHostName() const = 0;
    virtual std::string getHostAddress() const = 0;

    virtual elw::SockBase::Family getFamily() const = 0;

    virtual void getAddress(std::vector<uint8>& lst) const = 0;

    virtual std::string toString() const = 0;

public:
    static InetAddress* getByName(
        const std::string& strName,
        const std::string& strService = ""
        );

    static InetAddress* getByAddr(
            const sockaddr* pRawAddr
        );

    static bool getAllByName(
        const std::string& strName,
        std::vector<elw::SmartPtr<InetAddress> >& lst,
        const std::string& strService = ""
        );

    static InetAddress* getAnyLocalAddr();

protected:
    InetAddress() { };
};

END_ELW

#endif /* ElwingInetAddress_h__ */
