#include "../../dependancies.h"
#include "stdio.h"
#include "stdlib.h"

void teen_print(const char* message){
    printf("%s",message);
}

void teen_print_char_as_hex(unsigned char character){
    printf("%x",character);
}

void *loadSourceFile(char* path){
    FILE* file = fopen(path,"r");
    if(file){
        void *locatie = 0;
        fseek(file,0,SEEK_END);
        unsigned long size = ftell(file);
        rewind(file);
        locatie = malloc(size);
        fread(locatie,size,1,file);
        fclose(file);
        return locatie;
    }
    return (void *)RES_ERROR;
}