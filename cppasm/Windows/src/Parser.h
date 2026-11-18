#ifndef PARSER_H
#define PARSER_H

#include <string>

#include <fstream>

class Parser
{
    public:
        // Constructor
        Parser(const std::string& filename);
        bool hasMoreCommands();
        void advance();
        int getCounter();
        std::string commandType(const std::string& command);
        std::string commandType();
        std::string symbol();
        std::string symbol(const std::string& str);
        std::string dest();
        std::string comp();
        std::string jump();

    private:
        const std::string INSTRUCTIONS[3] = {"A_INSTRUCTION", "C_INSTRUCTION", "L_INSTRUCTION"};
        std::string filename;
        std::string next_command;
        std::string current_command;
        std::ifstream file;
        int prog_count;
        int nprog_count;
        int line_count;
        bool isInstruction(const std::string& element);
        void clean(std::string& text);

};

#endif