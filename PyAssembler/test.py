from sys import argv
from Assembler import Parser, SymbolTable
from Translation import a_instruct,c_instruct

def flag()->dict:
    """Handles Flags"""
    flags ={
        'output':[],
        'toAssembly':False
        }
    # ext = ['txt','o','out','hack']

    if '-o' in argv:
        i = argv.index('-o')
        if '.' not in argv[i+1]:
            raise Exception('No file specified')
        else:
            flags['output'].append(argv[i+1])

    if '-a' in argv:
        flags['toAssembly'] = True
    
    return flags

def main():
    file_list = [i for i in argv if i.endswith('.asm')]
    flags = flag()

    for file in file_list:
        # file = file
        table = SymbolTable()

        first_pass = Parser(file)
        first_pass.cycle() # initialize

        while True:
            if first_pass.commandType() == 'L_INSTRUCTION':
                table.addEntry(first_pass.symbol(),first_pass.get_counter())
            if not first_pass.hasMoreCommands():
                break
            first_pass.advance()

        for key, value in table._symbols.items():
            print(f'Key: {key} Value: {value}')

if __name__ == '__main__':
    main()