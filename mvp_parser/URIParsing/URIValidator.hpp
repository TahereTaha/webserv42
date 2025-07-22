#pragma once
#include "URI.hpp"

class URIValidator
{
    public:
        
        URIValidator();
        bool validate(URI* uri);

    private:

        bool validateScheme(const std::string& scheme);
        bool validateHost(const std::string& host, bool isHostIP);
        bool validatePort(const std::string& port, bool hasColonAfterHost);
        bool validatePath(const std::string& path);
        bool validateQuery(const std::string& query);
        

};