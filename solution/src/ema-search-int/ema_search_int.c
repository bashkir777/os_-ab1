#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ema-search-int/array_generator.h"
#include "ema-search-int/linear_search.h"
#include "shell/tools.h"
#include "mru_cache.h"
#include "mru_api.h"

void start_ema_search_int(int iterations, size_t array_size, char *filename, int target) {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    generate_array(array_size, filename);

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    MRUCache* cache = initialize_mru_cache(fd);
    if (cache == NULL) {
        perror("initialize_mru_cache");
        close(fd);
        return;
    }

    int position = -1;
    for (int i = 0; i < iterations; i++) {
        position = linear_search(target, cache);
    }

    if (position != -1) {
        printf("Target has been found. Position: %d\n", position);
    } else {
        printf("Target has not been found.\n");
    }

    // Закрываем кэш после завершения работы
    if (close_mru_cache(cache, true) != CLOSE_CACHE_SUCCESS) {
        perror("close_mru_cache");
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = calculate_time_diff(start_time, end_time);
    
    printf("Execution time: %.6f seconds\n", elapsed_time);
    fflush(stdout);
}
