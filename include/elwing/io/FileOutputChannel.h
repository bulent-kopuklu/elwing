/*
 * FileOutputChannel.h
 *
 *  Created on: Sep 27, 2011
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

#ifndef ElwingFileOutputChannel_h__
#define ElwingFileOutputChannel_h__

BEGIN_ELW

class FileOutputChannel :
    public elw::IOutputChannel
{
    FILE* m_pfd;
public:
    FileOutputChannel(elw::File& f);

    std::streamsize write(
            const char* pchBuff,
            std::streamsize nSize
            );

    bool isOpenned() const;

    void close();

    std::streamoff seek(
            std::streamoff lSeek,
            std::ios_base::seekdir pos
            );
};

END_ELW

#endif /* ElwingFileOutputChannel_h__ */
