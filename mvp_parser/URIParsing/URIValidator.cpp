#include "URIValidator.hpp"
#include "StringUtils.hpp"
#include <sstream>
#include <cctype>
#include <cstring>

URIValidator::URIValidator(){}

bool URIValidator::validate(URI* uri)
{
    if (!uri->isAbsolute())
    {
        uri->setValid(validatePath(uri->getPath()));
        return uri->isValid();
    }
    else
    {
        // Check if there's a colon after host but no port
        bool validHostPort = !(uri->hasColonAfterHost() && uri->getPort().empty());
        
        uri->setValid(validateScheme(uri->getScheme()) &&
        validateHost(uri->getHost(), uri->isHostIP()) &&
        validatePort(uri->getPort(), uri->hasColonAfterHost()) &&
        validatePath(uri->getPath()) &&
        validateQuery(uri->getQuery()) &&
        validHostPort);
        
        return uri->isValid();
    }
}

bool URIValidator::validateScheme(const std::string& scheme)
{
    if (scheme != "http" && scheme != "https")
        return false;
    return true;
}

bool URIValidator::validateHost(const std::string& host, bool isHostIP)
{
    if (host.empty())
        return false;
    
    if (isHostIP)
    {
        std::vector<std::string> octets = StringUtils::split(host, '.');
        
        if (octets.size() != 4)
            return false;
        
        for (size_t i = 0; i < octets.size(); i++)
        {
            if (octets[i].empty())
                return false;
            
            for (size_t j = 0; j < octets[i].length(); j++)
            {
                if (octets[i][j] < '0' || octets[i][j] > '9')
                    return false;
            }
            
            std::istringstream iss(octets[i]);
            int value;
            iss >> value;
            
            if (iss.fail() || value < 0 || value > 255)
                return false;
            
            if (octets[i].length() > 1 && octets[i][0] == '0')
                return false;
        }
        
        return true;
    }
    else
    {
        //maybe add a check for label lenght (<= 63)
        if (strchr("-.", host[0]) || strchr("-.", host[host.size()-1]) || host.size() > 253)
            return false;
        char c;
        for (int i = 0; i < host.size(); i++)
        {
            c = tolower(host[i]);
            if ((c < 'a' || c > 'z') && (c < '0' || c > '9') && c != '-' && c != '.')
                return false;
            if (c == '.' && i < host.size() -1 && host[i + 1] == '.')
                return false;
        }
    }

    return true;
}

bool URIValidator::validatePort(const std::string& port, bool hasColonAfterHost)
{
    if (port.empty() && hasColonAfterHost)
        return false;
    if(port.empty())
        return true;
    std::istringstream iss(port);
    int portNum;

    if (!(iss >> portNum) || iss.peek() != EOF)
        return false;
    
    if (portNum < 1 || portNum > 65535)
        return false;
        
    return true;
}

bool URIValidator::validatePath(const std::string& path)
{
   
    return true;
}

bool URIValidator::validateQuery(const std::string& query)
{
    
    return true;
}