#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/core.h"

struct CommandoArgumentIn *commando_argument_head;
struct CommandoArgumentIn *current;
struct OpcodeObject *opcode_head;
struct OpcodeObject *opcode_current;

int node_is_function(struct CommandoArgumentIn *ods){
    int z = 0;
    for(z = 0 ; z < MAX_VARIABLE_SIZE ; z++){
        if(ods->message[z]==':'){
            return 1;
        }
    }
    return 0;
}

void lexer_reset_pointer(){
    struct OpcodeObject* tmp1 = (struct OpcodeObject*) malloc(sizeof(struct OpcodeObject));
    tmp1->function = opcode_current->function;
    opcode_current->next = tmp1;
    tmp1->previous = opcode_current;
    opcode_current = tmp1;
}

struct OpcodeObject *createAST(struct CommandoArgumentIn *head){
    commando_argument_head = head;
    current = commando_argument_head;
    opcode_head = (struct OpcodeObject*) malloc(sizeof(struct OpcodeObject));
    opcode_current = opcode_head;
    while(current){
        if(current->is_string){
            syntaxError(current,"You cannot start a line with a string");
        }else if(node_is_function(current)){
            opcode_current->function = current;
        }else if(strcmp(current->message,RET_NAME)==0){
            opcode_current->opcode = RET_OPCODE;
            lexer_reset_pointer();
            opcode_current->function = 0;
        }else{
            syntaxError(current,"Unexpected token");
        }
        current = current->next;
    }
    return opcode_head;
}