#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void merge_sort(int* array, int begin, int end);
void merge(int* array, int begin, int middle, int end);
void get_inputs(int inputs[], int* number_of_inputs);
void* sorter_routine(void* args);

#define MAX_THREADS 4

typedef struct sorter {
    pthread_t thread_id;
    int index;
    int begin;
    int end;
} sorter_t;

int array[100000];

void* sorter_routine(void* args) {
    sorter_t sorter = *((sorter_t*) args);

    merge_sort(array, sorter.begin, sorter.end);
}

int main() {

    int number_of_elements;
    int number_of_threads;
    sorter_t* sorters;
    int thread_range;
    
    get_inputs(array, &number_of_elements);

    if (number_of_elements < MAX_THREADS) {
        number_of_threads = number_of_elements;
    }
    else {
        number_of_threads = MAX_THREADS;
    }
    
    sorters = (sorter_t*) malloc(number_of_threads * sizeof(sorter_t));
    
    thread_range = number_of_elements / number_of_threads;
    
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
   
   for (int i = 0, begin = 0; i < number_of_threads; i++) {
        pthread_join(sorters[i].thread_id, NULL);
   }
    
    for (int i = 1, begin = 0; i < number_of_threads; i++) {
        
        merge(array, 0, sorters[i - 1].end, sorters[i].end);
   }
    
    for (int index = 0, end = number_of_elements - 1; index < end; index++) {

        printf("%d ", array[index]);
    }
    
    printf("%d\n", array[number_of_elements - 1]);
    
    
  return 0;
}
void merge_sort(int* array, int begin, int end) {
    
    int middle = (end + begin) / 2;   
     
    if (end - begin < 1) {
        return;
    }

    merge_sort(array, begin, middle);
    merge_sort(array, middle + 1, end);   
    merge(array, begin, middle, end);
}

// array1 [begin...(middle-1)]
// array2 [middle...end]
void merge(int* array, int begin, int middle, int end) {
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
void get_inputs(int inputs[], int* number_of_inputs) {
    
    int input;
    int index = 0;
    
    while (scanf("%d", &input) != EOF) {
        inputs[index] = input;
        index++;
    }
    *number_of_inputs = index;
}
