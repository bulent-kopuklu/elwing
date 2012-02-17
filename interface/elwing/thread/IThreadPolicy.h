/*
 * IThread.h
 *
 *  Created on: Sep 29, 2011
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

#ifndef ElwingIThread_h__
#define ElwingIThread_h__

BEGIN_ELW

class IRunnable :
    public elw::IInterface
{
public:
    virtual int run() = 0;
};

class IThreadPolicy :
    public elw::IInterface
{
public:
    virtual bool    start(elw::IRunnable& rRunnable) = 0;
    virtual bool    kill() = 0;
    virtual bool    join() = 0;
//    virtual void    setPriority(EPriority ePriority) = 0;
    virtual dword   getId() const = 0;

//    virtual _TyHandle   getHandle() const = 0;
};

void    Sleep(dword dwMiliseconds);
dword   SelfId(void);
dword   Tick(void);
void    Yield(void);

#define ELW_THREAD_POLICY_IMPL_KEYWORD   ("elw::thread::ThreadPolicyImpl")
#define REGISTER_ELW_THREAD_POLICY_IMPL(__impl) \
    REGISTER_CLASS(\
        ELW_THREAD_POLICY_IMPL_KEYWORD,\
        IThreadPolicy,\
        __impl,\
        false,\
        ClassFactory::eStandart\
        )

END_ELW

#endif /* ElwingIThread_h__ */
