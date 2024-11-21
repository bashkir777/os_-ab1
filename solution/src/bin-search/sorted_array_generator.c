#include <stdio.h>
#include <stdlib.h>

void generate_sorted_array(int *array, int size) {
    if(size < 0){
        perror("Array size must be a positive number");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        array[i] = (int)i;
    }
}
