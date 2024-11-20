#include <stdio.h>
#include "../../include/ema-search-int/array_generator.h"
#include "../../include/ema-search-int/linear_search.h"

void start_ema_search_int(int iterations, size_t array_size, char *filename, int target) {
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
}
