#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/built_in_commands.h"
#include "../include/external_commands.h"
#include "../include/tools.h"

#define BUFFER_SIZE 1024

int main(int argc, char** argv) {
    char buffer[BUFFER_SIZE];

    while (true) {
        char* cur_dir;
        get_env_var("PWD", &cur_dir);
        printf("%s> ", cur_dir);
        fflush(stdout);

        ssize_t bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        if (bytesRead < 0) {
            perror("read");
            continue;
        }

        buffer[bytesRead] = '\0';

        char* command = NULL;
        char* args = NULL;

        parse_input(buffer, &command, &args);

        bool command_is_built_in = handle_command(command, args);
        if (!command_is_built_in) {
            handle_external_command(command, args);
        }
    }
}
