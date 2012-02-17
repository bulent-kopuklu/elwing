/*
 * FileChannel.h
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

#ifndef ElwingFileChannel_h__
#define ElwingFileChannel_h__

BEGIN_ELW

class FileChannel
{
protected:
    FILE* m_pfd;
public:
    FileChannel();
    virtual ~FileChannel();

    std::streamoff seek(
            std::streamoff lSeek,
            std::ios_base::seekdir pos
            );

    void close();

    bool isOpenned() const;

};

END_ELW

#endif /* ElwingFileChannel_h__ */
