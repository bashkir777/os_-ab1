#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../include/shell/tools.h"

static void handle_echo(const char* args) {
    printf("%s\n", args);
}

static void handle_cd(const char* path) {
    if (chdir(path) == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            setenv("PWD", cwd, 1); 
        } else {
            printf("getcwd failed");
        }
    }else{
        printf("Error: No such file or directory.\n");
    }
}


static void handle_exit() {
    exit(0);
}

static void handle_pwd() {
    char* cur_dir;
    get_env_var("PWD", &cur_dir);
    printf("%s\n", cur_dir);
}



bool handle_command(const char* command, const char* args) {
    if (strcmp(command, "echo") == 0) {
        handle_echo(args);
    } else if (strcmp(command, "cd") == 0) {
        handle_cd(args);
    }else if (strcmp(command, "exit") == 0) {
        handle_exit();
    }else if (strcmp(command, "pwd") == 0) {
        handle_pwd();
    } else {
        return false;
    }
    fflush(stdout);
    return true;
}
