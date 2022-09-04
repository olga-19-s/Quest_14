#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bin.h"

int cmpTime(Data *data, int *time);

int main() {
    char filePath[100];
    FILE *file;
    Data *data = malloc(sizeof(Data));
    char time[20];
    scanf("%s", filePath);
    fflush(stdin);
    scanf("%s", time);
    if ((file = fopen(filePath, "r+b")) == NULL) {
        printf("n/a\n");
    } else {
        fseek(file, 0, SEEK_END);
        if (!ftell(file)) {
            printf("n/a\n");
        } else {
            rewind(file);
            int t[3], flag = 1;
            char *n = strtok(time, ".");
            if (n == NULL) {
                fclose(file);
                printf("n/a");
                free(data);
                return 0;
            }
            t[0] = atoi(n);
            for (int i = 1; i < 3; ++i) {
                n = strtok(NULL, ".");
                if (n == NULL) {
                    fclose(file);
                    free(data);
                    printf("n/a");
                    return 0;
                }
                t[i] = atoi(n);
            }
            if (t[0] <= 0 || t[1] <= 0 || t[2] <= 0) {
                fclose(file);
                free(data);
                printf("n/a");
                return 0;
            }
            while ((fread(data, sizeof(Data), 1, file) != 0) && (flag == 1)) {
                flag = cmpTime(data, t);
                if (flag == 0) {
                    printf("%d", data->code);
                    break;
                }
            }
            if (flag == 1) {
                printf("n/a");
            }
        }
        fclose(file);
    }
    free(data);
    return 0;
}

int cmpTime(Data *data, int *time) {
    if ((data->year == time[2]) &&
        (data->month == time[1]) &&
        (data->day == time[0])) {
            return 0;
        }
    return 1;
}
