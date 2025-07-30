#include "Port.hpp"
#include <cstdlib>

Port::Port() : _portString(""), _portNumber(-1), _isValid(false)
{
}

Port::Port(const std::string& portStr) : _portString(portStr), _portNumber(-1), _isValid(false)
{
    validatePort();
}

Port::~Port()
{
}

void Port::setPortString(const std::string& portStr)
{
    _portString = portStr;
    validatePort();
}

bool Port::validatePort()
{
    if (_portString.empty())
    {
        _portNumber = -1;
        _isValid = false;
        return false;
    }

    // Check if port string contains only digits
    for (size_t i = 0; i < _portString.length(); ++i)
    {
        if (!isdigit(_portString[i]))
        {
            _portNumber = -1;
            _isValid = false;
            return false;
        }
    }

    // Convert to integer
    _portNumber = atoi(_portString.c_str());
    
    // Valid port range is 0-65535
    if (_portNumber < 0 || _portNumber > 65535)
    {
        _isValid = false;
        return false;
    }

    _isValid = true;
    return true;
}

std::string Port::getPortString() const
{
    return _portString;
}

int Port::getPortNumber() const
{
    return _portNumber;
}

bool Port::isValid() const
{
    return _isValid;
}
