
#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

int binary_search(const int *array, size_t size, int target);
void start_bin_search_benchmark(int array_size, int iterations, int target);
void start_bin_search_benchmark_multithreaded(int array_size, int iterations, int target, int num_threads);

typedef struct {
    int *array;
    size_t start_index;
    size_t end_index;
    int target;
    int result;
    int iterations;
} ThreadData;

#endif
