/**
 * @brief Parser structure
 * 
 */
typedef struct CommandoArgumentIn{
    /**
     * @brief The content of the message
     * 
     */
    char message[255];
    /**
     * @brief Row in the sourcefile
     * 
     */
    int row;
    /**
     * @brief Check if this is a string or not
     * 
     */
    int is_string;
    /**
     * @brief The previous object
     * 
     */
    struct CommandoArgumentIn *previous;
    /**
     * @brief The next object
     * 
     */
    struct CommandoArgumentIn *next;
}CommandoArgumentIn;

/**
 * @brief Lexer structure
 * 
 */
typedef struct OpcodeObject{
    /**
     * @brief Opcode 0xF000 args 0x0FFF
     * 
     */
    short opcode;
    /**
     * @brief Command which caused this
     * 
     */
    struct CommandoArgumentIn *command;
    /**
     * @brief Command where the function is defined
     * 
     */
    struct CommandoArgumentIn *function;
    /**
     * @brief Previous opcode command
     * 
     */
    struct OpcodeObject *previous;
    /**
     * @brief Next opcode command
     * 
     */
    struct OpcodeObject *next;
}OpcodeObject;

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

struct OpcodeObject *createAST(struct CommandoArgumentIn *head);
void syntaxError(struct CommandoArgumentIn *anchor,char* msg);
void link(struct OpcodeObject* head);
void output(struct OpcodeObject* head,FILE* outputfile);