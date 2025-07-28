#include "Host.hpp"

Host::Host() : _hostname(""), _isIP(false)
{
}

Host::Host(const std::string& hostname) : _hostname(hostname), _isIP(false)
{
}

Host::~Host()
{
}

void Host::setHostname(const std::string& hostname)
{
    _hostname = hostname;
}

void Host::setIsIP(bool isIP)
{
    _isIP = isIP;
}

std::string Host::getHostname() const
{
    return _hostname;
}

bool Host::isIP() const
{
    return _isIP;
}
