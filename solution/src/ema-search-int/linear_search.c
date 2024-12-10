#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ema-search-int/linear_search.h"

int linear_search(const char *filename, int target) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("fopen");
        return false;
    }

    int buffer[BLOCK_SIZE];
    size_t read_count;

    while ((read_count = fread(buffer, sizeof(int), BLOCK_SIZE, file)) > 0) {
        for (size_t i = 0; i < read_count; i++) {
            if (buffer[i] == target) {
                fclose(file);
                return i;
            }
        }
    }

    fclose(file);
    return -1;
}
