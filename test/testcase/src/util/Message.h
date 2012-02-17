/*
 * Message.h
 *
 *  Created on: Oct 6, 2011
 *      Author: altar
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#define MSGCNT  100000

class Message
{
    dword m_dwSender;
    dword m_dwParam;
public:
    Message(dword dwSender, dword dwParam) :
        m_dwSender(dwSender),
        m_dwParam(dwParam)
    {
    }

    dword getSender() const
    {
        return m_dwSender;
    }

    dword getParam() const
    {
        return m_dwParam;
    }
};

#endif /* MESSAGE_H_ */
