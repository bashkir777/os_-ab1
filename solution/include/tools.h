#ifndef TOOLS_H
#define TOOLS_H
#define CD cd
#define BUFFER_SIZE 1024
enum OPERATION_STATUS{
    SUCCESS,
    ERROR,
    NOT_FOUND
};

enum OPERATION_STATUS get_env_var(const char *var_name, char **ret);

void parse_input(char* buffer, char** command, char** args);

#endif
