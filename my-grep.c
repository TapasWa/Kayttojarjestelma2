#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_line(FILE *stream, char **buffer, size_t *capacity)
{
    size_t length = 0;
    int c = EOF;

    if (*buffer == NULL || *capacity == 0) {
        *capacity = 128;
        *buffer = malloc(*capacity);
        if (*buffer == NULL) {
            return -1;
        }
    }

    while ((c = fgetc(stream)) != EOF) {
        if (length + 1 >= *capacity) {
            size_t new_capacity = *capacity * 2;
            char *new_buffer = realloc(*buffer, new_capacity);

            if (new_buffer == NULL) {
                return -1;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[length++] = (char)c;

        if (c == '\n') {
            break;
        }
    }

    if (length == 0 && c == EOF) {
        return -1;
    }

    if (length + 1 >= *capacity) {
        size_t new_capacity = *capacity + 1;
        char *new_buffer = realloc(*buffer, new_capacity);

        if (new_buffer == NULL) {
            return -1;
        }

        *buffer = new_buffer;
        *capacity = new_capacity;
    }

    (*buffer)[length] = '\0';
    return (int)length;
}

static int grep_stream(FILE *stream, const char *needle)
{
    char *line = NULL;
    size_t capacity = 0;
    int line_length;

    while ((line_length = read_line(stream, &line, &capacity)) != -1) {
        if (needle[0] == '\0' || strstr(line, needle) != NULL) {
            if (fwrite(line, 1, (size_t)line_length, stdout) != (size_t)line_length) {
                free(line);
                return 1;
            }
        }
    }

    free(line);
    return 0;
}

int main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        printf("my-grep: searchterm [file ...]\n");
        return 1;
    }

    if (argc == 2) {
        return grep_stream(stdin, argv[1]);
    }

    for (i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL) {
            printf("my-grep: cannot open file\n");
            return 1;
        }

        if (grep_stream(fp, argv[1]) != 0) {
            fclose(fp);
            return 1;
        }

        fclose(fp);
    }

    return 0;
}