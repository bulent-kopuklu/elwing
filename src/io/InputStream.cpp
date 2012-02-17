/*
 * InputStream.cpp
 *
 *  Created on: Oct 14, 2011
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

class InputStreamBuffer :
    public std::streambuf
{
    IInputChannel& m_rReader;
    elw::Buffer m_buff;

//    typedef typename std::basic_streambuf<_TyCh, std::char_traits<_TyCh> > _MySB;
//    typedef typename _MySB::int_type int_type;
//    typedef typename _MySB::traits_type traits_type;

public:
    InputStreamBuffer(IInputChannel& rReader, int iInitialBufferSize = 4096) :
        m_rReader(rReader),
        m_buff(iInitialBufferSize)
    {
        reset();
    }

protected:
    void reset()
    {
        char* p = m_buff.ptr();
        setg(p, p+m_buff.sizeOf(), p+m_buff.sizeOf());
    }

    int_type underflow()
    {
        //  - eback() returns the beginning pointer for the input sequence
        //  - gptr() returns the next pointer for the input sequence
        //  - egptr() returns the end pointer for the input sequence

        if (gptr() != egptr())
            return traits_type::to_int_type(*gptr());
        std::streamsize nRead = m_rReader.read(eback(), egptr() - eback());
        if (0 >= nRead)
            return traits_type::eof();
        m_buff.count(nRead);
        std::streambuf::setg(eback(), eback(), eback() + nRead);
        return traits_type::to_int_type(*gptr());
    }

    std::streampos seekoff(std::streamoff off, std::ios::seekdir whence, std::ios::openmode mode)
    {
        if (!m_rReader.isOpenned() && !(mode & std::ios::in))
            return -1;
        if (whence == std::ios::cur)
            off -= static_cast<std::streamoff>(egptr() - gptr());
        reset();
        return m_rReader.seek(off, whence);
    }
};

InputStream::InputStream(elw::SmartPtr<elw::IInputChannel> ptrReader) :
    std::istream(new InputStreamBuffer(*ptrReader)),
    m_ptrReader(ptrReader)
{
}

InputStream::~InputStream()
{
    delete rdbuf();
}

bool InputStream::isOpened()
{
    return m_ptrReader->isOpenned();
}

void InputStream::close()
{
    return m_ptrReader->close();
}

END_ELW
