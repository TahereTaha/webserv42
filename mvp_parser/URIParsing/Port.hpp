#pragma once

#include <string>

class Port
{
private:
    std::string _portString;
    int _portNumber;
    bool _isValid;

public:
    Port();
    Port(const std::string& portStr);
    ~Port();

    void setPortString(const std::string& portStr);
    bool validatePort();

    std::string getPortString() const;
    int getPortNumber() const;
    bool isValid() const;
};
