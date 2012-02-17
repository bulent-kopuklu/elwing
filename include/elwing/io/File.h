/*
 * File.h
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

#ifndef ElwingFile_h__
#define ElwingFile_h__

BEGIN_ELW

class File
{
    elw::IFilePolicy* m_pImpl;
    int m_iType;
    std::string m_strPath;

public:
    File(const std::string& strPath);
    virtual ~File();

    bool exists() const;
    dword length() const;

    std::string getPath() const;
    std::string getParent() const;
    std::string getName() const;
    std::string getAbsolutePath() const;
    std::string getCanonicalPath() const;

    bool isAbsolutePath() const;
    bool isDirectory() const;
    bool isLink() const;
    bool isFile() const;
    bool isDevice() const;
    bool isHidden() const;

    bool canRead() const;
    bool canWrite() const;
    bool canExecute() const;

    bool setReadable(
            bool fReadable = true,
            bool fOwnerOnly = false
            );

    bool setWritable(
            bool fWritable = true,
            bool fOwnerOnly = false
            );

    bool setExecutable(
            bool fExecutable = true,
            bool fOwnerOnly = false
            );

    bool create();
    bool mkdir();
    bool mklink(
            const std::string& strTo
            );

    bool remove(
            bool fRecursive = false
            );

    bool move(
            const std::string& strDst
            );

    void list(
            std::vector<elw::File>& lst,
            const std::string& strFilter = ""
            );
    void list(
            std::vector<std::string>& lst,
            const std::string& strFilter = ""
            );

    std::string link() const;

    elw::SmartPtr<elw::IInputChannel> openInputChannel();
    elw::SmartPtr<elw::IOutputChannel> openOutputChannel();

protected:
    void init(const std::string& strPath);

public:
    static std::string getwd();
    static bool setwd(const std::string& str);
};

END_ELW

#endif /* ElwingFile_h__ */
