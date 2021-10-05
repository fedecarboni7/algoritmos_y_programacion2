#include <stdio.h>
#include <stdbool.h>

bool _arreglo_es_magico(int arr[], size_t inicio, size_t fin) {
    if (inicio > fin) {
        return false;
    }

    size_t medio = (inicio + fin) / 2;
    if (arr[medio] == medio) {
        return true;
    }
    if (arr[medio] < medio) {
        return _arreglo_es_magico(arr, medio + 1, fin);
    } else {
        // considerando el caso de haber llegado hasta el extremo izquierdo, 
        // y que esto puede dar underflow por el uso de size_t:
        if (medio == 0) return false;
        
        return _arreglo_es_magico(arr, inicio, medio - 1);
    }
}

bool arreglo_es_magico(int arr[], size_t n) {
    return _arreglo_es_magico(arr, 0, n - 1);
}

int main()
{
    int arreglo[] = {0, 1, 4, 5, 7, 9};
    if (arreglo_es_magico(arreglo, 6)) printf("El arreglo es mágico\n");
    return 0;
}