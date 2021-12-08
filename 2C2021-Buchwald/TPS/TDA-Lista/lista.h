#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista enlazada de punteros genéricos. */

struct lista;
typedef struct lista lista_t;
struct lista_iter;
typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista está vacía y falso si no lo está.
// Pre: la lista fue creada. 
bool lista_esta_vacia(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, el dato se encuentra al 
// principio de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Agrega un nuevo elemento al final de la lista. Devuelve false en caso de 
// error.
// Pre: la lista fue creada y no está vacía.
// Post: se agregó un nuevo elemento a la lista, el dato se encuentra al 
// final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Devuelve el valor del primer elemento de la lista. Devuelve NULL si la 
// lista está vacía.
// Pre: la lista fue creada y no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Devuelve el largo de la lista.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

// Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
// la misma. Dicha función puede devolver true si se deben seguir recorriendo
// elementos o false si se debe dejar de iterar elementos.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

// Crea un iterador externo.
// Pre: la lista fue creada.
// Post: devuelve un iterador apuntando al primer nodo de la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Devuelve el valor del elemento actual.
// Pre: el iterador fue creado.
// Post: se devolvió el elemento al que apunta el iterador si la lista 
// no está vacía o NULL si lo está.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
void lista_iter_destruir(lista_iter_t *iter);

// Borra el elemento al que apunta el iterador y devuelve su valor.
// Pre: el iterador fue creado.
// Post: el elemento fue eliminado de la lista y se devolvió su valor.
void *lista_iter_borrar(lista_iter_t *iter);

// Avanza una posición de la lista.
// Pre: el iterador fue creado.
// Post: devuelve true si puede avanzar una posición,
// false en caso de estar en el final de la lista.
bool lista_iter_avanzar(lista_iter_t *iter);

// Indica si llegó al final de la lista.
// Pre: el iterador fue creado.
// Post: devuelve true en caso de estar al final,
// false en caso contrario.
bool lista_iter_al_final(const lista_iter_t *iter);

// Inserta un elemento en la posición actual del iterador.
// Pre: el iterador fue creado.
// Post: devuelve true si se pudo insertar el elemento
// en la lista.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

void pruebas_lista_estudiante(void);

#endif  // LISTA_H
