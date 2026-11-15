#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(char *buffer, const int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        return buffer;
    }
    return nullptr;
}

bool get_int(const char *str, int *out, int min, int max) {
    char *err;
    const int parsed = (int)strtol(str, &err, 10);
    if (err == str) {
        // printf("No digits were found.\n");
        return false;
    }
    if (*err != '\0') {
        // printf("Invalid character: %c\n", *err);
        return false;
    }

    // printf("The number is: %ld\n", parsed);
    //todo make max/min checks optional
    if (parsed > max) return false;
    if (parsed < min) return false;
    *out = parsed;
    return true;
}
