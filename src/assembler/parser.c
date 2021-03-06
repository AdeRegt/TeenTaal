#include <stdio.h>
#include <stdlib.h>
#include "headers/core.h"

struct CommandoArgumentIn *first;
struct CommandoArgumentIn *current;

int pointer = 0;
int internalpointer = 0;
int row = 1;

void parser_reset_pointer(){
    if(internalpointer!=0||(internalpointer==0&&current->is_string==1)){
        struct CommandoArgumentIn* tmp1 = (struct CommandoArgumentIn*) malloc(sizeof(struct CommandoArgumentIn));
        current->next = tmp1;
        tmp1->previous = current;
        current = tmp1;
        internalpointer = 0;
        current->row = row;
        current->is_string = 0;
    }
}

struct CommandoArgumentIn *parseSourceFile(){
    first = (struct CommandoArgumentIn*) malloc(sizeof(struct CommandoArgumentIn));
    current = first;
    current->row = row;
    while(pointer<getFileSize()){
        char deze = getSourceFileBuffer()[pointer++];
        if(deze=='\n'){
            parser_reset_pointer();
            row++;
            current->row = row;
        }else if(deze==' '&&current->is_string==0){
            parser_reset_pointer();
        }else if(deze=='\"'){
            int last = current->is_string;
            parser_reset_pointer();
            current->is_string = last==0;
        }else if(internalpointer<MAX_VARIABLE_SIZE){
            current->message[internalpointer++] = deze;
        }else{
            syntaxError(current,"string is too large");
        }
    }
    parser_reset_pointer();

    // get rid of the last pointer if is empty
    if(current->message[0]==0){
        struct CommandoArgumentIn *prev = current->previous;
        prev->next = 0;
        free(current);
        current = 0;
    }
    return first;
}