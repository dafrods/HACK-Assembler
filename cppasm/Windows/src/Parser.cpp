#include "Parser.h"
#include "Utility.h"

#include <exception>

#include <iostream>
#include <algorithm>

bool Parser::isInstruction(const std::string& element)
{
    for(const auto& str:INSTRUCTIONS)
    {
        if(element == str)
            return true;
    }
    return false;
}

/**
 * The function cleans a given string by removing any characters after "//" and removing any
 * whitespace.
 * 
 * @param text The input string that needs to be cleaned. The function removes any characters after the
 * "//" symbol and then removes any whitespace characters from the remaining string. The cleaned string
 * is then stored back in the same input variable "text".
 */
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
}

bool Parser::hasMoreCommands()
{
    bool hasCycled = (this->current_command != this->next_command);

    std::string line;
    std::string cType;

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

        if (cType != "L_INSTRUCTION")
            this->nprog_count++;
        return true;
    }
    return false;
}

void Parser::advance()
{
    this->current_command = this->next_command;
    if(commandType() != "L_INSTRUCTION")
        this->prog_count++;
}

/**
 * The function returns the value of the "prog_count" variable in the Parser class.
 * 
 * @return The function `getCounter()` is returning the value of the member variable `prog_count` of
 * the current object (`this`).
 */
int Parser::getCounter()
{
    return this->prog_count;
}

/**
 * The function determines the type of instruction (A, L, or C) based on the input command string.
 * 
 * @param command The input command that needs to be parsed to determine its type.
 * 
 * @return The function `commandType` returns a string indicating the type of instruction based on the
 * input `command`. It returns "A_INSTRUCTION" if the command contains "@" symbol, "L_INSTRUCTION" if
 * it contains "(" symbol, "C_INSTRUCTION" if it contains "=" or ";" symbols, and an empty string if
 * none of these symbols are present in the command.
 */
std::string Parser::commandType(const std::string& command)
{
    if(Utils::inString(command,"@"))
        return "A_INSTRUCTION";
    else if(Utils::inString(command,"("))
        return "L_INSTRUCTION";
    else if (Utils::inString(command,"=") || Utils::inString(command,";"))
        return "C_INSTRUCTION";
    return "";
}

std::string Parser::commandType()
{
    if(Utils::inString(this->current_command,"@"))
        return "A_INSTRUCTION";
    else if(Utils::inString(this->current_command,"("))
        return "L_INSTRUCTION";
    else if (Utils::inString(this->current_command,"=") || Utils::inString(this->current_command,";"))
        return "C_INSTRUCTION";
    return "";
}

std::string Parser::symbol()
{
    std::string comType = commandType();
    if(comType == "A_INSTRUCTION")
        return this->current_command.substr(1);
    else if (comType == "L_INSTRUCTION")
        return this->current_command.substr(1,this->current_command.length() - 2);
    return "";
}
std::string Parser::symbol(const std::string& str)
{
    std::string comType = commandType(str);
    if(comType == "A_INSTRUCTION")
        return str.substr(1);
    else if (comType == "L_INSTRUCTION")
        return str.substr(1, str.length() - 2);
    return "";
}

std::string Parser::dest()
{
    if(commandType() != "C_INSTRUCTION")
        return "";
    if(Utils::inString(this->current_command,"="))
        return Utils::split(this->current_command,"=")[0];
    return "";
}

std::string Parser::comp()
{
    if(commandType() != "C_INSTRUCTION")
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
    if(commandType() != "C_INSTRUCTION")
        return "";
    if(Utils::inString(this->current_command,";"))
        return Utils::split(this->current_command,";")[1];
    return "";
}
