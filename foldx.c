#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LENGTH 32767

typedef struct {
    unsigned short ll;
    unsigned short zz;
    unsigned char data[MAX_LENGTH];
} Record;

void foldx(const char *filename, int record_length, bool is_variable) {
    Record record = {0};

    FILE *input = fopen(filename, "rb");
    char output_filename[strlen(filename) + 2];
    sprintf(output_filename, "@%s", filename);
    FILE *output = fopen(output_filename, "wb");


    while (!feof(input) && !ferror(input)) {
        if (is_variable) {
            unsigned short len;
            fread(&len, sizeof(short), 1, input);
            // assume little endian)x86)
            {
                record.ll |= (len & 0xFF00) >> 8;
                record.ll |= (len & 0x00FF);
            }
            fseek(input, 2, SEEK_CUR);
            fread(record.data, sizeof(char), record.ll - 4, input);
            fwrite(&record.ll, sizeof(short), 1, output);
            fseek(output, 2, SEEK_CUR);
            fwrite(record.data, sizeof(char), record.ll - 4, output);
            fwrite("\r\n", sizeof(char), 2, output);
        } else {
            fread(record.data, sizeof(char), record_length, input);
            fwrite(record.data, sizeof(char), record_length, output);
            fwrite("\r\n", sizeof(char), 2, output);
        }
    }


    fclose(input);
    fclose(output);
}

int main(int argc, char *argv[]) {
    int opt;
    bool is_variable;
    int record_length;

    while ((opt = getopt(argc, argv, "l:")) != -1) {
        switch (opt) {
            case 'l':
                if (strcmp("v", optarg) == 0) {
                    is_variable = true;
                } else {
                    record_length = atoi(optarg);
                }
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s -l length filename\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    printf("is_variable:%d, record_length:%d, optind:%d, filename:%s\n",
           is_variable, record_length, optind, argv[optind]);

    foldx(argv[optind], record_length, is_variable);

    exit(EXIT_SUCCESS);
}
