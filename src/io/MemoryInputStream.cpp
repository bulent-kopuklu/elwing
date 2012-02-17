/*
 * MemoryInputStream.cpp
 *
 *  Created on: Dec 20, 2011
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

BEGIN_ELW

class MemoryInputStreamBuffer :
    public std::streambuf
{
    elw::SmartPtr<elw::Buffer> m_ptrBuff;
protected:
    MemoryInputStreamBuffer(const elw::SmartPtr<elw::Buffer>& ptrBuff) :
        m_ptrBuff(ptrBuff)
    {
        setg(ptrBuff->ptr(), ptrBuff->ptr(), ptrBuff->ptr()+ptrBuff->length());
    }

//    MemoryInputStreamBuffer(const MemoryInputStreamBuffer& that) :
//        m_ptrBuff(that.m_ptrBuff)
//    {
//        setg(that.eback(), that.egptr(), that.epptr());
//    }

    int_type underflow()
    {
        return traits_type::eof();
    }

    void dump()
    {
        int iLength = egptr() - gptr();
        for (int i = 0; i < iLength; ++i)
        {
            std::cout << std::hex << (int)*(gptr() + i) << ":";
        }
        std::cout << std::dec << std::endl;
    }

    friend class MemoryInputStream;
};

MemoryInputStream::MemoryInputStream(const elw::Buffer& rBuffer) :
    std::istream(new MemoryInputStreamBuffer(elw::SmartPtr<elw::Buffer>(&rBuffer, 2)))
{
}

MemoryInputStream::MemoryInputStream(const elw::SmartPtr<elw::Buffer>& ptrBuffer) :
    std::istream(new MemoryInputStreamBuffer(ptrBuffer))
{
}

MemoryInputStream::~MemoryInputStream()
{
    delete rdbuf();
}

void MemoryInputStream::dump()
{
    ((MemoryInputStreamBuffer*)rdbuf())->dump();
}

END_ELW
