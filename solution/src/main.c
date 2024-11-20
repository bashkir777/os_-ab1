#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "../include/shell/built_in_commands.h"
#include "../include/shell/external_commands.h"
#include "../include/shell/shell.h"
#include "../include/shell/tools.h"
#include "../include/ema-search-int/array_generator.h"
#include "../include/ema-search-int/tools.h"
#include "../include/ema-search-int/linear_search.h"
#include "../include/ema-search-int/ema_search_int.h"

int main(int argc, char **argv) {
    char buffer[BUFFER_SIZE];

    if (argc < 2) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  To use shell: shell 1 || shell 1 <command>\n");
        fprintf(stderr, "  To use ema-search-int benchmark: shell 2 <iterations> <array size> <filename> <target>\n");
        exit(EXIT_FAILURE);
    }

    bool shell_mode = strcmp(argv[1], "1") == 0;
    bool ema_search_int_benchmark_mode = strcmp(argv[1], "2") == 0;

    if (shell_mode && argc == 2) {
        start_shell(buffer);
    } else if (shell_mode) {
        string_from_string_arr(buffer, BUFFER_SIZE, argc, 2, argv);
        single_command_execution(buffer);
    }

    if (ema_search_int_benchmark_mode && argc == 6) {
        size_t array_size = parse_size(argv[3]);
        int iterations = (int)parse_size(argv[2]);
        int target = (int)parse_size(argv[5]);
        char *filename = argv[4];
        start_ema_search_int(iterations, array_size, filename, target);
    } else if (ema_search_int_benchmark_mode) {
        fprintf(stderr, "Invalid arguments for ema-search-int benchmark:\n");
        fprintf(stderr, "Usage: shell 2 <iterations> <array size> <filename> <target>\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
