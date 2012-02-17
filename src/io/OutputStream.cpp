/*
 * OutputStream.cpp
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

class TransparentOutputStreamBuffer :
    public std::streambuf
{
    IOutputChannel& m_rWriter;
public:
    TransparentOutputStreamBuffer(IOutputChannel& rWriter) :
        m_rWriter(rWriter)
    {
    }

protected:
    std::streamsize xsputn(const std::streambuf::char_type* pchBuff, std::streamsize nSize)
    {
        return m_rWriter.write(pchBuff, nSize);
    }

    std::streambuf::pos_type seekoff(
            std::streambuf::off_type off, std::ios_base::seekdir pos,
            std::ios_base::openmode /*__mode*/ = std::ios_base::in | std::ios_base::out
            )
    {
        return m_rWriter.seek(off, pos);
    }
};


OutputStream::OutputStream(elw::SmartPtr<IOutputChannel> ptrWriter) :
    std::ostream(new TransparentOutputStreamBuffer(*ptrWriter)),
    m_ptrWriter(ptrWriter)
{
}

OutputStream::~OutputStream()
{
    delete rdbuf();
}

bool OutputStream::isOpened()
{
    return m_ptrWriter->isOpenned();
}

void OutputStream::close()
{
    return m_ptrWriter->close();
}

END_ELW
