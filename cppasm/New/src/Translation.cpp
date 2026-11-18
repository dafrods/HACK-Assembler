#include "Translation.h"

#include "Utility.h"

#include <unordered_map>
#include <bitset>

#include <iostream>

using namespace Utils;

const std::unordered_map<std::string, std::string> COMP =  
{
    {"0"  ,"101010"},
    {"1"  ,"111111"},
    {"-1" ,"111010"},
    {"D"  ,"001100"},
    {"A"  ,"110000"},
    {"!D" ,"001101"},
    {"!A" ,"110001"},
    {"-D" ,"001111"},
    {"-A" ,"110011"},
    {"D+1","011111"},
    {"A+1","110111"},
    {"D-1","001110"},
    {"A-1","110010"},
    {"D+A","000010"},
    {"D-A","010011"},
    {"A-D","000111"},
    {"D&A","000000"},
    {"D|A","010101"},
};

const std::unordered_map<std::string, std::string> DEST =  
{
    {""   ,"000"},
    {"M"  ,"001"},
    {"D"  ,"010"},
    {"MD" ,"011"},
    {"A"  ,"100"},
    {"AM" ,"101"},
    {"AD" ,"110"},
    {"AMD","111"}
};

const std::unordered_map<std::string, std::string> JMP =  
{
    {""   ,"000"},
    {"JGT","001"},
    {"JEQ","010"},
    {"JGE","011"},
    {"JLT","100"},
    {"JNE","101"},
    {"JLE","110"},
    {"JMP","111"}
};

static std::string dest(const std::string& mnemonic)
{
    return DEST.at(mnemonic);
}

static std::string comp(const std::string& mnemonic)
{
    std::string a = "0";
    std::string str = mnemonic;
    if (inString(mnemonic, "M"))
    {
        a = "1";
        replace(str,"M","A");
    }
    return (a + COMP.at(str));

}

static std::string jump(const std::string& mnemonic)
{
    return JMP.at(mnemonic);
}


/*
String Version
 Reconstruction of the original python implementation of 
 str(bin(int(symbol)))[2:].rjust(16,'0') by chatGPT
*/
static std::string processSymbol(const std::string& symbol) 
{
    int intValue = std::stoi(symbol);
    std::string binaryStr = std::bitset<16>(intValue).to_string();
    return binaryStr;
}
/*
Int Version
 Reconstruction of the original python implementation of 
 str(bin(int(symbol)))[2:].rjust(16,'0') by chatGPT
*/
static std::string processSymbol(int symbol) 
{
    std::string binaryStr = std::bitset<16>(symbol).to_string();
    return binaryStr;
}

namespace Translation
{
    std::string a_instruct(const std::string& symbol)
    {
        return processSymbol(symbol);
    }

    std::string a_instruct(uint symbol)
    { 
        return processSymbol(symbol);
    }

    std::string c_instruct(const std::string& Dest, const std::string& Comp,const std::string& Jump)
    {
        return ("111"+comp(Comp)+dest(Dest)+jump(Jump));
    }
}