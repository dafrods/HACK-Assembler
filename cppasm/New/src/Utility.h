#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>

namespace Utils
{   

    bool inString(const std::string& str,  const std::string& element);

    bool isStringDigit    (const std::string& str);
    
    bool beginsWith       (const std::string& str,  const std::string& element);
    

    std::vector<std::string> split            (const std::string& str,  const std::string& delimiter);


    void replace(std::string& str, const std::string& from, const std::string& to);
}

#endif