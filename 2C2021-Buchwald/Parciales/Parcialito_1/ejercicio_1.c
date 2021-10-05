/*Dada una pila, implementar una función que devuelva el largo de la misma, la pila debe
quedar en su estado original. Justificar el orden del algoritmo.*/

size_t largo_pila(pila_t *pila) {
    if (pila_esta_vacia(pila)) return 0;
    size_t largo = 0;
    pila_t *pila_aux = pila_crear();
    while (!pila_esta_vacia(pila)) {
        pila_apilar(pila_aux, pila_desapilar(pila));
        largo++;
    }
    while (!pila_esta_vacia(pila_aux)) {
        pila_apilar(pila, pila_desapilar(pila_aux));
    }
    return largo;
}

/*El orden del algoritmo es O(n*2) = O(n) ya que para determinar el largo de la pila, es necesario
desapilar y luego volver a apilar cada uno de sus elementos. Por eso mientras más elementos
tenga la pila, mayor será el tiempo que tarde en contarlos,de forma lineal.*/
