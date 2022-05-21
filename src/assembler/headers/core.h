typedef struct CommandoArgumentIn{
    char message[255];
    int row;
    int is_string;
    struct CommandoArgumentIn *previous;
    struct CommandoArgumentIn *next;
}CommandoArgumentIn;

/**
 * @brief Parses the sourcefile and returns a linkedlist to the source
 * 
 * @return struct CommandoArgumentIn* 
 */
struct CommandoArgumentIn *parseSourceFile();

/**
 * @brief Get the File Size
 * 
 * @return int the size of the inputfile
 */
int getFileSize();

/**
 * @brief Get the Source File Buffer
 * 
 * @return char* the inputfilebuffer
 */
char* getSourceFileBuffer();