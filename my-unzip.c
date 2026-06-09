#include <stdint.h>
#include <stdio.h>
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

static int unzip_stream(FILE *stream)
{
    while (1) {
        uint32_t count;
        unsigned char value;

        if (fread(&count, sizeof(count), 1, stream) != 1) {
            break;
        }

        if (fread(&value, sizeof(value), 1, stream) != 1) {
            return 1;
        }

        while (count > 0) {
            if (putchar(value) == EOF) {
                return 1;
            }
            count--;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
#ifdef _WIN32
    /* Ensure stdout is binary on Windows to avoid CRLF translation */
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    int i;

    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");

        if (fp == NULL) {
            printf("my-unzip: cannot open file\n");
            return 1;
        }

        if (unzip_stream(fp) != 0) {
            fclose(fp);
            return 1;
        }

        fclose(fp);
    }

    return 0;
}