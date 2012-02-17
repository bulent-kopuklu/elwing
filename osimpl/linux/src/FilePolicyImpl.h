/*
 * FilePolicyImpl.h
 *
 *  Created on: Oct 10, 2011
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

#ifndef ElwingFilePolicyImpl_h__
#define ElwingFilePolicyImpl_h__

BEGIN_ELW

class FilePolicyImpl :
    public elw::IFilePolicy
{
public:
    std::string getRoot() const;
    std::string getSperator() const;

    int getType(
        const std::string& strPath
        );

    dword getLength(
            const std::string& strPath
            ) const;

    bool canRead(
            const std::string& strPath
            ) const;

    bool canWrite(
            const std::string& strPath
            ) const;

    bool canExecute(
            const std::string& strPath
            ) const;

    bool setReadable(
            const std::string& strPath,
            bool fReadable,
            bool fOwnerOnly
            );

    bool setWritable(
            const std::string& strPath,
            bool fWritable,
            bool fOwnerOnly
            );

    bool setExecutable(
            const std::string& strPath,
            bool fExecutable,
            bool fOwnerOnly
            );

    bool mkdir(
            const std::string& strPath
            );

    bool create(
            const std::string& strPath
            );

    bool mklink(
            const std::string& strSrc,
            const std::string& strDst
            );

    bool remove(
            const std::string& strPath
            );

    bool move(
            const std::string& strPath,
            const std::string& strDst
            );

    void readDir(
            const std::string& strPath,
            std::vector<std::string>& lst,
            const std::string& strFilter
            );

    bool readLink(
            const std::string& strPath,
            std::string& strLink
            );

    bool realPath(
            const std::string& strPath,
            std::string& strReal
            );
};

END_ELW

#endif /* ElwingFilePolicyImpl_h__ */
