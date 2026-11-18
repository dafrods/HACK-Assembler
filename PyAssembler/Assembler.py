class Parser:

    INSTRUCTIONS = ['A_INSTRUCTION', 'C_INSTRUCTION', 'L_INSTRUCTION']

    def __init__(self,filename):
        self._file            = open(filename, 'r')
        self._next_command    = self._clean(self._file.readline())
        self._current_command = ''
        self._prog_count      = 0
        self._nprog_count     = 0
        self._line_count      = 1
        
    def _clean(self,string:str)->str:
        return string.split('//')[0].strip()
    
    def hasMoreCommands(self)->bool:
        """To be called before advance() is executed;
        @return -> true if there exist more commands
        """
        #If the current command is not equal to the next command, return true and if not find the next command
        if not (self._current_command == self._next_command) and self.commandType(self._next_command) in self.INSTRUCTIONS:
            return True
        for line in self._file:
            line = self._clean(line)
            self._line_count += 1
            if not self.commandType(line) in self.INSTRUCTIONS:
                continue
            self._next_command = line
            if self.commandType() != 'L_INSTRUCTION':
                self._nprog_count += 1
            return True
        return False
    
    def advance(self)->None:
        self._current_command = self._next_command
        if self.commandType() != 'L_INSTRUCTION':
            self._prog_count += 1

    def cycle(self)->None:
        self.hasMoreCommands()
        self.advance()

    def commandType(self,command = None)->str|None:
        if command is None:
            command = self._current_command

        if command.startswith('@'):
            return 'A_INSTRUCTION'
        elif command.startswith('('):
            return 'L_INSTRUCTION'
        elif '=' in command or ';' in command:
            return 'C_INSTRUCTION'
    
    def symbol(self)->str|None:
        if self.commandType() == 'A_INSTRUCTION':
            return self._current_command[1:]
        elif self.commandType() == 'L_INSTRUCTION':
            return self._current_command[1:-1]
      
    def dest(self)->str|None:
        if self.commandType() != 'C_INSTRUCTION':
            return
        if '=' in self._current_command:
            return self._current_command.split('=')[0]

    def comp(self)->str|None:
        if self.commandType() != 'C_INSTRUCTION':
            return
        if '=' in self._current_command and ';' in self._current_command:
            return self._current_command.split('=')[1].split(';')[0]
        elif '=' in self._current_command:
            return self._current_command.split('=')[1]
        elif ';' in self._current_command:
            return self._current_command.split(';')[0]

    def jump(self)->str|None:
        if self.commandType() != 'C_INSTRUCTION':
            return
        if ';' in self._current_command:
            return self._current_command.split(';')[1]

    def get_current_command(self)->str:
        return self._current_command
    
    def get_counter(self)->int:
        return self._prog_count

class SymbolTable:
    def __init__(self):
        self._symbols:dict={
            'SP' :0,
            'LCL':1,
            'ARG':2,
            'THIS':3,
            'THAT':4,
            'R0' :0,
            'R1' :1,
            'R2' :2,
            'R3' :3,
            'R4' :4,
            'R5' :5,
            'R6' :6,
            'R7' :7,
            'R8' :8,
            'R9' :9,
            'R10':10,
            'R11':11,
            'R12':12,
            'R13':13,
            'R14':14,
            'R15':15,
            'SCREEN':16384,
            'KBD':24576
        }

    def addEntry(self,symbol:str,address:int=0):
        self._symbols[symbol] = address

    def contains(self,symbol:str)->bool:
        return symbol in self._symbols

    def GetAddress(self,symbol:str)->int:
        return self._symbols[symbol]

# @"(@|\()(\w+)(\))?"