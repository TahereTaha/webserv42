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
    setHasColonAfterHost(false);
}

URI::~URI(){}

void URI::setScheme(const std::string& schemeInput)
{
    _scheme = schemeInput;
}

void URI::setUsername(const std::string& usernameInput)
{
    _username = usernameInput;
}

void URI::setPassword(const std::string& passwordInput)
{
    _password = passwordInput;
}

void URI::setHost(const std::string& hostInput)
{
    _host.setHostname(hostInput);
}

void URI::setHost(const Host& host)
{
    _host = host;
}

void URI::setPort(const std::string& portInput)
{
    _port.setPortString(portInput);
}

void URI::setPort(const Port& port)
{
    _port = port;
}

void URI::setPath(const std::string& pathInput)
{
    _path.setPath(pathInput);
}

void URI::setPath(const Path& path)
{
    _path = path;
}

void URI::setNormalizedPath(const std::string& pathInput)
{
    _path.setNormalizedPath(pathInput);
}

void URI::setQuery(const std::string& queryInput)
{
    _query = queryInput;
    _decodedQuery = percentDecode(queryInput);
}

void URI::setValid(bool status)
{
    _isValid = status;
}

void URI::setHasColonAfterHost(bool hasColon)
{
    _hasColonAfterHost = hasColon;
}

std::string URI::getScheme() const
{
    return _scheme;
}

std::string URI::getUsername() const
{
    return _username;
}

std::string URI::getPassword() const
{
    return _password;
}

Host URI::getHost() const
{
    return _host;
}

std::string URI::getHostString() const
{
    return _host.getHostname();
}

bool URI::isHostIP() const
{
    return _host.isIP();
}

Port URI::getPort() const
{
    return _port;
}

std::string URI::getPortString() const
{
    return _port.getPortString();
}

int URI::getPortNumber() const
{
    return _port.getPortNumber();
}

Path URI::getPath() const
{
    return _path;
}

std::string URI::getPathString() const
{
    return _path.getPath();
}

std::string URI::getNormalizedPath() const
{
    return _path.getNormalizedPath();
}

std::string URI::getDecodedPath() const
{
    return _path.getDecodedPath();
}

bool URI::isAbsolute() const
{
    return _path.isAbsolute();
}

std::string URI::getQuery() const
{
    return _query;
}

std::string URI::getDecodedQuery() const
{
    return _decodedQuery;
}

bool URI::hasColonAfterHost() const
{
    return _hasColonAfterHost;
}

bool URI::isValid() const
{
    return _isValid;
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