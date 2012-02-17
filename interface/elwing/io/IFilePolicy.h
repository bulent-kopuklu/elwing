/*
 * IFilePolicy.h
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

#ifndef ElwingIFilePolicy_h__
#define ElwingIFilePolicy_h__

BEGIN_ELW

namespace iobase
{
    enum Type
    {
        file        = 0x01,
        dir         = 0x02,
        dev         = 0x03,

        headen      = 0xe0,
        link        = 0xf0,
    };
}

class IFilePolicy :
    public elw::IInterface
{
public:
    virtual std::string getRoot() const = 0;
    virtual std::string getSperator() const = 0;

    virtual int getType(
            const std::string& strPath
            ) = 0;

    virtual dword getLength(
            const std::string& strPath
            ) const = 0;

    virtual bool canRead(
            const std::string& strPath
            ) const = 0;

    virtual bool canWrite(
            const std::string& strPath
            ) const = 0;

    virtual bool canExecute(
            const std::string& strPath
            ) const = 0;

    virtual bool setReadable(
            const std::string& strPath,
            bool fReadable,
            bool fOwner
            ) = 0;

    virtual bool setWritable(
            const std::string& strPath,
            bool fWritable,
            bool fOwner
            ) = 0;

    virtual bool setExecutable(
            const std::string& strPath,
            bool fExecutable,
            bool fOwner
            ) = 0;

    virtual bool mkdir(
            const std::string& strPath
            ) = 0;

    virtual bool create(
            const std::string& strPath
            ) = 0;

    virtual bool mklink(
            const std::string& strSrc,
            const std::string& strDst
            ) = 0;

    virtual bool remove(
            const std::string& strPath
            ) = 0;

    virtual bool move(
            const std::string& strPath,
            const std::string& strDst
            ) = 0;

    virtual void readDir(
            const std::string& strPath,
            std::vector<std::string>& lst,
            const std::string& strFilter
            ) = 0;

    virtual bool readLink(
            const std::string& strPath,
            std::string& strLink
            ) = 0;

    virtual bool realPath(
            const std::string& strPath,
            std::string& strReal
            ) = 0;
};

std::string GetWorkingDirectory();
bool SetWorkingDirectory(const std::string& str);

#define ELW_FILE_POLICY_IMPL_KEYWORD ("elw::io::FilePolicyImpl")
#define REGISTER_ELW_FILE_POLICY_IMPL(__impl) \
    REGISTER_CLASS(\
        ELW_FILE_POLICY_IMPL_KEYWORD,\
        IFilePolicy,\
        __impl,\
        false,\
        ClassFactory::eSingelton\
        )

END_ELW

#endif /* ElwingIFilePolicy_h__ */
