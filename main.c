#include "dependancies.h"

/*
    Stack of process slots
*/
Process processes[MAX_PROCESSES];

/*
    Our own CPU
*/
VirtualCPU cpu;

/*
    Installs a process to the system
    @param address the real address where the new code is
    @return RES_ERROR when there is something wrong or the PID when it is succesfull
*/
char install_process(unsigned long address){
    if(address>0){
        for(int i = 0 ; i < MAX_PROCESSES ; i++){
            Process *proc = (Process*) (&processes[i]);
            if(proc->used==0){
                proc->address = address;
                proc->register_eax = 0;
                proc->register_ebx = 0;
                proc->register_ecx = 0;
                proc->register_edx = 0;
                proc->register_isp = 0;
                proc->used = 1;
                teen_print("install_process: process installed!\n");
                return i;
            }
        }
    }
    return RES_ERROR;
}

/*
    Dummy data to test the VM on!
*/
unsigned char dummydata[10] = {
    CPU_INSTRUCTION_SET,
    CPU_REGISTER_POINTER_EBX | (CPU_REGISTER_RAW_BYTE_DI << 4),
    10,
    CPU_INSTRUCTION_INC,
    CPU_REGISTER_POINTER_EAX,
    CPU_INSTRUCTION_CMP_EQU_N,
    CPU_REGISTER_POINTER_EBX | (CPU_REGISTER_POINTER_EAX << 4),
    3,
    CPU_INSTRUCTION_HALT,
    CPU_INSTRUCTION_HALT
};

unsigned char getNextInstructionByte(unsigned long offset){
    Process *proc = cpu.currentProcess;
    unsigned long instructionpointer = proc->address + proc->register_isp + offset;
    unsigned char currentInstruction = ((unsigned char*)instructionpointer)[0];
    return currentInstruction;
}

unsigned short getNextInstructionWord(unsigned long offset){
    Process *proc = cpu.currentProcess;
    unsigned long instructionpointer = proc->address + proc->register_isp + offset;
    unsigned short currentInstruction = ((unsigned short*)instructionpointer)[0];
    return currentInstruction;
}

unsigned long getNextInstructionDWord(unsigned long offset){
    Process *proc = cpu.currentProcess;
    unsigned long instructionpointer = proc->address + proc->register_isp + offset;
    unsigned long currentInstruction = ((unsigned long*)instructionpointer)[0];
    return currentInstruction;
}

void setRegisterEAX(unsigned long waarde){
    cpu.currentProcess->register_eax = waarde;
}

void setRegisterEBX(unsigned long waarde){
    cpu.currentProcess->register_ebx = waarde;
}

void setRegisterECX(unsigned long waarde){
    cpu.currentProcess->register_ecx = waarde;
}

void setRegisterEDX(unsigned long waarde){
    cpu.currentProcess->register_edx = waarde;
}

void setRegisterOrMemory(unsigned char method,unsigned long waarde,int offset){
    if(method==CPU_REGISTER_POINTER_EAX){
        setRegisterEAX(waarde);
    }else if(method==CPU_REGISTER_POINTER_EBX){
        setRegisterEBX(waarde);
    }else if(method==CPU_REGISTER_POINTER_ECX){
        setRegisterECX(waarde);
    }else if(method==CPU_REGISTER_POINTER_EDX){
        setRegisterEDX(waarde);
    }else{
        teen_print("setRegisterOrMemory error: unknown method: ");
        teen_print_char_as_hex(method);
        teen_print(" \n");
        cpu.state = CPU_STATE_PANICK;
    }
}

unsigned long getRegisterOrMemory(unsigned char method,int offset){
    if(method==CPU_REGISTER_POINTER_EAX){
        return cpu.currentProcess->register_eax;
    }else if(method==CPU_REGISTER_POINTER_EBX){
        return cpu.currentProcess->register_ebx;
    }else if(method==CPU_REGISTER_POINTER_ECX){
        return cpu.currentProcess->register_ecx;
    }else if(method==CPU_REGISTER_POINTER_EDX){
        return cpu.currentProcess->register_edx;
    }else if(method==CPU_REGISTER_RAW_BYTE_DI){
        return getNextInstructionByte(offset);
    }else{
        teen_print("handle_cpu_instruction error: unknown swap type: ");
        teen_print_char_as_hex(method);
        teen_print(" \n");
        cpu.state = CPU_STATE_PANICK;
        return RES_ERROR;
    }
}

int calculateMemoryOffset(unsigned char method){
    if(method==CPU_REGISTER_POINTER_EAX||method==CPU_REGISTER_POINTER_EBX||method==CPU_REGISTER_POINTER_ECX||method==CPU_REGISTER_POINTER_EDX){
        return 0;
    }else if(method==CPU_REGISTER_RAW_BYTE_DI){
        return 1;
    }else{
        teen_print("calculateMemoryOffset error: unknown swap type: ");
        teen_print_char_as_hex(method);
        teen_print(" \n");
        cpu.state = CPU_STATE_PANICK;
        return RES_ERROR;
    }
}

void handle_cpu_instruction(){
    // is there a process we need to take care off?
    if(cpu.currentProcess == 0){
        // no, there is no process. This should not happen, so we are in panick!
        teen_print("handle_cpu_instruction panic: cpu.currentProcess == 0 !\n");
        cpu.state = CPU_STATE_PANICK;
        return;
    }
    // is the tread active?
    if(cpu.currentProcess->used == 0){
        // no, process is not used. We should not be here...
        teen_print("handle_cpu_instruction panic: cpu.currentProcess.used == 0 !\n");
        cpu.state = CPU_STATE_PANICK;
        return;
    }
    // OK, the CPU state is OK
    // now, lets get the instruction that we are waiting for...
    unsigned char currentInstruction = getNextInstructionByte(0);

    switch(currentInstruction){
        case CPU_INSTRUCTION_HALT:
            teen_print("handle_cpu_instruction info: HALT instruction found\n");
            cpu.state = CPU_STATE_OFF;
            break;
        case CPU_INSTRUCTION_JMP:
            teen_print("handle_cpu_instruction info: jump to instruction\n");
            unsigned long jump_to_address = getNextInstructionDWord(BYTE_SIZE);
            cpu.currentProcess->register_isp = jump_to_address;
            break;
        case CPU_INSTRUCTION_CALL:
            break;
        case CPU_INSTRUCTION_RET:
            break;
        case CPU_INSTRUCTION_SET:
            teen_print("handle_cpu_instruction info: set value to register\n");
            unsigned char quotaX = getNextInstructionByte(BYTE_SIZE);
            unsigned char quoteA = quotaX & 0x0F;
            unsigned char quoteB = (quotaX >> 4) & 0x0F;
            unsigned long waarde = 0;

            waarde = getRegisterOrMemory(quoteB, BYTE_SIZE + BYTE_SIZE + calculateMemoryOffset(quoteA));
            setRegisterOrMemory(quoteA,waarde,BYTE_SIZE + BYTE_SIZE);
            
            cpu.currentProcess->register_isp += ( BYTE_SIZE + BYTE_SIZE + calculateMemoryOffset(quoteA) + calculateMemoryOffset(quoteB));
            break;
        case CPU_INSTRUCTION_ADD:
            teen_print("handle_cpu_instruction info: add function\n");
            quotaX = getNextInstructionByte(1);
            quoteA = quotaX & 0x0F;
            quoteB = (quotaX >> 4) & 0x0F;
            waarde = 0;

            unsigned long awaarde = getRegisterOrMemory(quoteA, BYTE_SIZE + BYTE_SIZE);
            unsigned long bwaarde = getRegisterOrMemory(quoteB, BYTE_SIZE + BYTE_SIZE + calculateMemoryOffset(quoteA));
            awaarde += bwaarde;
            setRegisterOrMemory(quoteA,awaarde,BYTE_SIZE + BYTE_SIZE);
            
            cpu.currentProcess->register_isp += ( BYTE_SIZE + BYTE_SIZE + calculateMemoryOffset(quoteA) + calculateMemoryOffset(quoteB));
            break;
        case CPU_INSTRUCTION_SUB:
            break;
        case CPU_INSTRUCTION_DIV:
            break;
        case CPU_INSTRUCTION_MUL:
            break;
        case CPU_INSTRUCTION_INC:
            teen_print("handle_cpu_instruction info: increase value\n");
            quotaX = getNextInstructionByte(BYTE_SIZE);
            quoteA = quotaX & 0x0F;
            quoteB = (quotaX >> 4) & 0x0F;
            waarde = 0;
            if(quoteB!=0){
                teen_print("handle_cpu_instruction error: higher nibble of CPU_INSTRUCTION_INC param is set!\n");
                cpu.state = CPU_STATE_PANICK;
                return;
            }

            waarde = getRegisterOrMemory(quoteA, BYTE_SIZE + BYTE_SIZE );
            waarde ++;
            setRegisterOrMemory(quoteA,waarde,BYTE_SIZE + BYTE_SIZE);
            
            cpu.currentProcess->register_isp += ( BYTE_SIZE + BYTE_SIZE + calculateMemoryOffset(quoteA));
            break;
        case CPU_INSTRUCTION_DEC:
            teen_print("handle_cpu_instruction info: decrease value\n");
            quotaX = getNextInstructionByte(BYTE_SIZE);
            quoteA = quotaX & 0x0F;
            quoteB = (quotaX >> 4) & 0x0F;
            waarde = 0;
            if(quoteB!=0){
                teen_print("handle_cpu_instruction error: higher nibble of CPU_INSTRUCTION_INC param is set!\n");
                cpu.state = CPU_STATE_PANICK;
                return;
            }

            waarde = getRegisterOrMemory(quoteA, BYTE_SIZE + BYTE_SIZE);
            waarde --;
            setRegisterOrMemory(quoteA,waarde,BYTE_SIZE + BYTE_SIZE);
            
            cpu.currentProcess->register_isp += ( BYTE_SIZE + BYTE_SIZE + calculateMemoryOffset(quoteA));
            break;
        case CPU_INSTRUCTION_CMP_EQU:
            teen_print("handle_cpu_instruction info: compare and jump if equals\n");
            quotaX = getNextInstructionByte(BYTE_SIZE);
            quoteA = quotaX & 0x0F;
            quoteB = (quotaX >> 4) & 0x0F;
            waarde = 0;

            awaarde = getRegisterOrMemory(quoteA, BYTE_SIZE + BYTE_SIZE);
            bwaarde = getRegisterOrMemory(quoteB, BYTE_SIZE + BYTE_SIZE + calculateMemoryOffset(quoteA));
            unsigned long jumpwaarde = getNextInstructionDWord( BYTE_SIZE + BYTE_SIZE + calculateMemoryOffset(quoteA) + calculateMemoryOffset(quoteB) );
            
            cpu.currentProcess->register_isp += ( BYTE_SIZE + BYTE_SIZE + DWORD_SIZE + calculateMemoryOffset(quoteA) + calculateMemoryOffset(quoteB));

            if(awaarde==bwaarde){
                cpu.currentProcess->register_isp = jumpwaarde;
            }
            break;
        case CPU_INSTRUCTION_CMP_EQU_N:
            teen_print("handle_cpu_instruction info: compare and jump if not equals\n");
            quotaX = getNextInstructionByte(BYTE_SIZE);
            quoteA = quotaX & 0x0F;
            quoteB = (quotaX >> 4) & 0x0F;
            waarde = 0;

            awaarde = getRegisterOrMemory(quoteA, BYTE_SIZE + BYTE_SIZE);
            bwaarde = getRegisterOrMemory(quoteB, BYTE_SIZE + BYTE_SIZE + calculateMemoryOffset(quoteA));
            jumpwaarde = getNextInstructionDWord( BYTE_SIZE + BYTE_SIZE + calculateMemoryOffset(quoteA) + calculateMemoryOffset(quoteB) );
            
            cpu.currentProcess->register_isp += ( BYTE_SIZE + BYTE_SIZE + DWORD_SIZE + calculateMemoryOffset(quoteA) + calculateMemoryOffset(quoteB));

            if(awaarde!=bwaarde){
                cpu.currentProcess->register_isp = jumpwaarde;
            }
            break;
        default:
            teen_print("handle_cpu_instruction error: invalid opcode: ");
            teen_print_char_as_hex(currentInstruction);
            teen_print(" \n");
            cpu.state = CPU_STATE_PANICK;
            break;
    }
}

/*
    The main routine
    @param argc the ammount of arguments
    @param argv the arguments itself
    @result the result of the execution
*/
int main(int argc,char** argv){
    int pid = install_process((unsigned long)&dummydata);
    cpu.currentProcess = (Process*)(&processes[pid]);
    cpu.state = CPU_STATE_RUNNING;
    while(cpu.state==CPU_STATE_RUNNING){
        handle_cpu_instruction();
    }
    teen_print("main: end of execution.\n");
    teen_print("main: registers: EAX: ");
    teen_print_char_as_hex(cpu.currentProcess->register_eax);
    teen_print(" EBX: ");
    teen_print_char_as_hex(cpu.currentProcess->register_ebx);
    teen_print(" ECX: ");
    teen_print_char_as_hex(cpu.currentProcess->register_ecx);
    teen_print(" EDX: ");
    teen_print_char_as_hex(cpu.currentProcess->register_edx);
    teen_print(" EIP: ");
    teen_print_char_as_hex(cpu.currentProcess->register_isp);
    teen_print("\n\n");
    if(cpu.state==CPU_STATE_PANICK){
        teen_print("main: CPU state in panic!\n");
        return 1;
    }
    return 0;
}