#ifndef HELPERS_H
#define HELPERS_H
typedef enum { INPUT_OK, INPUT_INVALID, INPUT_EOF, } InputStatus;
InputStatus read_line(char *buffer, int size);
bool get_int(const char *string, int *out, int min, int max);
InputStatus prompt_string(const char *prompt, char *out, int size);
InputStatus prompt_int(const char *prompt, int *out, int min, int max);
#endif