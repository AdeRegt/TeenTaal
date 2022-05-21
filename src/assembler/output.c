#include <stdio.h>
#include <stdlib.h>
#include "headers/core.h"

struct OpcodeObject *link_head;

void output(struct OpcodeObject* head,FILE* outputfile){
    link_head = head;
}