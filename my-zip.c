#include <stdint.h>
#include <stdio.h>
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

static int write_run(uint32_t count, unsigned char value)
{
    if (fwrite(&count, sizeof(count), 1, stdout) != 1) {
        return 1;
    }

    if (fwrite(&value, sizeof(value), 1, stdout) != 1) {
        return 1;
    }

    return 0;
}

static int zip_stream(FILE *stream, int *have_run, unsigned char *current, uint32_t *count)
{
    int c;

    while ((c = fgetc(stream)) != EOF) {
        unsigned char value = (unsigned char)c;

        if (!(*have_run)) {
            *have_run = 1;
            *current = value;
            *count = 1;
        } else if (value == *current && *count < UINT32_MAX) {
            (*count)++;
        } else {
            if (write_run(*count, *current) != 0) {
                return 1;
            }
            *current = value;
            *count = 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
#ifdef _WIN32
    /* Ensure stdout is in binary mode on Windows to avoid CRLF translation */
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    int i;
    int have_run = 0;
    unsigned char current = 0;
    uint32_t count = 0;

    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");

        if (fp == NULL) {
            printf("my-zip: cannot open file\n");
            return 1;
        }

        if (zip_stream(fp, &have_run, &current, &count) != 0) {
            fclose(fp);
            return 1;
        }

        fclose(fp);
    }

    if (have_run && write_run(count, current) != 0) {
        return 1;
    }

    return 0;
}