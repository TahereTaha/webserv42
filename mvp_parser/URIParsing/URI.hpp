#pragma once

#include <iostream>
#include <string>
#include <vector>

class URI
{
    private:
        std::string _scheme;
        std::string _username;
        std::string _password;
        std::string _host;
        std::string _port;
        std::string _path;
        std::string _normalizedPath;
        std::string _decodedPath;
        std::string _query;
        std::string _decodedQuery;

        std::string percentDecode(const std::string& encoded);

        bool _isValid;
        bool _isHostIP;
        bool _isAbsolute;
        bool _hasColonAfterHost;
        
        std::string normalizePath(const std::string& path);

    public:
        URI();
        ~URI();
        
        void setScheme(std::string schemeInput);
        void setUsername(std::string usernameInput);
        void setPassword(std::string passwordInput);
        void setHost(std::string hostInput);
        void setPort(std::string portInput);
        void setPath(std::string pathInput);
        void setNormalizedPath(std::string pathInput);
        void setQuery(std::string queryInput);
        
        void setValid(bool status);
        void setHostIP(bool isIP);
        void setAbsolute(bool isAbsolute);
        void setHasColonAfterHost(bool hasColon);

        std::string getScheme();
        std::string getUsername();
        std::string getPassword();
        std::string getHost();
        std::string getPort();
        std::string getPath();
        std::string getNormalizedPath();
        std::string getDecodedPath();
        std::string getQuery();
        std::string getDecodedQuery();
        bool isHostIP();
        bool isAbsolute();
        bool hasColonAfterHost();
        bool isValid();

};