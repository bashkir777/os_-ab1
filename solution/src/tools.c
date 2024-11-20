#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "../include/tools.h"

extern char **environ;

enum OPERATION_STATUS get_env_var(const char *var_name, char **ret) {
    if (var_name == NULL || ret == NULL) {
        return ERROR;
    }

    for (char **env = environ; *env != 0; env++) {
        char *thisEnv = *env;
        char *equal_sign = strchr(thisEnv, '=');
        if (equal_sign) {
            size_t name_len = equal_sign - thisEnv;
            if (strncmp(thisEnv, var_name, name_len) == 0 && name_len == strlen(var_name)) {
                *ret = strdup(equal_sign + 1);
                return SUCCESS;
            }
        }
    }
    return NOT_FOUND;

}

void prepare_command(char* buffer, char** command, char** args) {
    buffer[strcspn(buffer, "\n")] = '\0';
    *command = strtok(buffer, " ");
    *args = strtok(NULL, "");
}