/*
 * ISocketAddress.h
 *
 *  Created on: Aug 24, 2011
 *      Author: Bulent.Kopuklu
 */

#ifndef ElwingISocketAddress_h__
#define ElwingISocketAddress_h__

BEGIN_ELW

class ISocketAddress :
    public elw::IInterface
{
public:
    virtual const sockaddr* getSockAddr() const = 0;
    virtual size_t getSizeOfAddr() const= 0;
};

END_ELW

#endif /* ElwingISocketAddress_h__ */
