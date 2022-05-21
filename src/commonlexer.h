/**
 * @brief Max size of the program
 * 
 */
#define MAX_PROGRAM_SIZE 0xFFF
/**
 * @brief Max var size 
 * 
 */
#define MAX_VARIABLE_SIZE 0xFF

#define OPCODE_MASK 0xF000

#define ARGUMENT_MASK 0x0FFF

#define RET_NAME "RET"
#define RET_OPCODE 0x0000

#define CALL_NAME "CALL"
#define CALL_OPCODE 0x1000

/*
OPCODE:
0   - RET      |     RETURN
1   - CALL     |     CALL [ADDRESS]
2   - JUMP     |     GOTO [ADDRESS]
3   - JE       |     JUMP EQUALS [ADDRESS]
4   - JM       |     JUMP MORE [ADDRESS]
5   - JL       |     JUMP LESS [ADDRESS]
6   - RRA      |     READ REGISTER A [ADDRESS]
7   - RRB      |     READ REGISTER B [ADDRESS]
8   - RRC      |     READ REGISTER C [ADDRESS]
9   - WRA      |     WRITE REGISTER A [ADDRESS]
A   - WRB      |     WRITE REGISTER B [ADDRESS]
B   - WRC      |     WRITE REGISTER C [ADDRESS]
C   - INT      |     INTERRUPT [NUMBER]
D   - OPE      |     OPERATIONAL [ADD|DEC|MUL|DIV]
E   - SHR      |     SHIFT [RIGHT|LEFT] [X]
F   - ???

BYTECODE SYNTAX:
0xF000 = opcode
0x0FFF = argument
max program size = 0xFFF
*/