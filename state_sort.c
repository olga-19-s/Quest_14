#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bin.h"

void sort(FILE *file, int count);

int main() {
    char filePath[100];
    FILE *file;
    Data *data = malloc(sizeof(Data));
    int mode = -2;
    scanf("%s", filePath);
    fflush(stdin);
    scanf("%d", &mode);
    switch (mode) {
    case 0:
        if ((file = fopen(filePath, "r+b")) == NULL) {
            printf("n/a\n");
        } else {
            fseek(file, 0, SEEK_END);
            if (!ftell(file)) {
                printf("n/a\n");
            } else {
                rewind(file);
                while (fread(data, sizeof(Data), 1, file) != 0) {
                    outputData(data);
                }
            }
            fclose(file);
        }
        break;
    case 1:
        if ((file = fopen(filePath, "r+b")) == NULL) {
            printf("n/a\n");
        } else {
            fseek(file, 0, SEEK_END);
            if (!ftell(file)) {
                printf("n/a\n");
            } else {
                fseek(file, 0, SEEK_END);
                int count = ftell(file) / sizeof(Data);
                sort(file, count);
                rewind(file);
                while (fread(data, sizeof(Data), 1, file) != 0) {
                    outputData(data);
                }
            }
            fclose(file);
        }
        break;
    case 2:
        if ((file = fopen(filePath, "r+b")) == NULL) {
            printf("n/a\n");
        } else {
            if (!inputData(data)) {
               printf("n/a\n");
            } else {
                outputData(data);
                fseek(file, 0, SEEK_END);
                fwrite(data, sizeof(Data), 1, file);
                fseek(file, 0, SEEK_END);
                int count = ftell(file) / sizeof(Data);
                sort(file, count);
                while (fread(data, sizeof(Data), 1, file) != 0) {
                    outputData(data);
                }
            }
            fclose(file);
        }
        break;
    default:
        printf("n/a\n");
        break;
    }
    free(data);
    return 0;
}

void sort(FILE *file, int count) {
    Data data1, data2;
    for (int i = count; i > 0; --i) {
        for (int j = 0; j < i - 1; ++j) {
            fseek(file, j * sizeof(Data), SEEK_SET);
            fread(&data1, sizeof(Data), 1, file);
            fread(&data2, sizeof(Data), 1, file);
            if (cmp(&data1, &data2) == 1) {
                fseek(file, j * sizeof(Data), SEEK_SET);
                fwrite(&data2, sizeof(Data), 1, file);
                fwrite(&data1, sizeof(Data), 1, file);
            }
        }
    }
    rewind(file);
}
