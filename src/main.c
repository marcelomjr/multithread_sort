// Parallel merge sort program

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void merge_sort(int begin, int end);
void merge(int begin, int middle, int end);
void get_inputs(int* number_of_inputs);
void* sorter_routine(void* args);

#define MAX_THREADS 4

typedef struct sorter {
    pthread_t thread_id;
    int index;
    int begin;
    int end;
} sorter_t;

int array[100000];

/* This is the thread routine, it sorts the array region received.
*/
void* sorter_routine(void* args) {
    sorter_t sorter = *((sorter_t*) args);

    merge_sort(sorter.begin, sorter.end);
}

int main() {

    int number_of_elements;
    int number_of_threads;
    sorter_t* sorters;
    int thread_range;
    
    // read the array from the stardard input
    get_inputs(&number_of_elements);
    
    // Calculate the thread number according to the number of elements
    if (number_of_elements < MAX_THREADS) {
        number_of_threads = number_of_elements;
    }
    else {
        number_of_threads = MAX_THREADS;
    }
    
    // Create a array of structs of thread information
    sorters = (sorter_t*) malloc(number_of_threads * sizeof(sorter_t));
    
    // Calculates the number of elements to be sorted by each thread
    thread_range = number_of_elements / number_of_threads;
    
    // Divide the array into segments for each thread to sort
    for (int i = 0, begin = 0; i < number_of_threads; i++) {
        sorters[i].index = i;
        sorters[i].begin = begin;
        begin += thread_range;
        
        if (i == number_of_threads - 1) {
            sorters[i].end = number_of_elements - 1;
        } else {
            sorters[i].end = begin -1;
        }

        pthread_create(&(sorters[i].thread_id), NULL, sorter_routine, &(sorters[i]));
    }
   
    // Wait until all the threads ends
    for (int i = 0, begin = 0; i < number_of_threads; i++) {
        pthread_join(sorters[i].thread_id, NULL);
    }
    
    // Merge the ordered segments of each thread
    for (int i = 1, begin = 0; i < number_of_threads; i++) {
        merge(0, sorters[i - 1].end, sorters[i].end);
    }
    
    // Print the ordered array
    for (int index = 0, end = number_of_elements - 1; index < end; index++) {
        printf("%d ", array[index]);
    }
    printf("%d\n", array[number_of_elements - 1]);
    
    return 0;
}

/* Recursive merge sort algorithm */
void merge_sort(int begin, int end) {
    
    int middle = (end + begin) / 2;   
     
    if (end - begin < 1) {
        return;
    }

    merge_sort(begin, middle);
    merge_sort(middle + 1, end);   
    merge(begin, middle, end);
}

/*
    Sort an array, which is composed by two sorted segments.
    array1 [begin...(middle-1)]
    array2 [middle...end]
*/
void merge(int begin, int middle, int end) {
    int begin1 = begin;
    int begin2 = middle + 1;
    int size = end - begin + 1;
    int* aux_array = (int*) malloc(size * sizeof(int));
    int aux_index = 0;
       
    while ((begin1 <= middle) && (begin2 <= end)) {
        if (array[begin1] < array[begin2]){
            aux_array[aux_index] = array[begin1];
            aux_index++;
            begin1++;
        }
        else {
            aux_array[aux_index] = array[begin2];
            aux_index++;
            begin2++;
        }
    }
    
    while (begin1 <= middle) {
         aux_array[aux_index] = array[begin1];
            aux_index++;
            begin1++;
    }
    
    while (begin2 <= end) {
         aux_array[aux_index] = array[begin2];
            aux_index++;
            begin2++;
    }
    
    for (int index = 0; index < size; index++) {
        array[begin + index] = aux_array[index];
    }
}

/* It gets the numbers from the standard input, one by one, 
   until the end of file character is found */
void get_inputs(int* number_of_inputs) {
    
    int input;
    int index = 0;
    
    while (scanf("%d", &input) != EOF) {
        array[index] = input;
        index++;
    }
    *number_of_inputs = index;
}
