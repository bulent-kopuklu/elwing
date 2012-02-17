/*
 * ielwing.h
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

#ifndef ielwing_h__
#define ielwing_h__

#include <elwing/elwstd.h>
#include <elwing/elwtypes.h>

#include <elwing/lang/IInterface.h>
#include <elwing/lang/Exception.h>

#include <elwing/thread/IThreadPolicy.h>
#include <elwing/thread/IMutexPolicy.h>
#include <elwing/thread/ISpinLockPolicy.h>
#include <elwing/thread/IConditionPolicy.h>
#include <elwing/thread/IAtomicIntegerPolicy.h>
#include <elwing/io/IFilePolicy.h>
#include <elwing/net/ISocketPolicy.h>
#include <elwing/system/ISharedLibraryPolicy.h>

BEGIN_ELW

elw::IInterface* CreatePolicyImpl(
        const std::string& strName
        );

END_ELW


#endif /* ielwing_h__ */
