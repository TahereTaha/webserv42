#include "URIParser.hpp"
#include <Kernel/mach/mach_types.h>

URIParser::URIParser(std::string input)
{
    _uri = URI();
    _input = input;
    parse();
}

URIParser::~URIParser(){}

std::string URIParser::getInput()
{
    return _input;
}

URI URIParser::getURI()
{
    return _uri;
}

void URIParser::parse()
{
    if (getInput().empty())
        return;
        
    std::string input = getInput();
    size_t position = 0;

    // Determine if the URI is absolute or relative
    bool isAbsolute = false;
    if (input[0] == '/' || input.find("://") != std::string::npos || 
        input.substr(0, 2) == "//")
    {
        isAbsolute = true;
    }
    _uri.setAbsolute(isAbsolute);

    bool isRelativePath = false;
    if (input[0] != '/' && input.find("://") == std::string::npos && 
        input.substr(0, 2) != "//" && input[0] != '?')
    {
        // This might be a relative path like "../path"
        size_t firstSlash = input.find("/");
        size_t firstColon = input.find(":");
        
        if (firstColon == std::string::npos || 
            (firstSlash != std::string::npos && firstColon > firstSlash))
        {
            isRelativePath = true;
            _uri.setPath(input); 
            _uri.setNormalizedPath(input);
            _uri.setValid(true);
            return;
        }
    }
    
    if (!isRelativePath)
    {
        parseScheme(input, position);
        parseHost(input, position);
        parsePort(input, position);
        parsePath(input, position);
        parseQuery(input, position);
    }
}

void URIParser::parseScheme(const std::string& input, size_t& position)
{
    if (input.length() >= position + 2 && input.substr(position, 2) == "//")
    {
        // This is a protocol-relative URL, no scheme
        position += 2;
        return;
    }
    
    size_t schemeEnd = input.find("://", position);
    
    if (schemeEnd != std::string::npos)
    {
        std::string scheme = input.substr(position, schemeEnd - position);
        _uri.setScheme(scheme);
        position = schemeEnd + 3; 
    }
}

void URIParser::parseUserAuth(const std::string& input, size_t& position)
{
    if (position >= input.length())
        return;
    
    size_t atPos = input.find("@", position);
    if (atPos != std::string::npos && atPos > position)
    {

        size_t colonPos = input.find(":", position);
        
        if (colonPos != std::string::npos && colonPos < atPos)
        {

            std::string username = input.substr(position, colonPos - position);
            std::string password = input.substr(colonPos + 1, atPos - colonPos - 1);
            
            _uri.setUsername(username);
            _uri.setPassword(password);
        }
        else
        {
            // Only username, no password
            std::string username = input.substr(position, atPos - position);
            _uri.setUsername(username);
        }
        
        position = atPos + 1;
    }
}

void URIParser::parseHost(const std::string& input, size_t& position)
{
    if (position >= input.length())
        return; // No host
    if (input[position] == '/' || input[position] == '?' || input[position] == '#')
        return; // No host

    parseUserAuth(input, position);
    
    size_t hostEnd = input.find_first_of(":/?#", position);
    if (hostEnd == std::string::npos)
        hostEnd = input.length();
    std::string host = input.substr(position, hostEnd - position);
    _uri.setHost(host);
    
    // Check if the host is an IPv4 address
    bool isIPv4 = isIPv4Address(host);
    _uri.setHostIP(isIPv4);
    
    position = hostEnd;
}

void URIParser::parseComponent(const std::string& input, size_t& position, 
                            char startChar, const std::string& endChars,
                            bool skipStartChar, void (URI::*setter)(std::string))
{
    if (position >= input.length())
        return; // No component

    if (input[position] == startChar)
    {
        if (skipStartChar)
            position++;
        size_t endPos = input.find_first_of(endChars, position);
        
        if (endPos == std::string::npos)
            endPos = input.length();
    
        if (endPos > position)
        {
            std::string component = input.substr(position, endPos - position);
            (_uri.*setter)(component);
            position = endPos;
        }
    }
}

void URIParser::parsePort(const std::string& input, size_t& position)
{
    parseComponent(input, position, ':', "/?#", true, &URI::setPort);
}

void URIParser::parsePath(const std::string& input, size_t& position)
{
    parseComponent(input, position, '/', "?#", false, &URI::setPath);
}

void URIParser::parseQuery(const std::string& input, size_t& position)
{
    parseComponent(input, position, '?', "#", true, &URI::setQuery);
}

bool URIParser::isIPv4Address(const std::string& host)
{
    // IPv4 address format: a.b.c.d where a,b,c,d are numbers between 0-255
    size_t start = 0;
    int octetCount = 0;
    
    for (size_t i = 0; i <= host.length(); ++i)
    {
        if (i == host.length() || host[i] == '.')
        {
            // We've reached the end of an octet
            if (i == start) // Empty octet
                return false;
            
            // Extract the octet
            std::string octet = host.substr(start, i - start);
            
            // Check if the octet contains only digits
            for (size_t j = 0; j < octet.length(); ++j)
            {
                if (octet[j] < '0' || octet[j] > '9')
                    return false;
            }
            
            // Convert octet to integer and check range
            int value = 0;
            for (size_t j = 0; j < octet.length(); ++j)
            {
                // Check for leading zeros (except for 0 itself)
                if (j == 0 && octet[j] == '0' && octet.length() > 1)
                    return false;
                
                value = value * 10 + (octet[j] - '0');
            }
            
            if (value < 0 || value > 255)
                return false;
            
            octetCount++;
            start = i + 1;
        }
    }
    
    // A valid IPv4 address must have exactly 4 octets
    return octetCount == 4;
}

