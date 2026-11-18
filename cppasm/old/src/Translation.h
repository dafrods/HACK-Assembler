#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <string>

namespace Translation
{
    std::string a_instruct(const std::string& symbol);
    
    std::string a_instruct(uint symbol);
    
    //Returns a C-Instruction 16-bit binary string
    std::string c_instruct(const std::string& Dest, const std::string& Comp,const std::string& Jump);
}

#endif