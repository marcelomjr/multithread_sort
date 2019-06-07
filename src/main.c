/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>

void merge_sort(int* array, int begin, int end);
void merge(int* array, int begin, int middle, int end);
void get_inputs(int inputs[], int* number_of_inputs);

int main() {

  int x, y;

    int array[100000];
    int number_of_elements;
    
    get_inputs(array, &number_of_elements);
    

    merge_sort(array, 0, number_of_elements - 1);
    
    number_of_elements--;
    
    for (int index = 0; index < number_of_elements; index++) {

        printf("%d ", array[index]);
    }
    
    printf("%d\n", array[number_of_elements]);
    
    
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
