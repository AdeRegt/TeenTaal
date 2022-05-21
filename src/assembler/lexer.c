#include <stdio.h>
#include <stdlib.h>
#include "headers/core.h"

struct CommandoArgumentIn *commando_argument_head;
struct OpcodeObject *opcode_head;

struct OpcodeObject *createAST(struct CommandoArgumentIn *head){
    commando_argument_head = head;
    return opcode_head;
}