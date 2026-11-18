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
        
        output_name = ''
        if flags['output']:
            e =2 # Do later
        else:
            output_name = file.split('/')[-1].split('.')[0]+'.hack'
        
        output = open(output_name, 'w')

        address = 16
        sec_pass = Parser(file)
        sec_pass.cycle() # initialize

        while True:
            cType  = sec_pass.commandType()
            sym    = sec_pass.symbol()
            c_inst = [sec_pass.dest(),sec_pass.comp(),sec_pass.jump()]

            # If command is an A instruction
            if cType == 'A_INSTRUCTION':
                # Check if the symbol is a digit or a variable
                if not sym.isdigit():
                    # Check if variable already exist (If it exists then it points to where the program will jump)
                    if table.contains(sym):
                        output.writelines(a_instruct(table.GetAddress(sym)) + '\n')
                    else:
                        table.addEntry(sym, address)
                        address += 1
                        output.writelines(a_instruct(table.GetAddress(sym)) + '\n')
                else:
                    output.writelines(a_instruct(sym)+'\n')
            # If command is a C instruction
            elif cType == 'C_INSTRUCTION':
                # Unpack list to args(* operator unpacks list)
                output.writelines(c_instruct(*c_inst) + '\n')
            # print(sec_pass.get_current_command())
            if not sec_pass.hasMoreCommands():
                break
            sec_pass.advance()

if __name__ == '__main__':
    main()