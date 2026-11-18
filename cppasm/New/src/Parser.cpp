#include "Parser.h"
#include "Utility.h"

#include <exception>

#include <iostream>

#include <algorithm>

bool Parser::isInstruction(const Instructions& element)
{
    return element >= A_INSTRUCTION && element <= L_INSTRUCTION;
}

void Parser::clean(std::string& text)
{
    size_t pos = text.find("//");
    text = text.substr(0, pos);
    text.erase(std::remove_if(text.begin(), text.end(), ::isspace), text.end());
}

Parser::Parser(const std::string& filename)
{
    file.open(filename.c_str());
    if (!file.is_open())
        throw std::ifstream::failure("Could not open file: " + filename + ".\n");

    getline(file,next_command);
    clean(next_command);
            
    current_command = "";
    prog_count = 0;
    nprog_count = 0;
    line_count = 1;

    // Cycles to the nearest available instruction
    this->hasMoreCommands();
    this->advance();
}

bool Parser::hasMoreCommands()
{
    bool hasCycled = (this->current_command != this->next_command);

    std::string line;
    Instructions cType;

    if (hasCycled && isInstruction(commandType(this->next_command))) 
        return true;

    while(getline(this->file, line))
    {
        clean(line);
        cType = commandType(line);

        this->line_count++;

        if(!isInstruction(cType))
            continue;

        this->next_command = line;

        if (cType != L_INSTRUCTION)
            this->nprog_count++;
        return true;
    }
    return false;
}

void Parser::advance()
{
    this->current_command = this->next_command;
    Instructions cType = commandType();
    if(cType < L_INSTRUCTION)
        this->prog_count++;
}

int Parser::getCounter()
{
    return this->prog_count;
}

Instructions Parser::commandType(const std::string& command)
{
    if(Utils::beginsWith(command,"@"))
        return A_INSTRUCTION;
    else if(Utils::beginsWith(command,"("))
        return L_INSTRUCTION;
    else if (Utils::inString(command,"=") || Utils::inString(command,";"))
        return C_INSTRUCTION;
    return NOT_AN_INSTRUCTION;
}

Instructions Parser::commandType()
{
    if(Utils::beginsWith(this->current_command,"@"))
        return A_INSTRUCTION;
    else if(Utils::beginsWith(this->current_command,"("))
        return L_INSTRUCTION;
    else if (Utils::inString(this->current_command,"=") || Utils::inString(this->current_command,";"))
        return C_INSTRUCTION;
    return NOT_AN_INSTRUCTION;
}

std::string Parser::symbol()
{
    Instructions comType = commandType();
    if(comType == A_INSTRUCTION)
        return this->current_command.substr(1);
    else if (comType == L_INSTRUCTION)
        return this->current_command.substr(1,this->current_command.length() - 2);
    return "";
}

std::string Parser::symbol(const std::string& str)
{
    Instructions comType = commandType(str);
    if(comType == A_INSTRUCTION)
        return str.substr(1);
    else if (comType == L_INSTRUCTION)
        return str.substr(1, str.length() - 2);
    return "";
}

std::string Parser::dest()
{
    if(commandType() != C_INSTRUCTION)
        return "";
    if(Utils::inString(this->current_command,"="))
        return Utils::split(this->current_command,"=")[0];
    return "";
}

std::string Parser::comp()
{
    if(commandType() != C_INSTRUCTION)
        return "";
    if(Utils::inString(this->current_command,"=") && Utils::inString(this->current_command,";"))
        return Utils::split(Utils::split(this->current_command,"=")[1],";")[0];
    else if(Utils::inString(this->current_command,"="))
        return Utils::split(this->current_command,"=")[1];
    else if(Utils::inString(this->current_command,";"))
        return Utils::split(this->current_command,";")[0];
    return "";
}

std::string Parser::jump()
{
    if(commandType() != C_INSTRUCTION)
        return "";
    if(Utils::inString(this->current_command,";"))
        return Utils::split(this->current_command,";")[1];
    return "";
}
