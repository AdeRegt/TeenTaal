typedef struct{
    unsigned long address;
    unsigned long register_eax;
    unsigned long register_ebx;
    unsigned long register_ecx;
    unsigned long register_edx;
    unsigned long register_isp;
    unsigned char used;
}Process;

typedef struct{
    Process *currentProcess;
    char state;
}VirtualCPU;

#define MAX_PROCESSES 3
#define RES_ERROR 0xCD

#define CPU_STATE_OFF 0x00
#define CPU_STATE_RUNNING 0x01
#define CPU_STATE_PANICK 0x02

/*
    Halts the machine
    Opcode: 0x00
    Length: 1
    HLT
*/
#define CPU_INSTRUCTION_HALT            0x00

/*
    Jump to address
    Opcode: 0x01 [dword]
    Length: 5
    JMP DWORD
*/
#define CPU_INSTRUCTION_JMP             0x01

/*
    Call to address
    Opcode: 0x02 [dword]
    Length: 5
    CALL DWORD
*/
#define CPU_INSTRUCTION_CALL            0x02

/*
    Return to last addr
    Opcode: 0x03
    Length: 1
    RET
*/
#define CPU_INSTRUCTION_RET             0x03

/*
    Set value to target
    Opcode: 0x05 [byte] [arg1] [arg2]
    Length: 5
    JMP DWORD
*/
#define CPU_INSTRUCTION_SET             0x05
#define CPU_INSTRUCTION_ADD             0x06
#define CPU_INSTRUCTION_SUB             0x07
#define CPU_INSTRUCTION_DIV             0x08
#define CPU_INSTRUCTION_MUL             0x09
#define CPU_INSTRUCTION_INC             0x0A
#define CPU_INSTRUCTION_DEC             0x0B
#define CPU_INSTRUCTION_CMP_EQU         0x0C
#define CPU_INSTRUCTION_CMP_EQU_N       0x0D

#define CPU_REGISTER_POINTER_EAX        0x01
#define CPU_REGISTER_POINTER_EBX        0x02
#define CPU_REGISTER_POINTER_ECX        0x03
#define CPU_REGISTER_POINTER_EDX        0x04
#define CPU_REGISTER_RAW_BYTE_AT        0x05
#define CPU_REGISTER_RAW_WORD_AT        0x06
#define CPU_REGISTER_RAW_DWORD_AT       0x07
#define CPU_REGISTER_RAW_BYTE_DI        0x08
#define CPU_REGISTER_RAW_WORD_DI        0x09
#define CPU_REGISTER_RAW_DWORD_DI       0x0A

#define BYTE_SIZE                       1
#define WORD_SIZE                       2
#define DWORD_SIZE                      4

/*
    Print a string message to the console, ending with 0x00
    @param message the string to print
*/
void teen_print(const char* message);

/*
    Print a hexadecimal number on the screen
    @param character the character to print
*/
void teen_print_char_as_hex(unsigned char character);
