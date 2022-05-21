#include <stdio.h>
#include <stdlib.h>
#include "headers/core.h"

char* argument_location;
FILE* file;
FILE* outputfile;
int file_size;
char *inputbuffer;

struct CommandoArgumentIn *root;
struct OpcodeObject *opcodetree;

void syntaxError(struct CommandoArgumentIn *anchor,char* msg){
    printf("Error in row %x : parse error: %s \n",anchor->row,msg);
    fclose(file);
    fclose(outputfile);
    exit(EXIT_FAILURE);
}

int getFileSize(){
    return file_size;
}

char* getSourceFileBuffer(){
    return inputbuffer;
}

int main(int argc,char** argv){
    printf("TeenTaalAssembler \n");
    printf("Copyright Alexandros de Regt \n");
    if(argc==2){
        argument_location = argv[1];
        printf("Inputfile %s \n",argument_location);
        file = fopen(argument_location,"r");
        if(!file){
            printf("Unable to open sourcefile\n");
            return EXIT_FAILURE;
        }
        outputfile = fopen("outputfile.sef","w");
        if(!outputfile){
            printf("Unable to open outputfile\n");
            return EXIT_FAILURE;
        }
        fseek(file,0,SEEK_END);
        file_size = ftell(file);
        printf("Inputfilesize %x \n",file_size);
        fseek(file,0,SEEK_SET);
        inputbuffer = (char*)malloc(file_size);
        fread(inputbuffer,file_size,1,file);

        root = parseSourceFile();
        opcodetree = createAST(root);
        link(opcodetree);
        output(opcodetree,outputfile);
        
        fclose(file);
        fclose(outputfile);
    }else{
        printf("Not enough parameters\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}