#ifndef SORT_DATA_H
#define SORT_DATA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define RECORD_STRING_SIZE 95 // Specified String Length

typedef unsigned long int32b; // 32-bit number from 0 to 2^32 - 1

struct record {
    int32b myInt;
    char* myString;
}; // Record structure


// Comparing two records
int cmp(const struct record a, const struct record b) {
    if(a.myInt > b.myInt) return 1;
    if(a.myInt < b.myInt) return -1;
    return 0;
}

// Swaping elements in 
void swap(struct record *a, struct record *b) {
  struct record t = *a;
  *a = *b;
  *b = t;
}

#endif