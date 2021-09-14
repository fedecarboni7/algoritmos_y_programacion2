#include "tp0.h"
#include <stdio.h>
#include <stdlib.h>


/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int *z = malloc(sizeof(int*));
    *z = *x;
    *x = *y;
    *y = *z;
    free(z);
}


int maximo(int vector[], int n) {
    if(n == 0)
        return -1;
    int max = vector[0];
    for(int i = 0; i < n; i++){
        if(vector[i] > max){
            max = vector[i];
        }
    }
    int j = 0;
    while(vector[j] != max){
        j++;
    }
    return j;
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
    return 0;
}


void seleccion(int vector[], int n) {
}
