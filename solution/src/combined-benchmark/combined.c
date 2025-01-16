#define _GNU_SOURCE
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "combined-benchmark/combined.h"
#include "ema-search-int/linear_search.h"
#include "ema-search-int/array_generator.h"
#include "bin-search/sorted_array_generator.h"
#include "bin-search/bin_search.h"
#include "shell/tools.h"

void *start_bin_search_benchmark_thread(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    int *in_memory_array = malloc(sizeof(int) * data->array_size);
    generate_sorted_array(in_memory_array, data->array_size);
    int position = -1;
    for (int i = 0; i < data->iterations; i++) {
        position = binary_search(in_memory_array, data->array_size, data->target);
    }
    if (position != -1) {
        printf("Binary Search: Target has been found. Position: %d\n", position);
    } else {
        printf("Binary Search: Target has not been found.\n");
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = calculate_time_diff(start_time, end_time);

    printf("Binary Search Execution time: %.6f seconds\n", elapsed_time);
    fflush(stdout);

    free(in_memory_array);
    return NULL;
}

void *start_ema_search_int_thread(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    generate_array(data->array_size, data->filename);

    int position = -1;
    for (int i = 0; i < data->iterations; i++) {
        position = linear_search(data->filename, data->target);
    }

    if (position != -1) {
        printf("EMA Search: Target has been found. Position: %d\n", position);
    } else {
        printf("EMA Search: Target has not been found.\n");
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = calculate_time_diff(start_time, end_time);

    printf("EMA Search Execution time: %.6f seconds\n", elapsed_time);
    fflush(stdout);

    return NULL;
}

void start_combined_benchmark () {
    int bin_search_array_size = 200000;
    int bin_search_iterations = 300000000;
    int bin_search_target = 18;
  
    int ema_search_array_size = 67108864;
    int ema_search_iterations = 1;
    int ema_search_target = 666;
    char *ema_search_filename = "array.bin";

    pthread_t bin_search_thread, ema_search_thread;

    ThreadData bin_search_data = {
        .type = 0,
        .array_size = bin_search_array_size,
        .iterations = bin_search_iterations,
        .target = bin_search_target,
        .filename = NULL
    };

    ThreadData ema_search_data = {
        .type = 1,
        .array_size = ema_search_array_size,
        .iterations = ema_search_iterations,
        .target = ema_search_target,
        .filename = ema_search_filename
    };

    pthread_create(&bin_search_thread, NULL, start_bin_search_benchmark_thread, &bin_search_data);
    pthread_create(&ema_search_thread, NULL, start_ema_search_int_thread, &ema_search_data);

    pthread_join(bin_search_thread, NULL);
    pthread_join(ema_search_thread, NULL);

}
