#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

InputStatus read_line(char *buffer, const int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        const size_t LENGTH = strlen(buffer);
        // printf("\n [debugging] buffer: [%s], length: %i\n", buffer, LENGTH);
        if (LENGTH > 0 && !(buffer[LENGTH-1] == '\n' || buffer[LENGTH-1] == EOF)) {
            //drop line that didn't fit into buffer
            int c;
            while (( c = fgetc(stdin)) != '\n' && c != EOF) {};
            // printf("\n [debugging] Emptied stdin\n");
            return INPUT_INVALID;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        return INPUT_OK;
    }
    return INPUT_EOF;
}

bool get_int(const char *str, int *out, int min, int max) {
    char *err;
    const size_t parsed = strtol(str, &err, 10);
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
    if (parsed > (size_t)max) return false;
    if (parsed < (size_t)min) return false;
    *out = (int)parsed;
    return true;
}

InputStatus prompt_string(const char *prompt, char *out, const int SIZE) {
    printf("%s", prompt);
    const InputStatus status =  read_line(out, SIZE);
    if (out[0] == '\0') {
        return INPUT_INVALID;
    }
    return status;
}

InputStatus prompt_int(const char *prompt, int *out, const int min, const int max) {
    printf("%s", prompt);
    constexpr int SIZE = 32;
    char input[SIZE];
    InputStatus status;
    if ((status = read_line(input, SIZE)) == INPUT_EOF || status == INPUT_INVALID) {
        return status;
    }

    const bool is_parsed = get_int(input, out, min, max);
    if (is_parsed) {
        return INPUT_OK;
    }
    return INPUT_INVALID;
}
