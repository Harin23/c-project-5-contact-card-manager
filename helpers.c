#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(char *buffer, const int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        const int LENGTH = (int)strlen(buffer);
        printf("\n [debugging] buffer: [%s], length: %i\n", buffer, LENGTH);
        if (LENGTH > 0 && !(buffer[LENGTH-1] == '\n' || buffer[LENGTH-1] == EOF)) {
            //drop line didn't fit into buffer
            int c;
            while (( c = fgetc(stdin)) != '\n' && c != EOF) {};
            printf("\n [debugging] Emptied stdin\n");
        }else {
            buffer[strcspn(buffer, "\n")] = '\0';
        }
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
