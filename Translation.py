COMP = {
    '0'  :'101010',
    '1'  :'111111',
    '-1' :'111010',
    'D'  :'001100',
    'A'  :'110000',
    '!D' :'001101',
    '!A' :'110001',
    '-D' :'001111',
    '-A' :'110011',
    'D+1':'011111',
    'A+1':'110111',
    'D-1':'001110',
    'A-1':'110010',
    'D+A':'000010',
    'D-A':'010011',
    'A-D':'000111',
    'D&A':'000000',
    'D|A':'010101',
}
DEST = {
    ''   :'000',
    'M'  :'001',
    'D'  :'010',
    'MD' :'011',
    'A'  :'100',
    'AM' :'101',
    'AD' :'110',
    'AMD':'111'
}
JMP= {
    ''   :'000',
    'JGT':'001',
    'JEQ':'010',
    'JGE':'011',
    'JLT':'100',
    'JNE':'101',
    'JLE':'110',
    'JMP':'111'
}

def dest(mnemonic:str)->str:
    if mnemonic is None:
        mnemonic = ''
    return DEST[mnemonic]

def comp(mnemonic:str)->str:
    a = '0'
    if 'M' in mnemonic:
        a = '1'
        mnemonic = mnemonic.replace('M','A')
    return a+COMP[mnemonic]

def jump(mnemonic:str)->str:
    if mnemonic is None:
        mnemonic = ''
    return JMP[mnemonic]

def a_instruct(symbol:str|int)->str:
    """Returns a 16-bit binary string"""
    if type(symbol) == type('str'):
        if symbol.isdigit():
            return str(bin(int(symbol)))[2:].rjust(16,'0')
    elif type(symbol) == type(1):
        return str(bin(symbol))[2:].rjust(16,'0')
    
def c_instruct(Dest:str,Comp:str,Jump:str)->str:
    """Returns a 16-bit binary string"""
    return '111'+comp(Comp)+dest(Dest)+jump(Jump)
