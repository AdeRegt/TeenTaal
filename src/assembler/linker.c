#include <stdio.h>
#include <stdlib.h>
#include "headers/core.h"

struct OpcodeObject *link_head;

void link(struct OpcodeObject* head){
    link_head = head;
}