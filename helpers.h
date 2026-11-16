#ifndef HELPERS_H
#define HELPERS_H
char *read_line(char *buffer, int size);
bool get_int(const char *string, int *out, int min, int max);
bool prompt_int(const char *prompt, int *out, int min, int max);
#endif