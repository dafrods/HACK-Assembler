#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>

namespace Utils
{   
    // Searches string element or substring within a string
    // Returns true if the substring is found
    bool                     inString(const std::string& str,  const std::string& element);
    bool                     isStringDigit    (const std::string& str);
    void                     replace          (      std::string& str,  const std::string& from, const std::string& to);
    std::vector<std::string> split            (const std::string& str,  const std::string& delimiter);

}

#endif