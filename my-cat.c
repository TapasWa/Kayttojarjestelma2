#include <stdio.h>

static int copy_stream(FILE *stream)
{
    int c;

    while ((c = fgetc(stream)) != EOF) {
        if (putchar(c) == EOF) {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        return 0;
    }

    for (i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL) {
            printf("my-cat: cannot open file\n");
            return 1;
        }

        if (copy_stream(fp) != 0) {
            fclose(fp);
            return 1;
        }

        fclose(fp);
    }

    return 0;
}