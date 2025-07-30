#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Host.hpp"
#include "Path.hpp"
#include "Port.hpp"

class URI
{
    private:
        std::string _scheme;
        std::string _username;
        std::string _password;
        Host _host;
        Port _port;
        Path _path;
        std::string _query;
        std::string _decodedQuery;

        std::string percentDecode(const std::string& encoded);

        bool _isValid;
        bool _hasColonAfterHost;

    public:
        URI();
        ~URI();
        
        void setScheme(const std::string& schemeInput);
        void setUsername(const std::string& usernameInput);
        void setPassword(const std::string& passwordInput);
        void setHost(const std::string& hostInput);
        void setHost(const Host& host);
        void setPort(const std::string& portInput);
        void setPort(const Port& port);
        void setPath(const std::string& pathInput);
        void setPath(const Path& path);
        void setNormalizedPath(const std::string& pathInput);
        void setQuery(const std::string& queryInput);
        
        void setValid(bool status);
        void setHasColonAfterHost(bool hasColon);

        std::string getScheme() const;
        std::string getUsername() const;
        std::string getPassword() const;
        
        
        Host getHost() const;
        std::string getHostString() const;
        bool isHostIP() const;
        
        
        Port getPort() const;
        std::string getPortString() const;
        int getPortNumber() const;
        
        
        Path getPath() const;
        std::string getPathString() const;
        std::string getNormalizedPath() const;
        std::string getDecodedPath() const;
        bool isAbsolute() const;
        
        std::string getQuery() const;
        std::string getDecodedQuery() const;
        bool hasColonAfterHost() const;
        bool isValid() const;

};