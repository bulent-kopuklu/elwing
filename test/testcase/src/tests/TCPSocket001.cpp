/*
 * TCPSocket001.cpp
 *
 *  Created on: Oct 24, 2011
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
#include "TCPSocket001.h"

std::string TCPSocket001::getDescription() const
{
    return "elw::Socket() test.";
}

bool TCPSocket001::run()
{
    class ClientSocket :
        public elw::IRunnable
    {
        std::string m_strRemoteAddr;
        word m_wRemotePort;
        bool m_fSuccess;
    public:
        ClientSocket(const std::string& strRemoteAddr, word wRemotePort) :
            m_strRemoteAddr(strRemoteAddr),
            m_wRemotePort(wRemotePort),
            m_fSuccess(true)
        {
        }

    protected:
        int run()
        {
            elw::Socket sock;

            if (!sock.create())
                goto _ERROR;
            sock.connect(m_strRemoteAddr, m_wRemotePort);
            if (9 != sock.send("123456789", 9))
                goto _ERROR;
            if (1 != sock.send("0", 1))
                goto _ERROR;
            if (3 != sock.send("987", 3))
                goto _ERROR;
            if (2 != sock.send("65", 2))
                goto _ERROR;
            if (4 != sock.send("4321", 4))
                goto _ERROR;

            sock.shutdown(elw::SockBase::rw);
            sock.close();
            return 0;

        _ERROR:
            m_fSuccess = false;
            sock.shutdown(elw::SockBase::rw);
            sock.close();
            return 0;
        }

    public:
        bool isSuccess() const
        {
            return m_fSuccess;
        }
    } clnt("127.0.0.1", 22000);

    class ServerSocket :
        public elw::IRunnable
    {
        word m_wLinteningPort;
        bool m_fSuccess;
    public:
        ServerSocket(word wListeningPort) :
            m_wLinteningPort(wListeningPort),
            m_fSuccess(true)
        {
        }

    protected:
        int run()
        {
            elw::SmartPtr<elw::Socket> ptr;
            elw::ServerSocket serv;
            char sz[32] = { 0 };
            uint uTotalRead = 0;
            std::string str;

            if (!serv.create())
                goto _ERROR;
            if (!serv.bind(m_wLinteningPort))
                goto _ERROR;
            ptr = serv.accept();
            for ( ; ; )
            {
                int iRead = ptr->recv(sz + uTotalRead, sizeof(sz) - uTotalRead, elw::SockBase::none);
                if (iRead <= 0)
                    break;
                uTotalRead += iRead;
                if (uTotalRead >= sizeof(sz))
                    break;
            }

            ptr->close();
            serv.close();

            str = sz;
            if (str != "1234567890987654321")
                goto _ERROR;

            return 0;

         _ERROR:
            m_fSuccess = false;
            return 0;
        }
    public:
        bool isSuccess() const
        {
            return m_fSuccess;
        }
    } srv(22000);

    elw::Thread thrd0(&srv);
    thrd0.start();
    elw::Thread::sleep(250);
    elw::Thread thrd1(&clnt);
    thrd1.start();
    thrd1.join();
    thrd0.join();

    if (!clnt.isSuccess())
        return false;
    if (!srv.isSuccess())
        return false;
    return true;
}
