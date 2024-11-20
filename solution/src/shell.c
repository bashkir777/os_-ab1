#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "external_commands.h"
#include "built_in_commands.h"
#include "tools.h"
#define BUFFER_SIZE 1024

void read_command(char* buffer){
    ssize_t bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
    if (bytesRead < 0) {
        perror("read");
        return;
    }

    buffer[bytesRead] = '\0';
}

void single_command_execution(char* buffer){
    
    char* command = NULL;
    char* args = NULL;

    prepare_command(buffer, &command, &args);

    bool command_is_built_in = handle_command(command, args);
    if (!command_is_built_in) {
        handle_external_command(command, args);
    }
    fflush(stdout);
}

void start_shell(char* buffer){
    while (true) {
        char* cur_dir;
        get_env_var("PWD", &cur_dir);
        printf("%s> ", cur_dir);
        fflush(stdout);
        read_command(buffer);
        single_command_execution(buffer);
    }
}
