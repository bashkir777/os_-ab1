#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>

#include "ema-search-int/array_generator.h"
#include "ema-search-int/linear_search.h"
#include "shell/tools.h"

void start_ema_search_int(int iterations, size_t array_size, char *filename, int target) {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    generate_array(array_size, filename);

    int position = -1;
    for (int i = 0; i < iterations; i++) {
        position = linear_search(filename, target);
    }

    if (position != -1) {
        printf("Target has been found. Position: %d\n", position);
    } else {
        printf("Target has not been found.\n");
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = calculate_time_diff(start_time, end_time);
    
    printf("Execution time: %.6f seconds\n", elapsed_time);
    fflush(stdout);
}
