#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

bool handle_external_command(char* command, char* args) {
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return false;
    }

    if (pid == 0) {
        char* args_array[64];
        int i = 0;
        args_array[i++] = command;
        char* arg = strtok(args, " ");
        while (arg != NULL) {
            args_array[i++] = arg;
            arg = strtok(NULL, " ");
        }
        args_array[i] = NULL;
        execvp(command, args_array);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        return true;
    }
}
