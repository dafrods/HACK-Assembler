#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <unordered_map>

class SymbolTable
{
    private:
        std::unordered_map<std::string, uint> Symbols;
    public:
        SymbolTable();
        void addEntry   (const std::string& symbol, uint address);
        bool contains   (const std::string& symbol);
        int  getAddress (const std::string& symbol);
};

#endif