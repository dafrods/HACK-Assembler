#include "Parser.h"
#include "Translation.h"
#include "SymbolTable.h"
#include "Utility.h"
#include "Enums.h"

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <unordered_map>

#include <algorithm>

#define VERSION "1.0"
#define PROGRAM_NAME "Hack Assembler"
#define PROGRAM_DESCRIPTION "Hack Assembler"
#define BUILD "Linux Build"


/**
 * Function checks if string exist in contain(Vector)
 * 
 * @param arguments 
 * 
 * @return true if string exist
*/
bool inContainer(      
                       std::vector<std::string>&            arguments, 
                 const std::string&                         element, 
                       std::vector<std::string>::iterator&  it
                );

/**
 * Function handles arguments and error-handling of arguments
 * 
 * @param arguments vector of arguments to be handled
 * @param &inputFile an empty string to be used as input 
 * @param &outputFile an empty string to be used as output when found with -o in arguments
*/
void argumentFlags(std::vector<std::string>& arguments,std::string& inputFile, std::string& outputFile);
void FirstPass(Parser& pass, SymbolTable& symbolTable);
void SecondPass(Parser& pass, SymbolTable& symbolTable, const std::string& outputFile);
void removeBeginsWith(std::vector<std::string>& arguments, const std::string& element);

int main(int argc, char** argv)
{
    std::vector<std::string> arguments(argv + 1, argv + argc);

    std::string inputFile, 
                outputFile;

    argumentFlags(arguments, inputFile, outputFile);

    
    // Exit if input file is not specified
    if(inputFile.empty())
        return 0;
    
    if(outputFile.empty())
        outputFile = inputFile;

    Parser      firstPass(inputFile);

    SymbolTable symbolTable;

    // Collect L-Instruction Symbols
    FirstPass(firstPass, symbolTable);

    Parser secondPass(inputFile);
    
    // Parse to Binary 
    SecondPass(secondPass, symbolTable, outputFile);

    return 0;
}

bool inContainer(std::vector<std::string>& arguments, const std::string& element, std::vector<std::string>::iterator& it)
{
    it = std::find(arguments.begin(), arguments.end(), element);
    if (it != arguments.end()) 
        return true;
    else
        return false;
}

void removeBeginsWith(std::vector<std::string>& arguments, const std::string& element)
{
    std::vector<std::string>::iterator it = arguments.begin();
    std::vector<std::string>::iterator lastGoodIt;
    while(it != arguments.end())
    {
        if(Utils::beginsWith(*it, element))
        {

        }
    }
}

void argumentFlags(std::vector<std::string>& arguments, std::string& inputFile,std::string& outputFile)
{  
    std::vector<std::string>::iterator it;
    bool argError = false;

    if(arguments.empty())
        throw std::invalid_argument("No arguments provided");

    if(inContainer(arguments,"-o",it))
    {
        std::cout << "Begins with '-'?: " << Utils::beginsWith(*(std::next(it)),"-") << "\tIs adjacent empty?: " << ((std::next(it)) == arguments.end()) << "\n";

        if(Utils::beginsWith(*(std::next(it)),"-") || (std::next(it)) == arguments.end())
            // If there is no output file specified, throw exception
            throw std::runtime_error("No input file specified!\n\t-o [output filename]");

        outputFile = *(std::next(it));
        arguments.erase(std::next(it));
        arguments.erase(it);
    }

    if(inContainer(arguments,"-h",it))
    {
        std::cout   << "Usage: HACK [options] file\n"
                    << "Options:\n"
                    << "    -h\t    Displays this Text.\n"
                    << "    -v\t    Displays Version of this Program\n"
                    << "    -o\t    Usage: '-o [filename]'\n"
                    << "When -o is not specified, a file will be created with name <input name>.hack\n";                    
        arguments.erase(it);
    }

    if(inContainer(arguments,"-v",it))
    {
        std::cout   << PROGRAM_NAME << " " << BUILD << " " << VERSION << std::endl;
        arguments.erase(it);
    }

    std::vector<std::string> invalids;

    it = arguments.begin();
    int i;

    for(i = 0; it+i != arguments.end();i++)
    {

    }

    for(const auto& arg : invalids)
    {
        std::cout << "Unknown argument: '" << arg << "' \n";
    }

    if(!invalids.empty())
        throw std::runtime_error("");


    // if(*arguments.begin() != arguments.back())
    // {
    //     throw std::runtime_error("Only one file must be provided");
    // }

    // inputFile = *arguments.begin(); // bruh moment
    inputFile = arguments.front();
    
}

void FirstPass(Parser& pass,SymbolTable& symbolTable)
{
    while(true)
    {
        if(pass.commandType() == L_INSTRUCTION)
            symbolTable.addEntry(pass.symbol(),pass.getCounter());
        if (!pass.hasMoreCommands())
            break;
        pass.advance();
    }
}

void SecondPass(Parser& pass,SymbolTable& symbolTable, const std::string& outputFile)
{
    Instructions cType;
    std::string symbol;
    
    std::ofstream output(outputFile);

    bool isVariable;
    bool isAddress;
    bool isCInst;

    int address = 16; // 0 to 15 are reserved

    while(true)
    {
        cType  = pass.commandType();
        symbol = pass.symbol();
        
        isVariable = (cType == A_INSTRUCTION) && (!Utils::isStringDigit(symbol));
        isAddress  = (cType == A_INSTRUCTION) && (Utils::isStringDigit(symbol));
        isCInst    = (cType == C_INSTRUCTION);

        if(isVariable)
        {
            if(symbolTable.contains(symbol))
                output << Translation::a_instruct(symbolTable.getAddress(symbol)) <<"\n";
            else
            {
                symbolTable.addEntry(symbol, address);
                address++;
                output << Translation::a_instruct(symbolTable.getAddress(symbol)) <<"\n";
            }
        }
    
        if(isAddress)
            output << Translation::a_instruct(symbol) << "\n";
        
        if(isCInst)
            output << Translation::c_instruct(pass.dest(),pass.comp(),pass.jump()) << "\n";

        if(!pass.hasMoreCommands())
            break;
        pass.advance();
    }
}
