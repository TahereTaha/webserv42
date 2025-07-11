#pragma once

#include <iostream>

class URI
{
    private:
        std::string _scheme;
        std::string _host;
        std::string _port;
        std::string _path;
        std::string _query;

        bool _isValid;
        //make it canonical

    public:
        URI();
        ~URI();
        
        void setScheme(std::string schemeInput);
        void setHost(std::string hostInput);
        void setPort(std::string portInput);
        void setPath(std::string pathInput);
        void setQuery(std::string queryInput);
        
        void setValid(bool status);

        std::string getScheme();
        std::string getHost();
        std::string getPort();
        std::string getPath();
        std::string getQuery();

};