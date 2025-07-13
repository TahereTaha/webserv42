#include "URI.hpp"

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
}

void URI::setNormalizedPath(std::string pathInput)
{
    _normalizedPath = pathInput;
}
void URI::setQuery(std::string queryInput)
{
    _query = queryInput;
}

void URI::setValid(bool status)
{
    _isValid = status;
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


std::vector<std::string> URI::split(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == delimiter)
        {
            if (!token.empty())
                tokens.push_back(token);
            token.clear();
        }
        else
        {
            token += str[i];
        }
    }
    
    if (!token.empty())
        tokens.push_back(token);
    
    return tokens;
}


std::string URI::normalizePath(const std::string& path)
{
    if (path.empty())
        return "";
    
    
    std::vector<std::string> segments = split(path, '/');
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
