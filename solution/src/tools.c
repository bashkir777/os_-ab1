#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "../include/tools.h"

extern char **environ;

enum OPERATION_STATUS get_env_var(const char *var_name, char **ret) {
    if (var_name == NULL || ret == NULL) {
        return ERROR;
    }

    for (char **env = environ; *env != 0; env++) {
        char *thisEnv = *env;
        char *equal_sign = strchr(thisEnv, '=');
        if (equal_sign) {
            size_t name_len = equal_sign - thisEnv;
            if (strncmp(thisEnv, var_name, name_len) == 0 && name_len == strlen(var_name)) {
                *ret = strdup(equal_sign + 1);
                return SUCCESS;
            }
        }
    }
    return NOT_FOUND;

}

void prepare_command(char* buffer, char** command, char** args) {
    buffer[strcspn(buffer, "\n")] = '\0';
    *command = strtok(buffer, " ");
    *args = strtok(NULL, "");
}

void string_from_string_arr(char* out_string, size_t out_size, int arr_len, int start_index, char** arr) {
    out_string[0] = '\0'; // Начинаем с пустой строки

    for (int i = start_index; i < arr_len; i++) {
        size_t remaining_space = out_size - strlen(out_string) - 1; // Вычисляем оставшееся место с учётом терминального символа '\0'
        strncat(out_string, arr[i], remaining_space); // Безопасно добавляем следующий элемент массива

        if (i < arr_len - 1) {
            remaining_space = out_size - strlen(out_string) - 1; // Пересчитываем оставшееся место
            strncat(out_string, " ", remaining_space); // Добавляем пробел, если это не последний элемент
        }
    }
}
