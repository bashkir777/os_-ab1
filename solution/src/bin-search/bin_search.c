#define _GNU_SOURCE
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "bin-search/sorted_array_generator.h"
#include "bin-search/bin_search.h"
#include "shell/tools.h"

int binary_search(const int *array, size_t size, int target) {
    size_t left = 0;
    size_t right = size;

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (array[mid] == target) {
            return (int)mid;
        } else if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return -1;
}

void start_bin_search_benchmark(int array_size, int iterations, int target){
    
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);


    int* in_memory_array = malloc(sizeof(int) * array_size);
    generate_sorted_array(in_memory_array, array_size);
    int position = -1;
    for(int i = 0; i < iterations; i++){
        position = binary_search(in_memory_array, array_size, target);
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

    free(in_memory_array);
}

