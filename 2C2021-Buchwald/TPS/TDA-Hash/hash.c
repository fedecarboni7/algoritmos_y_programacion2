#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAMANIO_INICIAL 7
#define FACTOR_CARGA_SUPERIOR 3
#define FACTOR_CARGA_INFERIOR 1
#define FACTOR_REDIMENSION_ARRIBA 2
#define FACTOR_REDIMENSION_ABAJO 0.5

// Definición del struct hash

struct hash {
    lista_t** tabla;
    size_t m;
    hash_destruir_dato_t destruir_dato;
};

// Definición del struct campo

typedef struct campo {
    const char* clave;
    void* dato;
} campo_t;

// Definición del struct hash_iter

struct hash_iter {
    const hash_t* hash;
    size_t indice;
    lista_iter_t *actual;
};

// Definición de la función de hashing elegida: DJB2
// Fuente: https://softwareengineering.stackexchange.com/a/49566

size_t funcion_hash(const char *clave) {
    size_t hash = 5381;
    int c;

    while ((c = *clave++)) {
        hash = ((hash << 5) + hash) + c;
    }
        
    return hash;
}

void redimensionar(hash_t *hash, float factor) {
    hash->m = hash->m * (size_t) factor;
    lista_t** tabla_vieja = hash->tabla;
    hash->tabla = malloc(sizeof(lista_t*) * hash->m);
    for (size_t i = 0; i < hash->m; i++) {
        hash->tabla[i] = lista_crear();
    }
    for (size_t i = 0; i < hash->m; i++) {
        if(!lista_esta_vacia(tabla_vieja[i])) {
            lista_iter_t *iter = lista_iter_crear(tabla_vieja[i]);
            while (!lista_iter_al_final(iter)) {
                campo_t *actual = lista_iter_ver_actual(iter);
                hash_guardar(hash, actual->clave, actual->dato);
                lista_iter_avanzar(iter);
            }
            lista_iter_destruir(iter);
        }
    }
}

void campo_destruir(campo_t* campo) {
    free((char*) campo->clave);
    free(campo);
}

/* *****************************************************************
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t* hash = malloc(sizeof(hash_t));
    if (!hash) return NULL;
    hash->m = 7;
    hash->tabla = malloc(sizeof(lista_t*) * hash->m);
    if (!hash->tabla) {
        free(hash);
        return NULL;
    }
    for (size_t i = 0; i < hash->m; i++) {
        hash->tabla[i] = lista_crear();
    }
    hash->destruir_dato = destruir_dato;
    return hash;
}

void *hash_borrar(hash_t *hash, const char *clave) {
    size_t pos = funcion_hash(clave) % hash->m;
    lista_iter_t* iter = lista_iter_crear(hash->tabla[pos]);
    if (!iter) return NULL;
    campo_t* campo;
    while ((campo = lista_iter_ver_actual(iter))) {
        if (!strcmp(campo->clave, clave)) {
            void* dato = campo->dato; 
            campo_destruir(campo);
            lista_iter_borrar(iter);
            lista_iter_destruir(iter);
            return dato;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave) {
    size_t pos = funcion_hash(clave) % hash->m;
    lista_iter_t* iter = lista_iter_crear(hash->tabla[pos]);
    if (!iter) return NULL;
    campo_t* campo;
    while ((campo = lista_iter_ver_actual(iter))) {
        if (!strcmp(campo->clave, clave)) {
            lista_iter_destruir(iter);
            return true;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return false;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
    size_t pos = funcion_hash(clave) % hash->m;
    void *dato = NULL;
    if (hash_pertenece(hash, clave)) {
        lista_iter_t *iter = lista_iter_crear(hash->tabla[pos]);
        campo_t *actual; 
        while (!lista_iter_al_final(iter)) {
            actual = lista_iter_ver_actual(iter);
            lista_iter_avanzar(iter);
        }
        dato = actual->dato;
        lista_iter_destruir(iter);
    }
    return dato; 
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    float factor_carga = (float) hash_cantidad(hash) / (float) hash->m;
    if (factor_carga >= FACTOR_CARGA_SUPERIOR) {
        redimensionar(hash, FACTOR_REDIMENSION_ARRIBA);
    }
    if (factor_carga < FACTOR_CARGA_INFERIOR && hash->m > TAMANIO_INICIAL) {
        redimensionar(hash, FACTOR_REDIMENSION_ABAJO);
    }
    campo_t *campo = malloc(sizeof(campo_t));
    if (!campo) return false;
    campo->clave = strndup(clave, strlen(clave));
    campo->dato = dato;
    size_t pos = funcion_hash(clave) % hash->m;
    lista_insertar_ultimo(hash->tabla[pos], campo);
    return true;
}

size_t hash_cantidad(const hash_t *hash) {
    size_t cantidad = 0;
    for (size_t i = 0; i < hash->m; i++) {
        if (!lista_esta_vacia(hash->tabla[i])) {
            cantidad += lista_largo(hash->tabla[i]);
        }
    }
    return cantidad;
}

void hash_destruir(hash_t *hash) {
    for(size_t i = 0; i < hash->m; i++) {
        lista_destruir(hash->tabla[i], (void*) campo_destruir);
    }
    free(hash->tabla);
    free(hash);
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

hash_iter_t *hash_iter_crear(const hash_t *hash) {
    hash_iter_t *iter = calloc(1, sizeof(hash_iter_t));
    if (!iter) return NULL;
    if (hash_cantidad(hash) == 0) {
        iter->hash = hash;
        return iter;
    }
    lista_t *lista;
    size_t i = 0;
    do {
        lista = hash->tabla[i];
        i++;
    } while(lista_esta_vacia(lista));
    lista_iter_t *lista_iter = lista_iter_crear(lista);
    if (!lista_iter) {
        free(iter);
        return NULL;
    }
    iter->actual = lista_iter;
    iter->indice = i;
    return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) return false;
    if (lista_iter_al_final(iter->actual)) {
        lista_iter_destruir(iter->actual);
        lista_t* lista;
        size_t i = iter->indice;
        do {
            lista = iter->hash->tabla[i];
            i++;
        } while(lista_esta_vacia(lista));
        lista_iter_t *lista_iter = lista_iter_crear(lista);
        if (!lista_iter) return false;
        iter->actual = lista_iter;
        iter->indice = i;   
    } else {
        lista_iter_avanzar(iter->actual);
    }
    return true;
}

bool hash_iter_al_final(const hash_iter_t *iter) {
    if (hash_cantidad(iter->hash) == 0) return true;
    return iter->indice == iter->hash->m - 1 && lista_iter_al_final(iter->actual);
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) return NULL;
    return lista_iter_ver_actual(iter->actual); 
}

void hash_iter_destruir(hash_iter_t *iter) {
    free(iter);
}