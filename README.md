# TeenTaal
Virtual Machine for the TeenTaal.
In Dutch, Teen means toe and Taal means language.
So, TeenTaal means ToeLanguage.

# Building
Requirements: 
* GCC
Go to the OS folder to see the supported build methods for your OS

# Instructionset
| Opcode | Name | Comments |
| ------ | ---- | -------- |
| 0x00 | HLT | Halts execution |
| 0x01 | JMP addr | Jumps to DWORD |
| 0x02 | CALL addr | Calls DWORD |
| 0x03 | RET | Returns from a call |
| 0x05 | SET method source dest | Copies a value from memory to register, register to memory, register to register or memory to memory |
| 0x06 | ADD method dest ammount | Adds ammount to destination |
| 0x07 | SUB method dest ammount | Substracts ammount from destination |
| 0x08 | DIV method dest ammount | Devide destination to amount |
| 0x09 | MUL method dest ammount | Multiply destination with amount | 
| 0x0A | INC method dest | Increases the value in dest by 1 |
| 0x0B | DEC method dest | Decreases the value in dest by 1 |
| 0x0C | CMPE method arg1 arg2 location | Checks if arg1 is equal to arg2 if yes go to location |
| 0x0D | CMPNE method arg1 arg2 location | Checks if arg1 is not equal to arg2 if yes go to location |

Values for method:
| Opcode | Comment |
| ------ | ------- |
| 0x1 | Register EAX |
| 0x2 | Register EBX |
| 0x3 | Register ECX |
| 0x4 | Register EDX |
| 0x5 | Raw byte stored at memorylocation |
| 0x6 | Raw word stored at memorylocation |
| 0x7 | Raw dword stored at memorylocation |
| 0x8 | Raw byte stored at value |
| 0x9 | Raw word stored at value |
| 0xA | Raw dword stored at value |