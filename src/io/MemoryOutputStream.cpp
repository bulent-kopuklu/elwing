/*
 * MemoryOutputStream.cpp
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

class MemoryOutputStreamBuffer :
    std::streambuf
{
    int m_iBlockSize;
    elw::SmartPtr<elw::Buffer> m_ptrBuff;
    int m_iResizeCnt;
protected:
    MemoryOutputStreamBuffer(int iInitialBufferSize) :
        m_iBlockSize((iInitialBufferSize > 8 ? iInitialBufferSize : 8)),
        m_ptrBuff(new elw::Buffer(m_iBlockSize)),
        m_iResizeCnt(0)
    {
        setp(m_ptrBuff->ptr(), m_ptrBuff->ptr() + m_ptrBuff->sizeOf());
    }


    int_type overflow(int_type ch)
    {
        std::streamsize nCrnt = m_ptrBuff->sizeOf();
        if (!m_ptrBuff->resize(m_ptrBuff->sizeOf()+m_iBlockSize))
            return traits_type::eof();
        setp(m_ptrBuff->ptr() + nCrnt, m_ptrBuff->ptr() + m_ptrBuff->sizeOf());
        *pptr() = traits_type::to_char_type(ch);
        setp(m_ptrBuff->ptr() + nCrnt + 1, m_ptrBuff->ptr() + m_ptrBuff->sizeOf());
        ++m_iResizeCnt;
        return ch;

    }

    int sync()
    {
        std::streamsize nCnt = static_cast<std::streamsize>(pptr() - pbase());
        if (m_iResizeCnt > 0)
        {
            nCnt += m_iBlockSize*m_iResizeCnt;
            nCnt += 1; // overflow char
        }
        m_ptrBuff->count(nCnt);

        return 0;
    }

    elw::SmartPtr<elw::Buffer> getBuffer()
    {
        return m_ptrBuff;
    }

    void reset()
    {
        setp(m_ptrBuff->ptr(), m_ptrBuff->ptr() + m_ptrBuff->sizeOf());
        m_ptrBuff->reset();
    }

    friend class MemoryOutputStream;
};

MemoryOutputStream::MemoryOutputStream(int iInitialBufferSize) :
    std::ostream(new MemoryOutputStreamBuffer(iInitialBufferSize))
{
}

MemoryOutputStream::~MemoryOutputStream()
{
    delete rdbuf();
}

elw::SmartPtr<elw::Buffer> MemoryOutputStream::getBuffer()
{
    return ((MemoryOutputStreamBuffer*)rdbuf())->getBuffer();
}

void MemoryOutputStream::reset()
{
    return ((MemoryOutputStreamBuffer*)rdbuf())->reset();
}

END_ELW
