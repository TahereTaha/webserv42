#include "Path.hpp"
#include "StringUtils.hpp"

Path::Path() : _path(""), _normalizedPath(""), _decodedPath(""), _isAbsolute(false)
{
}

Path::Path(const std::string& path) : _path(path), _isAbsolute(false)
{
    if (!path.empty() && path[0] == '/')
        _isAbsolute = true;
    _normalizedPath = normalizePath(path);
    _decodedPath = percentDecode(_normalizedPath);
}

Path::~Path()
{
}

void Path::setPath(const std::string& path)
{
    _path = path;
    if (!path.empty() && path[0] == '/')
        _isAbsolute = true;
    else
        _isAbsolute = false;
    _normalizedPath = normalizePath(path);
    _decodedPath = percentDecode(_normalizedPath);
}

void Path::setNormalizedPath(const std::string& normalizedPath)
{
    _normalizedPath = normalizedPath;
    _decodedPath = percentDecode(_normalizedPath);
}

void Path::setAbsolute(bool isAbsolute)
{
    _isAbsolute = isAbsolute;
}

std::string Path::getPath() const
{
    return _path;
}

std::string Path::getNormalizedPath() const
{
    return _normalizedPath;
}

std::string Path::getDecodedPath() const
{
    return _decodedPath;
}

bool Path::isAbsolute() const
{
    return _isAbsolute;
}

std::string Path::normalizePath(const std::string& path)
{
    if (path.empty())
        return "";
    
    std::vector<std::string> segments = StringUtils::split(path, '/');
    std::vector<std::string> normalizedSegments;
    
    for (size_t i = 0; i < segments.size(); i++)
    {
        const std::string& segment = segments[i];
        
        if (segment.empty() || segment == ".")
        {
            continue;
        }
        else if (segment == "..")
        {
            if (!normalizedSegments.empty())
                normalizedSegments.pop_back();
        }
        else
        {
            normalizedSegments.push_back(segment);
        }
    }
    
    std::string normalizedPath;
    
    if (!path.empty() && path[0] == '/')
        normalizedPath = "/";
    
    for (size_t i = 0; i < normalizedSegments.size(); i++)
    {
        if (i > 0)
            normalizedPath += "/";
        normalizedPath += normalizedSegments[i];
    }
    
    if (path.length() > 1 && path[path.length() - 1] == '/' && !normalizedPath.empty() && normalizedPath[normalizedPath.length() - 1] != '/')
        normalizedPath += "/";
    
    return normalizedPath;
}

std::string Path::percentDecode(const std::string& encoded)
{
    std::string decoded;
    for (size_t i = 0; i < encoded.length(); i++)
    {
        if (encoded[i] == '%' && i + 2 < encoded.length())
        {
            int digit1 = StringUtils::hexToDecimal(encoded[i+1]);
            int digit2 = StringUtils::hexToDecimal(encoded[i+2]);
            
            if (digit1 != -1 && digit2 != -1)
            {
                char decodedChar = static_cast<char>((digit1 << 4) | digit2);
                decoded += decodedChar;
                i += 2; 
            }
            else
            {
                decoded += encoded[i];
            }
        }
        else if (encoded[i] == '+')
        {
            decoded += ' ';
        }
        else
        {
            decoded += encoded[i];
        }
    }
    return decoded;
}
