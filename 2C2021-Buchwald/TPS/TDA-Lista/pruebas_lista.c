#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

bool imprimir(void* dato, void* extra) {
    if (*(int*) extra == 5) {
        return false;
    }
    (*(int*) extra)++;
    printf("%d", *(int*) dato);
    return true;
}

bool sumar(void* dato, void* extra) {
    *(int*) extra += *(int*) dato;
    return true;  
}

static void prueba_lista_vacia(void) {
    printf("\nINICIO DE PRUEBAS CON LISTA VACIA\n");

    lista_t *lista = lista_crear();
    print_test("Crear lista", lista != NULL);
    
    printf("\nCONDICIÓN DE BORDE\n");
    print_test("La lista está vacía", lista_esta_vacia(lista));
    print_test("Borrar un elemento de una lista vacía devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("Ver el primer elemento de una lista vacía devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("Ver el último elemento de una lista vacía devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("La lista tiene 0 elementos", lista_largo(lista) == 0);

    lista_destruir(lista, NULL);
}

static void prueba_agregar_elementos(void) {
    printf("\nINICIO DE PRUEBAS INSERTAR Y BORRAR ELEMENTOS\n");

    lista_t *lista = lista_crear();
    int arreglo[] = {0, 2, 5, 6};

    print_test("Agregar 1 elemento al principio", lista_insertar_primero(lista, &arreglo[0]));
    print_test("El elemento agregado es el primero", lista_ver_primero(lista) == &arreglo[0]);
    print_test("Agregar un segundo elemento al principio", lista_insertar_primero(lista, &arreglo[1]));
    print_test("El elemento agregado es el primero", lista_ver_primero(lista) == &arreglo[1]);
    print_test("Agregar un tercer elemento al final", lista_insertar_ultimo(lista, &arreglo[2]));
    print_test("El elemento agregado es el último", lista_ver_ultimo(lista) == &arreglo[2]);
    print_test("Agregar un cuarto elemento al final", lista_insertar_ultimo(lista, &arreglo[3]));
    print_test("El elemento agregado es el último", lista_ver_ultimo(lista) == &arreglo[3]);
    print_test("El largo de la lista es igual a 4", lista_largo(lista) == 4);
    print_test("Borro el primer elemento", lista_borrar_primero(lista) == &arreglo[1]);
    print_test("Borro el segundo elemento", lista_borrar_primero(lista) == &arreglo[0]);
    print_test("Borro el tercer elemento", lista_borrar_primero(lista) == &arreglo[2]);
    print_test("Borro el cuarto elemento", lista_borrar_primero(lista) == &arreglo[3]);
    print_test("La lista está vacía", lista_esta_vacia(lista));
    
    lista_destruir(lista, NULL);
}

static void prueba_de_volumen(void) {
    printf("\nINICIO DE PRUEBAS VOLUMEN\n");

    lista_t *lista = lista_crear();
    int dato;
    bool resultado = true;

    for (int i = 0; i <= 999; i++) {
        resultado = lista_insertar_ultimo(lista, &dato);
        if (!resultado) break;
    }
    print_test("Puedo insertar todos los elementos", resultado);

    for (int i = 999; i >= 0; i--) {
        if (i == 0) {
            resultado = resultado && lista_borrar_primero(lista) == &dato && lista_esta_vacia(lista);
            break;
        }
        resultado &= lista_borrar_primero(lista) == &dato;
        if (!resultado) break;
    }
    print_test("Puedo borrar todos los elementos", resultado);

    lista_destruir(lista, NULL);
}

static void prueba_insertar_NULL(void) {
    printf("\nINICIO DE PRUEBAS INSERTAR ELEMENTO NULL\n");

    lista_t *lista = lista_crear();

    print_test("Agrego NULL", lista_insertar_primero(lista, NULL));
    print_test("La lista no está vacía", lista_esta_vacia(lista) == false);
    print_test("El primer elemento es NULL", lista_ver_primero(lista) == NULL);
    print_test("Borro NULL", lista_borrar_primero(lista) == NULL);
    print_test("La lista queda vacía", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);
}

void pila_destruir_wrapper(void* pila) {
    pila_destruir(pila);
}


static void prueba_destruccion_lista_vacia_funcion_NULL(void) {
    printf("\nINICIO DE PRUEBA DESTRUCCION LISTA VACIA FUNCION NULL\n");

    lista_t *lista = lista_crear();

    print_test("Crear lista", lista != NULL);
    print_test("La lista está vacía", lista_esta_vacia(lista));
    
    lista_destruir(lista, NULL);
}

static void prueba_destruccion_lista_vacia_funcion_NO_NULL(void) {
    printf("\nINICIO DE PRUEBA DESTRUCCION LISTA VACIA FUNCION NO NULL\n");

    lista_t *lista = lista_crear();

    print_test("Crear lista", lista != NULL);
    print_test("La lista está vacía", lista_esta_vacia(lista));

    lista_destruir(lista, free);
}

static void prueba_destruccion_lista_NO_vacia_funcion_NULL(void) {
    printf("\nINICIO DE PRUEBA DESTRUCCION LISTA NO VACIA FUNCION NULL\n");

    lista_t *lista = lista_crear();
    bool resultado = true;

    for (int i = 0; i <= 10; i++) {
        resultado = lista_insertar_ultimo(lista, &i);
        if (!resultado) break;
    }

    lista_destruir(lista, NULL);
}

static void prueba_destruccion_lista_NO_vacia_funcion_NO_NULL(void) {
    printf("\nINICIO DE PRUEBA DESTRUCCION LISTA NO VACIA FUNCION NO NULL\n");

    pila_t *pila = pila_crear();
    lista_t *lista = lista_crear();
    int valor;

    print_test("Agrego elementos a una pila", pila_apilar(pila, &valor) && pila_apilar(pila, &valor) && pila_apilar(pila, &valor));
    print_test("Agrego a la lista una pila que tiene elementos", lista_insertar_primero(lista, pila));
    print_test("El primer elemento es la pila", lista_ver_primero(lista) == pila);

    lista_destruir(lista, pila_destruir_wrapper);
}

/* ******************************************************************
 *                        PRUEBAS ITERADOR EXTERNO
 * *****************************************************************/

static void prueba_remover_al_crear(void) {
    printf("\nINICIO DE PRUEBAS REMOVER ELEMENTO AL CREAR ITERADOR\n");

    lista_t *lista = lista_crear();

    int arreglo[] = {2, 5, 6};

    print_test("Insertar 2 es true", lista_insertar_primero(lista, &arreglo[0]));
    print_test("Insertar 5 es true", lista_insertar_primero(lista, &arreglo[1]));
    print_test("Insertar 6 es true", lista_insertar_primero(lista, &arreglo[2]));
    
    lista_iter_t *lista_iter = lista_iter_crear(lista);

    print_test("Remuevo el primer elemento", lista_iter_borrar(lista_iter) == &arreglo[2]);
    print_test("El primer elemento de la lista es 5", lista_ver_primero(lista) == &arreglo[1]);

    lista_iter_destruir(lista_iter);
    lista_destruir(lista, NULL);
}

static void prueba_remover_ultimo(void) {
    printf("\nINICIO DE PRUEBAS REMOVER ÚLTIMO ELEMENTO\n");

    lista_t *lista = lista_crear();
    
    int arreglo[] = {1, 2};

    print_test("Insertar 1 es true", lista_insertar_primero(lista, &arreglo[0]));
    print_test("Insertar 2 es true", lista_insertar_ultimo(lista, &arreglo[1]));
    
    lista_iter_t *lista_iter = lista_iter_crear(lista);

    
    print_test("Me posiciono en el último elemento de la lista", lista_iter_avanzar(lista_iter) && lista_iter_ver_actual(lista_iter) == &arreglo[1]);
    print_test("El último elemento de la lista es 2", lista_ver_ultimo(lista) == &arreglo[1]);
    print_test("Borro el último elemento", lista_iter_borrar(lista_iter) == &arreglo[1]);
    print_test("El último elemento de la lista es 1", lista_ver_ultimo(lista) == &arreglo[0]);
    print_test("El largo de la lista es igual a 1", lista_largo(lista) == 1);
    
    lista_iter_destruir(lista_iter);
    lista_iter_t* lista_iter2 = lista_iter_crear(lista);
    
    print_test("Creo un nuevo iterador", lista_iter2 != NULL);
    print_test("El actual es igual al primer elemento", lista_iter_ver_actual(lista_iter2) == &arreglo[0]);
    print_test("Avanzo una posicion", lista_iter_avanzar(lista_iter2));
    print_test("Me posiciono al final", lista_iter_al_final(lista_iter2));
    print_test("Ver actual es igual a NULL", lista_iter_ver_actual(lista_iter2) == NULL);
    print_test("Iter avanzar es false", !lista_iter_avanzar(lista_iter2));

    lista_iter_destruir(lista_iter2);
    lista_destruir(lista, NULL);
}

static void prueba_remover_del_medio(void) {
    printf("\nINICIO DE PRUEBAS REMOVER ELEMENTO DEL MEDIO\n");

    lista_t *lista = lista_crear();
    int arreglo[] = {1, 3, 5};

    print_test("Insertar 1 es true", lista_insertar_primero(lista, &arreglo[0]));
    print_test("Insertar 3 es true", lista_insertar_primero(lista, &arreglo[1]));
    print_test("Insertar 5 es true", lista_insertar_primero(lista, &arreglo[2]));

    lista_iter_t *iter_1 = lista_iter_crear(lista);

    lista_iter_avanzar(iter_1);

    lista_iter_borrar(iter_1);
    lista_iter_destruir(iter_1);

    lista_iter_t *iter_2 = lista_iter_crear(lista);

    lista_iter_avanzar(iter_2);

    print_test("el elemento del medio no está", *(int *)lista_iter_ver_actual(iter_2) == 1);
    
    lista_iter_destruir(iter_2);
    lista_destruir(lista, NULL);
}

static void prueba_insertar_al_principio(void) {
    printf("\nINICIO DE PRUEBAS INSERTAR AL CREAR ITERADOR\n");

    lista_t *lista = lista_crear();

    int arreglo[] = {2, 5, 6};

    print_test("Insertar 2 es true", lista_insertar_primero(lista, &arreglo[0]));
    print_test("Insertar 5 es true", lista_insertar_primero(lista, &arreglo[1]));
    
    lista_iter_t *iter = lista_iter_crear(lista);
    
    print_test("Inserto con el iterador un elemento a una lista con elementos", lista_iter_insertar(iter, &arreglo[2]));
    print_test("Ver actual con el iterador luego de insertar", lista_iter_ver_actual(iter) == &arreglo[2]);
    print_test("El elemento agregado es el primero de la lista", lista_ver_primero(lista) == &arreglo[2]);

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

static void prueba_insertar_al_final(void) {
    printf("\nINICIO DE PRUEBAS INSERTAR CON ITERADOR AL FINAL\n");

    lista_t *lista = lista_crear();

    int arreglo[] = {2, 5, 6};

    print_test("Insertar 2 es true", lista_insertar_primero(lista, &arreglo[0]));
    print_test("Insertar 5 es true", lista_insertar_primero(lista, &arreglo[1]));
    
    lista_iter_t *iter = lista_iter_crear(lista);
    
    print_test("Me posiciono al final de la lista", lista_iter_avanzar(iter) && lista_iter_avanzar(iter) && lista_iter_al_final(iter));
    print_test("Ver actual devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Avanzar devuelve false", !lista_iter_avanzar(iter));
    print_test("Inserto un elemento al final de la lista", lista_iter_insertar(iter, &arreglo[2]));
    print_test("El elemento agregado es el último de la lista", lista_ver_ultimo(lista) == &arreglo[2] && lista_iter_ver_actual(iter) == &arreglo[2]);

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

static void prueba_insertar_en_el_medio(void) {
    printf("\nINICIO DE PRUEBAS INSERTAR EN EL MEDIO\n");

    lista_t *lista = lista_crear();

    int arreglo[] = {0, 2, 5, 6, 7};

    print_test("Insertar 0 es true", lista_insertar_primero(lista, &arreglo[0]));
    print_test("Insertar 2 es true", lista_insertar_primero(lista, &arreglo[1]));
    print_test("Insertar 6 es true", lista_insertar_primero(lista, &arreglo[3]));
    print_test("Insertar 7 es true", lista_insertar_primero(lista, &arreglo[4]));
    
    lista_iter_t *iter = lista_iter_crear(lista);
    
    print_test("Me posiciono en el medio de la lista", lista_iter_avanzar(iter) && lista_iter_avanzar(iter) && lista_iter_ver_actual(iter) == &arreglo[1]);
    print_test("Inserto un elemento en el medio de la lista", lista_iter_insertar(iter, &arreglo[2]));

    lista_iter_destruir(iter);

    lista_iter_t* iter2 = lista_iter_crear(lista);

    lista_iter_avanzar(iter2);
    lista_iter_avanzar(iter2);
    print_test("El elemento agregado está a la mitad de la lista", lista_iter_ver_actual(iter2) == &arreglo[2]);

    lista_iter_destruir(iter2);
    lista_destruir(lista, NULL);
}

static void prueba_imprimir_con_corte(void) {
    printf("\nINICIO DE PRUEBAS IMPRIMIR ELEMENTOS\n");
    int arreglo[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    lista_t *lista = lista_crear();
    bool resultado = true;

    for (int i = 0; i < 10; i++) {
        resultado = lista_insertar_ultimo(lista, (void*) &arreglo[i]);
        if (!resultado) break; 
    }

    int extra = 0;
    lista_iterar(lista, imprimir, &extra); 
    lista_destruir(lista, NULL);
}

static void prueba_sumar_sin_corte(void) {
    printf("\nINICIO DE PRUEBAS SUMAR ELEMENTOS\n");
    int arreglo[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    lista_t *lista = lista_crear();
    bool resultado = true;

    for (int i = 0; i < 10; i++) {
        resultado = lista_insertar_ultimo(lista, (void*) &arreglo[i]); 
        if (!resultado) break;
    }

    int suma = 0;
    lista_iterar(lista, sumar, &suma);
    print_test("La suma de todos los elementos de la lista es 55", suma == 55);
    lista_destruir(lista, NULL);
}

static void pruebas_borde_iter_externo(void) {
    printf("\nINICIO DE PRUEBAS BORDE ITERADOR EXTERNO\n");

    lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);

    print_test("Ver el actual de una lista vacía devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("El iterador está al final cuando la lista está vacía", lista_iter_al_final(iter));
    print_test("El iterador no puede borrar cuando la lista está vacía", lista_iter_borrar(iter) == NULL);
    print_test("El iterador no puede avanzar cuando la lista está vacía", !lista_iter_avanzar(iter));

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

void pruebas_lista_estudiante() {
    printf("INICIO PRUEBAS CASOS BÁSICOS LISTA\n");
    prueba_lista_vacia();
    prueba_agregar_elementos();
    prueba_de_volumen();
    prueba_insertar_NULL();
    prueba_destruccion_lista_NO_vacia_funcion_NO_NULL();
    prueba_destruccion_lista_NO_vacia_funcion_NULL();
    prueba_destruccion_lista_vacia_funcion_NO_NULL();
    prueba_destruccion_lista_vacia_funcion_NULL();
    printf("\nINICIO PRUEBAS CASOS ITERADOR INTERNO\n");
    prueba_imprimir_con_corte();
    prueba_sumar_sin_corte();
    printf("\nINICIO PRUEBAS CASOS ITERADOR EXTERNO\n");
    prueba_remover_al_crear();
    prueba_remover_ultimo();
    prueba_remover_del_medio();
    prueba_insertar_al_principio();
    prueba_insertar_al_final();
    prueba_insertar_en_el_medio();
    pruebas_borde_iter_externo();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
