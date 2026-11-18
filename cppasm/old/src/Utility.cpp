#include "Utility.h"

#include <iostream>

namespace Utils
{   
    /**
     * The function checks if a given element is present in a given string and returns a boolean value.
     * 
     * @param str The string in which we want to check if the element is present or not.
     * @param element The element parameter is a string that we are checking to see if it is present in
     * another string (str).
     * 
     * @return The function `isElementInString` returns a boolean value indicating whether the
     * `element` string is present in the `str` string. It returns `true` if the `element` string is
     * found in the `str` string, and `false` otherwise.
     */
    bool isElementInString(const std::string& str, const std::string& element) 
    {
       return str.find(element) != std::string::npos;
    }
    /**
     * The function replaces all occurrences of a substring in a given string with another substring.
     * 
     * @param str A reference to a string that we want to modify by replacing a substring.
     * @param from The string that we want to replace in the original string.
     * @param to The "to" parameter is a constant reference to a std::string object that represents the
     * replacement string. This parameter specifies the string that will replace the "from" string in
     * the input string "str".
     * 
     * @return If the `index` variable is equal to `std::string::npos`, which means that the `from`
     * string was not found in the `str` string, then the function returns without doing anything. If
     * the `from` string is found in the `str` string, then the function replaces the `from` string
     * with the `to` string and returns nothing.
     */
    void replace(std::string& str, const std::string& from, const std::string& to)
    {
        size_t index = str.find(from);
        if (index == std::string::npos)
            return;
        str.replace(index, from.length(), to);
    }

    /**
     * The function splits a given string into substrings based on a specified delimiter and returns a
     * vector of the resulting substrings.
     * 
     * @param str The string that needs to be split into substrings based on the delimiter.
     * @param delimiter The delimiter is a string that is used to split the input string into
     * substrings. The function splits the input string at every occurrence of the delimiter and
     * returns a vector of the resulting substrings.
     * 
     * @return A vector of strings, where each string is a substring of the input string that was
     * separated by the specified delimiter.
     */
    std::vector<std::string> split(const std::string& str, const std::string& delimiter)
    {
        std::vector<std::string> substrings;
        size_t index;
        size_t d_len = delimiter.length();
        std::string temp = str;
        while(true)
        {
            index = temp.find(delimiter);
            if (index == std::string::npos)
            {
                substrings.push_back(temp);
                break;
            }
            substrings.push_back(temp.substr(0,index));
            temp = temp.substr(index + d_len);
        }
        return substrings;
    }

/**
 * The function checks if a given string consists only of digits.
 * 
 * @param str The input string that we want to check if it contains only digits or not.
 * 
 * @return The function `isStringDigit` returns a boolean value indicating whether all characters in
 * the input string are digits or not. It returns `true` if all characters are digits and `false`
 * otherwise.
 */
    bool isStringDigit(const std::string& str)
    {
        for (char c : str) 
        {
            if (!std::isdigit(c)) 
                return false;
        }
        return true;
    }
}