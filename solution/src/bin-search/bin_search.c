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


void *thread_binary_search(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    for(int i = 0; i < data->iterations; i++){
        data->result = binary_search(&data->array[data->start_index], data->end_index - data->start_index, data->target);
    }
    if (data->result != -1) {
        data->result += data->start_index;
    }
    return NULL;
}

void start_bin_search_benchmark_multithreaded(int array_size, int iterations, int target, int num_threads) {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    int *in_memory_array = malloc(sizeof(int) * array_size);
    generate_sorted_array(in_memory_array, array_size);

    pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
    ThreadData *thread_data = malloc(sizeof(ThreadData) * num_threads);

    size_t chunk_size = array_size / num_threads;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].array = in_memory_array;
        thread_data[i].start_index = i * chunk_size;
        thread_data[i].end_index = (i == num_threads - 1) ? array_size : (i + 1) * chunk_size;
        thread_data[i].target = target;
        thread_data[i].iterations = iterations;
        pthread_create(&threads[i], NULL, thread_binary_search, &thread_data[i]);
    }

    int position = -1;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        if (thread_data[i].result != -1) {
            position = thread_data[i].result;
        }
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
    free(threads);
    free(thread_data);
}
