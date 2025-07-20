#include "URI.hpp"
#include "StringUtils.hpp"

URI::URI()
{
    setScheme("");
    setUsername("");
    setPassword("");
    setHost("");
    setPort("");
    setPath("");
    setQuery("");
    setValid(false);
    setHostIP(false);
    setAbsolute(false);
    setHasColonAfterHost(false);
}

URI::~URI(){}

void URI::setScheme(std::string schemeInput)
{
    _scheme = schemeInput;
}

void URI::setUsername(std::string usernameInput)
{
    _username = usernameInput;
}

void URI::setPassword(std::string passwordInput)
{
    _password = passwordInput;
}

void URI::setHost(std::string hostInput)
{
    _host = hostInput;
}
void URI::setPort(std::string portInput)
{
    _port = portInput;
}
void URI::setPath(std::string pathInput)
{
    _path = pathInput;
    _normalizedPath = normalizePath(pathInput);
    _decodedPath = percentDecode(_normalizedPath);
}

void URI::setNormalizedPath(std::string pathInput)
{
    _normalizedPath = pathInput;
}
void URI::setQuery(std::string queryInput)
{
    _query = queryInput;
    _decodedQuery = percentDecode(queryInput);
}

void URI::setValid(bool status)
{
    _isValid = status;
}

void URI::setHostIP(bool isIP)
{
    _isHostIP = isIP;
}

void URI::setAbsolute(bool isAbsolute)
{
    _isAbsolute = isAbsolute;
}

void URI::setHasColonAfterHost(bool hasColon)
{
    _hasColonAfterHost = hasColon;
}

std::string URI::getScheme()
{
    return _scheme;
}

std::string URI::getUsername()
{
    return _username;
}

std::string URI::getPassword()
{
    return _password;
}

std::string URI::getHost()
{
    return _host;
}

std::string URI::getPort()
{
    return _port;
}

std::string URI::getPath()
{
    return _path;
}

std::string URI::getNormalizedPath()
{
    return _normalizedPath;
}

std::string URI::getQuery()
{
    return _query;
}

std::string URI::getDecodedPath()
{
    return _decodedPath;
}

std::string URI::getDecodedQuery()
{
    return _decodedQuery;
}

bool URI::isHostIP()
{
    return _isHostIP;
}

bool URI::isAbsolute()
{
    return _isAbsolute;
}

bool URI::hasColonAfterHost()
{
    return _hasColonAfterHost;
}

bool URI::isValid()
{
    return _isValid;
}



std::string URI::normalizePath(const std::string& path)
{
    if (path.empty())
        return "";
    
    
    std::vector<std::string> segments = StringUtils::split(path, '/');
    std::vector<std::string> normalizedSegments;
    
    for (size_t i = 0; i < segments.size(); i++)
    {
        const std::string& segment = segments[i];
        
        if (segment.empty() || segment == ".")
        {
            
            continue;
        }
        else if (segment == "..")
        {
            
            if (!normalizedSegments.empty())
                normalizedSegments.pop_back();
        }
        else
        {
            normalizedSegments.push_back(segment);
        }
    }
    
    std::string normalizedPath;
    
    if (!path.empty() && path[0] == '/')
        normalizedPath = "/";
    
    for (size_t i = 0; i < normalizedSegments.size(); i++)
    {
        if (i > 0)
            normalizedPath += "/";
        normalizedPath += normalizedSegments[i];
    }
    
    if (path.length() > 1 && path[path.length() - 1] == '/' && !normalizedPath.empty() && normalizedPath[normalizedPath.length() - 1] != '/')
        normalizedPath += "/";
    
    return normalizedPath;
}



std::string URI::percentDecode(const std::string& encoded)
{
    std::string decoded;
    for (size_t i = 0; i < encoded.length(); i++)
    {
        if (encoded[i] == '%' && i + 2 < encoded.length())
        {
            int digit1 = StringUtils::hexToDecimal(encoded[i+1]);
            int digit2 = StringUtils::hexToDecimal(encoded[i+2]);
            
            if (digit1 != -1 && digit2 != -1)
            {
                char decodedChar = static_cast<char>((digit1 << 4) | digit2);
                decoded += decodedChar;
                i += 2; 
            }
            else
            {
                decoded += encoded[i];
            }
        }
        else if (encoded[i] == '+')
        {
            decoded += ' ';
        }
        else
        {
            decoded += encoded[i];
        }
    }
    return decoded;
}