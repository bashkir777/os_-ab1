#ifndef COMBINED_H
#define COMBINED_H
#include <pthread.h>

typedef struct {
    int type;  // Тип бенчмарка: 0 - bin_search, 1 - ema_search
    int array_size;
    int iterations;
    int target;
    char *filename;  // Для ema_search
} ThreadData;

void start_combined_benchmark();

#endif
