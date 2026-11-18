#ifndef PARSER_H
#define PARSER_H

#include <string>

#include <fstream>

#include "Enums.h"

class Parser
{   
    public:
        // Constructor
        Parser(const std::string& filename);

        bool hasMoreCommands();

        void advance();

        /**
         * The function returns the counter of the current available command (skips newline).
         * 
         * @return The function `getCounter()` is returning the value of the member variable `prog_count` of
         * the current object (`this`).
         */
        int getCounter();

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
        Instructions commandType(const std::string& command);

        Instructions commandType();

        std::string symbol();

        std::string symbol(const std::string& str);

        std::string dest();

        std::string comp();

        std::string jump();

    private:
        std::string filename;
        std::string next_command;
        std::string current_command;
        
        std::ifstream file;

        int prog_count; // Counter for processable instructions: A and C instructions
        int nprog_count;// Counter for processable instructions including symbols: A, L and C instructions
        int line_count; // Counter for line number, not including trailing

        bool isInstruction(const Instructions& element);
        /**
         * The function cleans a given string by removing any characters after "//" and removing any
         * whitespace.
         * 
         * @param text The input string that needs to be cleaned. The function removes any characters after the
         * "//" symbol and then removes any whitespace characters from the remaining string. The cleaned string
         * is then stored back in the same input variable "text".
         */
        void clean(std::string& text);

};

#endif