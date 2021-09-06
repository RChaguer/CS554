#include <sched.h>
#include <pthread.h>
#include <assert.h>
#include "sort-data.h"

unsigned long max_records = 100; // Not defined as constant because we will be changing it if needed

struct record * array;

struct args{
    int first;
    int last;
};

void *quickSort(void *arg) {

    pthread_t th, th2;
    int err;
    struct args *a = (struct args *) arg;

    /* on passe un peu la main aux autres pour eviter de faire uniquement la partie gauche de l'arbre */
    sched_yield();

    int pivot, i, j;
    if( ((struct args *) arg)->first <((struct args *) arg)->last) {
        pivot = a->first;
        i = a->first;
        j = a->last;
        while (i < j) {
            while(cmp(array[i], array[pivot]) <= 0 && i < a->last)
                i++;
            while(cmp(array[j], array[pivot]) > 0)
                j--;
            if(i < j) {
                swap(&(array[i]), &(array[j]));
            }
        }
        swap(&(array[pivot]), &(array[j]));
        struct args a1;
        a1.first = a->first;
        a1.last = j-1;
        err = pthread_create(&th, NULL, quickSort, (void*)(&a1)); // pthread_create(th, NULL, func, arg)
        assert(!err);
        struct args a2;
        a2.first = j+1;
        a2.last = a->last;
        err = pthread_create(&th2, NULL, quickSort, (void*)(&a2));
        assert(!err);
        err = pthread_join(th, NULL);
        assert(!err);
        err = pthread_join(th2, NULL);
        assert(!err); 
    }
    return (void*)NULL;
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
    array = data;

    // Reading through input file and completing data array
    int records = 0;
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
            array = data;
        }
        data[records].myInt = record_int;   
        data[records].myString = strdup(record_string);
        records++;
    }
    fclose(file);
    
    // Sorting data using quick sort program
    struct args arg;
    arg.first = 0;
    arg.last = records - 1;
    quickSort((void *) &arg);

    // Opening/creating output file
    char prefix[] = "Threaded_C_sorted_";
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
    printf("Time taken is: %f s\n", time_taken);
    return EXIT_SUCCESS;
}