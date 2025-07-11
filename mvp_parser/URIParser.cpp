#include "URIParser.hpp"
#include <Kernel/mach/mach_types.h>

URIParser::URIParser(std::string input)
{
    _uri = URI();
    _input = input;
    parse(); // Parse the URI when the object is created
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

    parseScheme(input, position);
    parseHost(input, position);
    parsePort(input, position);
    parsePath(input, position);
    parseQuery(input, position);
}

void URIParser::parseScheme(const std::string& input, size_t& position)
{
    // Scheme is special because it ends with "://" instead of a single character
    size_t schemeEnd = input.find("://", position);
    
    if (schemeEnd != std::string::npos)
    {
        std::string scheme = input.substr(position, schemeEnd - position);
        _uri.setScheme(scheme);
        position = schemeEnd + 3; // Skip past "://"
    }
}

void URIParser::parseHost(const std::string& input, size_t& position)
{
    // Check if we're already at the end of the string
    if (position >= input.length())
        return; // No host
    
    // Check if we're already at a delimiter (/, ?, #)
    if (input[position] == '/' || input[position] == '?' || input[position] == '#')
        return; // No host
    
    // For host, we don't have a specific start character, so we handle it differently
    // Find the end of the host
    size_t hostEnd = input.find_first_of(":/?#", position);
    if (hostEnd == std::string::npos)
        hostEnd = input.length();
    
    // Extract the host
    std::string host = input.substr(position, hostEnd - position);
    _uri.setHost(host);
    position = hostEnd;
}

// Template method for parsing URI components
void URIParser::parseComponent(const std::string& input, size_t& position, 
                            char startChar, const std::string& endChars,
                            bool skipStartChar, void (URI::*setter)(std::string))
{
    // Check if we're at the end of the string
    if (position >= input.length())
        return; // No component
    
    // Check if we have the component (starts with startChar)
    if (input[position] == startChar)
    {
        // Skip the start character if needed
        if (skipStartChar)
            position++;
        
        // Find the end of the component
        size_t endPos = input.find_first_of(endChars, position);
        
        if (endPos == std::string::npos)
            endPos = input.length();
        
        // Extract the component
        if (endPos > position)
        {
            std::string component = input.substr(position, endPos - position);
            (_uri.*setter)(component);
            position = endPos;
        }
    }
    // If there's no component (doesn't start with startChar), do nothing
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

