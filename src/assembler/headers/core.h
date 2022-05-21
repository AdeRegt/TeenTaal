typedef struct CommandoArgumentIn{
    char message[255];
    int row;
    int is_string;
    struct CommandoArgumentIn *previous;
    struct CommandoArgumentIn *next;
}CommandoArgumentIn;

struct CommandoArgumentIn *parseSourceFile();
int getFileSize();
char* getSourceFileBuffer();