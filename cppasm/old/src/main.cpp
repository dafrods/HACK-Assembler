#include "Parser.h"
#include "Translation.h"
#include "SymbolTable.h"
#include "Utility.h"

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <unordered_map>

#include <algorithm>

bool inContainer(std::vector<std::string>& arguments, const std::string& element, std::vector<std::string>::iterator& it);
void argumentFlags(std::vector<std::string>& arguments,std::string& inputFile, std::string& outputFile);
void FirstPass(Parser& pass, SymbolTable& symbolTable);
void SecondPass(Parser& pass, SymbolTable& symbolTable, const std::string& outputFile);

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        std::cout << "No Arguments Specified...\nAssembler.a [Filename] <-options>" << std::endl;
        return 1;
    }

    std::vector<std::string> arguments(argv + 1, argv + argc);

    std::string inputFile, 
                outputFile;

    argumentFlags(arguments, inputFile, outputFile);

    if(outputFile.empty())
        outputFile = "test.hack";

    Parser      firstPass(inputFile);
    SymbolTable symbolTable;

    FirstPass(firstPass, symbolTable);

    Parser secondPass(inputFile);
    
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

void argumentFlags(std::vector<std::string>& arguments,std::string& inputFile, std::string& outputFile)
{  
    std::vector<std::string>::iterator it;
    bool hasInputFile = false;

    // check is the first argument has the '-' character
    if(!Utils::isElementInString(arguments[0],"-"))
    {
        hasInputFile = true;
        inputFile = arguments[0];
        arguments.erase(arguments.begin());
    }

    if(inContainer(arguments,"-h",it))
    {

        arguments.erase(it);
    }
 
    if(inContainer(arguments,"-o",it) && hasInputFile)
    {
        if(Utils::isElementInString(*(it+1),"-") || it+1 == arguments.end())
            throw std::runtime_error("-o [output filename]");
        // outputFile = *(it+1);
        outputFile = *(std::next(it));
        arguments.erase(it+1);
        arguments.erase(it);
    }

}

void FirstPass(Parser& pass,SymbolTable& symbolTable)
{

    while(true)
    {
        if(pass.commandType() == "L_INSTRUCTION")
            symbolTable.addEntry(pass.symbol(),pass.getCounter());
        if (!pass.hasMoreCommands())
            break;
        pass.advance();
    }
}

void SecondPass(Parser& pass,SymbolTable& symbolTable, const std::string& outputFile)
{
    std::string cType;
    std::string symbol;
    
    std::ofstream output(outputFile);

    bool isVariable;
    bool isAddress;
    bool isCInst;

    int address = 16;

    while(true)
    {
        cType  = pass.commandType();
        symbol = pass.symbol();
        
        isVariable = (cType == "A_INSTRUCTION") && (!Utils::isStringDigit(symbol));
        isAddress  = (cType == "A_INSTRUCTION") && (Utils::isStringDigit(symbol));
        isCInst    = (cType == "C_INSTRUCTION");

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
        {
            output << Translation::a_instruct(symbol) << "\n";
        }
        
        if(isCInst)
        {
            output << Translation::c_instruct(pass.dest(),pass.comp(),pass.jump()) << "\n";
        }
        if(!pass.hasMoreCommands())
            break;
        pass.advance();
    }
}
