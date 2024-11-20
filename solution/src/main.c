#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/built_in_commands.h"
#include "../include/external_commands.h"
#include "../include/tools.h"
#include "../include/shell.h"


int main(int argc, char** argv) {
    
    char buffer[BUFFER_SIZE];

    if (argc < 2){
        perror("Usage: shell 1 || shell 1 <command>");
    }

    bool shell_mode = strcmp(argv[1], "1") == 0;

    if(shell_mode && argc == 2){
        start_shell(buffer);
    }else if(shell_mode){
        string_from_string_arr(buffer, argc, 2, argv);
        single_command_execution(buffer);
    }
    
}
