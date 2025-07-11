#include "URI.hpp"

URI::URI()
{
    setScheme("");
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

std::string URI::getQuery()
{
    return _query;
}
