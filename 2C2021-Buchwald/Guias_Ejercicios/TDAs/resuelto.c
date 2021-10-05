void** pila_multitop(const pila_t* pila, size_t n) {
    void** topes = malloc(sizeof(void*) * n);
    if (!topes) {
        return NULL;
    }
    // Se podria hacer que i comience en k o pila->cantidad - 1, pero hay que
    // tener cuidado con esto, y con la condicion de corte: un size_t nunca
    // va a ser menor a 0
    for (size_t i = 0; i < n; i++) {
        if (i < pila->cantidad) {
            topes[i] = pila->datos[pila->cantidad - 1 - i];
        } else {
            topes[i] = NULL;
        }
    }
    return topes;
}

//Otras formas...

void** pila_multitop(const pila_t* pila, size_t n) {
    void** topes = malloc(sizeof(void*) * n);
    if (!topes) return NULL;

    for (size_t i = 0; i < pila->cantidad; i++) {
        topes[i] = pila->datos[pila->cantidad - 1 - i];
    }

    for (size_t i = pila->cantidad; i < n; i++) {
        topes[i] = NULL;
    }
    return topes;
}

void** pila_multitop(const pila_t* pila, size_t n) {
    void** topes = calloc(NULL, sizeof(void*) * n);
    if (!topes) return NULL;

    for (size_t i = 0; i < n && i < pila->cantidad; i++) {
        topes[i] = pila->datos[pila->cantidad - 1 - i];
    }
    return topes;
}