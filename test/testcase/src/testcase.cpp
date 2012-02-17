/*
 * testcase.cpp
 *
 *  Created on: Oct 4, 2011
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
#include "tests/Sleep001.h"
#include "tests/Thread001.h"
#include "tests/Runnable001.h"
#include "tests/AtomicInteger001.h"
#include "tests/AtomicCounter001.h"
#include "tests/SmartPointer001.h"
#include "tests/SmartPointer002.h"
#include "tests/SmartPointer003.h"
#include "tests/MemoryStream001.h"
#include "tests/MemoryStream002.h"
#include "tests/MemoryStream003.h"
#include "tests/ThreadQueue001.h"
#include "tests/ThreadQueue002.h"
#include "tests/ThreadQueue003.h"
#include "tests/ThreadQueue004.h"
#include "tests/ThreadPool001.h"
#include "tests/File001.h"
#include "tests/File002.h"
#include "tests/File003.h"
#include "tests/File004.h"
#include "tests/File005.h"
#include "tests/File006.h"
#include "tests/InetAddress001.h"
#include "tests/TCPSocket001.h"
#include "tests/URI001.h"

void Testcases::load()
{
    elw::ClassFactory::Registrar<ITest, Sleep001>(                  "Test001");
    elw::ClassFactory::Registrar<ITest, Thread001>(                 "Test002");
    elw::ClassFactory::Registrar<ITest, Runnable001>(               "Test003");
    elw::ClassFactory::Registrar<ITest, AtomicInteger001>(          "Test004");
    elw::ClassFactory::Registrar<ITest, AtomicCounter001>(          "Test005");
    elw::ClassFactory::Registrar<ITest, SmartPointer001>(           "Test006");
    elw::ClassFactory::Registrar<ITest, SmartPointer002>(           "Test007");
    elw::ClassFactory::Registrar<ITest, SmartPointer003>(           "Test008");
    elw::ClassFactory::Registrar<ITest, MemoryStream001>(           "Test009");
    elw::ClassFactory::Registrar<ITest, MemoryStream002>(           "Test010");
    elw::ClassFactory::Registrar<ITest, MemoryStream003>(           "Test011");
    elw::ClassFactory::Registrar<ITest, ThreadQueue001>(            "Test012");
    elw::ClassFactory::Registrar<ITest, ThreadQueue002>(            "Test013");
    elw::ClassFactory::Registrar<ITest, ThreadQueue003>(            "Test014");
    elw::ClassFactory::Registrar<ITest, ThreadQueue004>(            "Test015");
    elw::ClassFactory::Registrar<ITest, ThreadPool001>(             "Test016");
    elw::ClassFactory::Registrar<ITest, File001>(                   "Test017");
    elw::ClassFactory::Registrar<ITest, File002>(                   "Test018");
    elw::ClassFactory::Registrar<ITest, File003>(                   "Test019");
    elw::ClassFactory::Registrar<ITest, File004>(                   "Test020");
    elw::ClassFactory::Registrar<ITest, File005>(                   "Test021");
    elw::ClassFactory::Registrar<ITest, File006>(                   "Test022");
    elw::ClassFactory::Registrar<ITest, InetAddress001>(            "Test023");
    elw::ClassFactory::Registrar<ITest, TCPSocket001>(              "Test024");
    elw::ClassFactory::Registrar<ITest, URI001>(                    "Test025");

}
