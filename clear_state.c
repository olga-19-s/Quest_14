#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bin.h"

int cmpTime(Data *data, Data time);
void sort(FILE *file, int count);
void init(Data *a);

int main() {
    char filePath[100];
    FILE *file, *resFile;
    Data *data = malloc(sizeof(Data));
    scanf("%s", filePath);
    fflush(stdin);
    Data time1, time2;
    init(&time1);
    init(&time2);
    scanf("%2d.%2d.%4d", &time1.day, &time1.month, &time1.year);
    scanf("%2d.%2d.%4d", &time2.day, &time2.month, &time2.year);
    if (time1.day > 31 || time1.day <= 0 ||
        time2.day > 31 || time2.day <= 0 ||
        time1.month > 12 || time1.month <= 0 ||
        time2.month > 12 || time2.month <= 0 ||
        time1.year <= 0 || time2.year <= 0) {
        printf("n/a");
        return 0;
    }
    if ((file = fopen(filePath, "r+b")) == NULL) {
        printf("n/a\n");
    } else {
        fseek(file, 0, SEEK_END);
        int count = ftell(file);
        if (!count) {
            printf("n/a\n");
        } else {
            count = count / sizeof(Data);
            fseek(file, 0, SEEK_END);
            fwrite(&time1, sizeof(Data), 1, file);
            fwrite(&time2, sizeof(Data), 1, file);
            sort(file, count + 2);
            resFile = fopen("res", "wb");
            while (fread(data, sizeof(Data), 1, file) != 0 && cmpTime(data, time1)) {
                outputData(data);
                fwrite(data, sizeof(Data), 1, resFile);
            }
            while (fread(data, sizeof(Data), 1, file) != 0 && cmpTime(data, time2)) {
            }
            while (fread(data, sizeof(Data), 1, file) != 0) {
                outputData(data);
                fwrite(data, sizeof(Data), 1, resFile);
            }
            fclose(resFile);
            fclose(file);
            if ((resFile = fopen("res", "rb")) == NULL) {
                printf("n/a\n");
            } else {
                file = fopen(filePath, "wb");
                while (fread(data, sizeof(Data), 1, resFile) != 0) {
                    fwrite(data, sizeof(Data), 1, file);
                }
                fclose(resFile);
                fclose(file);
                remove("res");
            }
        }
    }
    free(data);
    return 0;
}

void init(Data *a) {
    a->year = 0;
    a->month = 0;
    a->day = 0;
    a->hour = 0;
    a->minute = 0;
    a->sec = 0;
    a->status = 0;
    a->code = 0;
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

int cmpTime(Data *data, Data time) {
    if (data->year == time.year && data->month == time.month &&
        data->day == time.day) {
            return 0;
    }
    return 1;
}
