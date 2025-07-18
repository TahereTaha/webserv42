#pragma once

#include "URI.hpp"

class URIParser
{
    private:
        URI _uri;
        std::string _input;

        //helper methods
        void parseScheme(const std::string& input, size_t& position);
        void parseUserAuth(const std::string& input, size_t& position);
        void parseHost(const std::string& input, size_t& position);
        void parsePort(const std::string& input, size_t& position);
        void parsePath(const std::string& input, size_t& position);
        void parseQuery(const std::string& input, size_t& position);
        
        void parseComponent(const std::string& input, size_t& position, 
                          char startChar, const std::string& endChars,
                          bool skipStartChar, void (URI::*setter)(std::string));
        
        bool isIPv4Address(const std::string& host);

    public:
        URIParser(std::string input);
        ~URIParser();

        void parse();
        std::string getInput();
        URI getURI();

};