/*
 * FileInputChannel.h
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

#ifndef ElwingFileInputChannel_h__
#define ElwingFileInputChannel_h__

BEGIN_ELW

class FileInputChannel :
    public elw::IInputChannel
{
    FILE* m_pfd;
public:
    FileInputChannel(
            const elw::File& f
            );

    std::streamsize read(
            char* pchBuff, std::streamsize nSize
            );

    std::streamoff seek(
            std::streamoff off,
            std::ios::seekdir origin
            );

    void close();

    bool isOpenned() const;
};

END_ELW

#endif /* ElwingFileInputChannel_h__ */
