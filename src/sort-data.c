#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define RECORD_STRING_SIZE 95 // Specified String Length

typedef unsigned long int32b; // 32-bit number from 0 to 2^32 - 1

int32b max_records = 1000; // Not defined as constant because we will be changing it if needed

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

// Finding partition position used in quick sort program
int partition(struct record array[], int low, int high) {
  
  // select the rightmost element as pivot
  struct record pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (cmp(array[j], pivot) <= 0) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

// Quick Sort program
void quickSort(struct record array[], int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

// Main function
int main(int argc, char** argv){
    // Usage
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Initializing start time
    clock_t t;
    t = clock();

    // Opening input file
    char* filename = argv[1];

    FILE *file;
    file = fopen(filename, "r");
    if(file == NULL) {
        printf("Could not open file %s\n", filename);
        return EXIT_FAILURE;
    }

    // Dynamically allocating data array
    struct record *data = malloc(max_records * sizeof(struct record));
    if(data == NULL) { // Edge case if there is no disk space
        printf("Could not allocate memory for recorded data\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Reading through input file and completing data array
    int32b records = 0;
    int32b record_int;
    char record_string[95];

    while(fscanf(file, "%lu %s", &record_int, record_string) == 2) {
        // If more space is needed, the data array is reallocated
        if (records >= max_records) {
            max_records *= 2;
            data = realloc(data, max_records * sizeof(struct record));
            if (data == NULL) { // Edge case if there is no disk space for reallocation
                printf("Could not allocate MORE memory for recorded data\n");
                fclose(file);
                return EXIT_FAILURE;
            }
        }
        data[records].myInt = record_int;   
        data[records].myString = strdup(record_string);
        records++;
    }
    fclose(file);
    
    // Sorting data using quick sort program
    quickSort(data, 0, records - 1);

    // Opening/creating output file
    char prefix[] = "C_sorted_";
    char* output_filename = strcat(prefix, filename);

    FILE *output_file;
    output_file = fopen(output_filename, "wb");
    if(output_file == NULL) {
        printf("Could not open output_file %s\n", output_filename);
        return EXIT_FAILURE;
    }

    // Writing sorted data in output file
    for (int j = 0; j < records; j++) {
        fprintf(output_file, "%lu %s\n", data[j].myInt, data[j].myString);
        free(data[j].myString); // Needs to be freed as it was copied with strdup
    }
    fclose(output_file);

    // Freeing the data array
    free(data);

    // Computing execution time
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("C Execution Time is : %f s\n", time_taken);
    return EXIT_SUCCESS;
}
