#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ema-search-int/linear_search.h"
#include <mru_cache.h>
#include <mru_api.h>

int linear_search(int target, MRUCache* cache) {
    // Читаем данные из кэша
    int data[MRU_CACHE_BLOCK_SIZE];
    off_t block_number = 0;

    while (1) {
        // Пытаемся прочитать блок из кэша
        enum READ_CACHE_RESULT result = read_from_cache(cache, block_number, data);
        if (result == READ_CACHE_MISS) {
            // Если данные не найдены в кэше, читаем их из файла
            if (lseek(cache->fd, block_number * MRU_CACHE_BLOCK_SIZE * sizeof(int), SEEK_SET) == -1) {
                perror("lseek");
                return -1;
            }

            if (read(cache->fd, data, MRU_CACHE_BLOCK_SIZE * sizeof(int)) == -1) {
                perror("read");
                return -1;
            }

            // Добавляем данные в кэш
            if (write_to_cache(cache, block_number, data) == WRITE_CACHE_FAILURE) {
                perror("write_to_cache");
                return -1;
            }
        }

        // Ищем целевое значение в текущем блоке
        for (size_t i = 0; i < MRU_CACHE_BLOCK_SIZE; i++) {
            if (data[i] == target) {
                return block_number * MRU_CACHE_BLOCK_SIZE + i;
            }
        }

        block_number++;
    }

    return -1;
}
