/*
 * SocketBase.h
 *
 *  Created on: Aug 25, 2011
 *      Author: Bulent.Kopuklu
 */

#ifndef ElwingSocketBase_h__
#define ElwingSocketBase_h__

#include <os/net/SocketImpl.h>

BEGIN_ELW

template <class _TySockBaseImpl>
class BasicSockBase :
    public _TySockBaseImpl
{
protected:
    BasicSockBase() { };
};

typedef BasicSockBase<elw::SockBaseImpl> SockBase;

END_ELW

#endif /* ElwingSocketBase_h__ */
