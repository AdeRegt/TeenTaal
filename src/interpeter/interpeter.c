#include <stdio.h>
#include <stdlib.h>

char* argument_location;
FILE* file;

int main(int argc,char** argv){
    printf("TeenTaalInterpeter \n");
    printf("Copyright Alexandros de Regt \n");
    if(argc==2){
        argument_location = argv[1];
        printf("Inputfile %s \n",argument_location);
        file = fopen(argument_location,"r");
        if(!file){
            printf("Unable to open sourcefile\n");
            return EXIT_FAILURE;
        }
        
        fclose(file);
    }else{
        printf("Not enough parameters\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}