#pragma once

#include <string>

class Host
{
private:
    std::string _hostname;
    bool _isIP;

public:
    Host();
    Host(const std::string& hostname);
    ~Host();

    void setHostname(const std::string& hostname);
    void setIsIP(bool isIP);

    std::string getHostname() const;
    bool isIP() const;
};
