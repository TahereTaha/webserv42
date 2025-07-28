#pragma once

#include <string>
#include <vector>

class Path
{
private:
    std::string _path;
    std::string _normalizedPath;
    std::string _decodedPath;
    bool _isAbsolute;

    std::string normalizePath(const std::string& path);
    std::string percentDecode(const std::string& encoded);

public:
    Path();
    Path(const std::string& path);
    ~Path();

    void setPath(const std::string& path);
    void setNormalizedPath(const std::string& normalizedPath);
    void setAbsolute(bool isAbsolute);

    std::string getPath() const;
    std::string getNormalizedPath() const;
    std::string getDecodedPath() const;
    bool isAbsolute() const;
};
