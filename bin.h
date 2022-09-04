#ifndef SRC_BIN_H_
#define SRC_BIN_H_
#include <stdio.h>

typedef struct data {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    int status;
    int code;
} Data;

void outputData(Data *a);
int cmp(Data *a, Data *b);
int inputData(Data *a);

#endif  // SRC_BIN_H_
