

/*
 * URI.h
 *
 *  Created on : 2011/08/19  1:11
 *      Author : Bulent Kopuklu
 *      Contact: bulent.kopuklu@gmail.com
 */


#ifndef ElwingURI_h__
#define ElwingURI_h__

BEGIN_ELW

class LIBELWING_API URI
{
    std::string m_strURI;
    std::string m_strScheme;
    std::string m_strUserInfo;
    std::string m_strHost;
    word        m_wPort;
    std::string m_strPath;
    std::string m_strQuery;
    std::string m_strFragment;

public:
    URI(void);
    URI(const std::string& strURI);

    URI& operator =(const std::string& strURI);

    virtual ~URI(void);

public:
    std::string getScheme() const
    {
        return m_strScheme;
    }

    std::string getUserInfo() const
    {
        return m_strUserInfo;
    }

    std::string getHost() const
    {
        return m_strHost;
    }

    std::string getPath() const
    {
        return m_strPath;
    }

    std::string getQuery() const
    {
        return m_strQuery;
    }

    std::string getFragment() const
    {
        return m_strFragment;
    }

    word getPort() const
    {
        return m_wPort;
    }

    std::string toString() const;

protected:
    bool parse(const std::string& strURI);
    bool parseHierarchical(std::string& str);
    bool parseAuthority(std::string& str);

    void clear();
};

END_ELW

#endif // ElwingURI_h__
