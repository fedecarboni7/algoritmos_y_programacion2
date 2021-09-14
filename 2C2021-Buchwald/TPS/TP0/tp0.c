#include "tp0.h"
#include <stdio.h>
#include <stdlib.h>


/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int z = *x;
    *x = *y;
    *y = z;
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
    int n = 0;
    if(n1 < n2){
        n = n1; 
    }
    else {
        n = n2;
    }
    for(int i = 0; i < n; i++){
        if(vector1[i] < vector2[i]){
            return -1;
        }
        else if(vector1[i] > vector2[i]){
            return 1;
        }
    }
    if(n1 < n2){
        return -1;
    }
    else if(n2 < n1){
        return 1;
    }
    return 0;
}

/*
void seleccion(int vector[], int n) {
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (vector[i] > vector[j])
                swap(&vector[i], &vector[j]);
        }
    }
}*/

void seleccion(int vector[], int n) {
    for(int j = 0; j < n - 1; j++){
        int i_max = maximo(vector, n - j);
        swap(&vector[i_max], &vector[n-1 - j]);
    }
}
