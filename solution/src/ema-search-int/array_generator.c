#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/ema-search-int/array_generator.h"

int generate_array(size_t size, char* filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        int num = rand() % 1000000;
        fwrite(&num, sizeof(int), 1, file);
    }

    fclose(file);
    printf("Array generated and saved to file: %s\n", filename);
    return 0;
}
