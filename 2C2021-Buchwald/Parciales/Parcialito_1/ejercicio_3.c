/*A un array ordenado se lo rotó k posiciones. Implementar una función por división y conquista
que permita encontrar la cantidad k de rotaciones que se le aplicó al array. Justificar el orden
del algoritmo. Ejemplo:
[1,2,3,4,5,6] -> 0 rotaciones
[6,1,2,3,4,5] -> 1 rotación
[3,4,5,6,1,2] -> 4 rotaciones*/

size_t _cantidad_rotaciones(int arr[], size_t inicio, size_t fin) {
    if (inicio > fin) return 0;

    size_t medio = (inicio + fin) / 2;
    if (arr[medio] > arr[medio - 1] && arr[medio] > arr[medio + 1]) {
        return medio + 1;
    }
    if (arr[medio] < arr[medio - 1]) {
        return medio;
    }
    if (arr[medio] > arr[medio - 1]) {
        return _cantidad_rotaciones(arr, medio + 1, fin);
    }
    else {
        if (medio == 0) return 0;
        return _cantidad_rotaciones(arr, inicio, medio - 1);
    }

}

size_t cantidad_rotaciones(int arr[], size_t n) {
    return _cantidad_rotaciones(arr, 0, n - 1); 
}

//El orden del algoritmo no llegué a calcularlo.