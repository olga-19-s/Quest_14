#include "bin.h"

void outputData(Data *a) {
    printf("%d ", a->year);
    printf("%d ", a->month);
    printf("%d ", a->day);
    printf("%d ", a->hour);
    printf("%d ", a->minute);
    printf("%d ", a->sec);
    printf("%d ", a->status);
    printf("%d", a->code);
    printf("\n");
}

int cmp(Data *a, Data *b) {
    int *ai = (int *)a;
    int *bi = (int *)b;
    for (int i = 0; i < 6; ++i) {
        if (*ai != *bi) {
            if (*ai < *bi) {
                return -1;
            } else {
                return 1;
            }
        }
        ++ai;
        ++bi;
    }
    return 0;
}


int inputData(Data *a) {
    int flag = 1;
    if (scanf("%d", &a->year) != 1) {
        flag = 0;
    }
    if (scanf("%d", &a->month) != 1) {
        flag = 0;
    }
    if (scanf("%d", &a->day) != 1) {
        flag = 0;
    }
    if (scanf("%d", &a->hour) != 1) {
        flag = 0;
    }
    if (scanf("%d", &a->minute) != 1) {
        flag = 0;
    }
    if (scanf("%d", &a->sec) != 1) {
        flag = 0;
    }
    if (scanf("%d", &a->status) != 1) {
        flag = 0;
    }
    if (scanf("%d", &a->code) != 1) {
        flag = 0;
    }
    return flag;
}
