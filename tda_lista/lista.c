#include "lista.h"
#include <stdlib.h>

lista_t* lista_crear(){
    lista_t* lista_nueva = calloc(1, sizeof(lista_t));
    if(!lista_nueva)
        return NULL;
    return lista_nueva;
}

int lista_insertar(lista_t* lista, void* elemento){
    if(!lista)
        return -1;
    if(!lista->nodo_inicio){
        nodo_t* nuevo_nodo = calloc(1, sizeof(nodo_t));
        if(!nuevo_nodo)
            return -1;
        nuevo_nodo->elemento = elemento;
        lista->nodo_inicio = nuevo_nodo;
        lista->nodo_fin = nuevo_nodo;
        lista->nodo_inicio->siguiente = lista->nodo_fin;
    }
    else{
        nodo_t* nuevo_nodo = calloc(1, sizeof(nodo_t));
        if(!nuevo_nodo)
            return -1;
        nuevo_nodo->elemento = elemento;
        lista->nodo_fin->siguiente = nuevo_nodo;
        lista->nodo_fin = nuevo_nodo;
    }
    lista->cantidad++;
    return 0;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    if(!lista)
        return -1;
    if(posicion >= lista->cantidad)
        return lista_insertar(lista, elemento);
    nodo_t* nuevo_nodo = calloc(1, sizeof(nodo_t));
    if(!nuevo_nodo)
        return -1;
    nuevo_nodo->elemento = elemento;
    if(posicion == 0){
        nuevo_nodo->siguiente = lista->nodo_inicio;
        lista->nodo_inicio = nuevo_nodo;
    }
    else{
        size_t posicion_aux = 0;
        nodo_t* nodo_aux = lista->nodo_inicio;
        while(posicion_aux < posicion){
            nodo_aux = nodo_aux->siguiente;
            posicion_aux++;
        }
        nuevo_nodo->siguiente = nodo_aux->siguiente;
        nodo_aux = nuevo_nodo;
    }
    lista->cantidad++;
    return 0;
}

int lista_borrar(lista_t* lista){
    if(!lista)
        return -1;
    if(lista->cantidad == 0)
        return -1;
    nodo_t* nodo_aux = lista->nodo_inicio;
    if(lista->cantidad == 1){
        free(nodo_aux);
        lista->cantidad--;
        return 0;
        }
    size_t posicion = 1;
    while(posicion < lista->cantidad - 1){
        nodo_aux = nodo_aux->siguiente;
        posicion++;
    }
    free(lista->nodo_fin);
    nodo_aux->siguiente = NULL;
    lista->nodo_fin = nodo_aux;
    lista->cantidad--;
    return 0;
}

int lista_borrar_primero(lista_t* lista){
    if(!lista)
        return -1;
    if(lista->cantidad == 0)
        return -1;
    nodo_t* nodo_aux = lista->nodo_inicio;
    if(lista->cantidad == 1){
        free(nodo_aux);
        lista->cantidad--;
        return 0;
        }
    lista->nodo_inicio = lista->nodo_inicio->siguiente;
    free(nodo_aux);
    lista->cantidad--;
    return 0;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    if(!lista)
        return -1;
    if(posicion >= lista->cantidad - 1)
        return lista_borrar(lista);
    if(posicion == 0)
        return lista_borrar_primero(lista);
    nodo_t* nodo_aux = lista->nodo_inicio->siguiente;
    nodo_t* nodo_anterior = lista->nodo_inicio;
    size_t posicion_nodo_aux = 1;
    while(posicion_nodo_aux < posicion){
        nodo_aux = nodo_aux->siguiente;
        nodo_anterior = nodo_anterior->siguiente;
        posicion_nodo_aux++;
    }
    nodo_anterior->siguiente = nodo_aux->siguiente;
    free(nodo_aux);
    lista->cantidad--;
    return 0;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    if(!lista)
        return NULL;
    if(posicion >= lista->cantidad)
        return NULL;
    nodo_t* nodo_aux = lista->nodo_inicio;
    size_t posicion_aux = 0;
    while(posicion_aux < posicion){
        nodo_aux = nodo_aux->siguiente;
        posicion_aux++;
    }
    return nodo_aux->elemento;
}

void* lista_ultimo(lista_t* lista){
    if(!lista)
        return NULL;
    if(lista->cantidad == 0)
        return NULL;
    return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){
    if(lista->cantidad == 0)
        return true;
    return false;
}

size_t lista_elementos(lista_t* lista){
    if(!lista)
        return 0;
    return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){
    return lista_insertar(lista, elemento);
}

int lista_desapilar(lista_t* lista){
    return lista_borrar(lista);
}

void* lista_tope(lista_t* lista){
    if(lista->cantidad == 0)
        return NULL;
    return lista->nodo_fin->elemento;
}

int lista_encolar(lista_t* lista, void* elemento){
    return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t* lista){
    return lista_borrar_primero(lista);
}

void* lista_primero(lista_t* lista){
    if(!lista)
        return NULL;
    if(lista->cantidad == 0)
        return NULL;
    return lista->nodo_inicio->elemento;
}

void lista_destruir(lista_t* lista){
    while(lista_elementos(lista) > 0)
        lista_borrar_primero(lista);
    free(lista);
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    if(!lista)
        return NULL;
    lista_iterador_t* iterador = calloc(1, sizeof(lista_iterador_t));
    if(!iterador)
        return NULL;
    iterador->lista = lista;
    iterador->corriente = lista->nodo_inicio;
    return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    if(!iterador || !iterador->corriente->siguiente)
        return false;
    return true;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    if(!iterador || !iterador->corriente->siguiente)
        return false;
    iterador->corriente = iterador->corriente->siguiente;
    return true;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    if(!iterador->corriente || !iterador)
        return NULL;
    return iterador->corriente;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
    if(iterador->lista)
        lista_destruir(iterador->lista);
    free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
    if(!lista)
        return 0;
    
    nodo_t* actual = lista->nodo_inicio;
    size_t i;
    for(i = 0; actual->siguiente; actual = actual->siguiente){
        void* elemento = actual->elemento;
        funcion(elemento, contexto);
        i++;
    }
    return i;
}
