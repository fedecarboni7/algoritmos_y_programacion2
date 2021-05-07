#include "salon.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

salon_t* salon_leer_archivo(const char* nombre_archivo){
    salon_t* salon = malloc(sizeof(salon_t));
    if(!salon)
        return NULL;
    entrenador_t* entrenador = malloc(sizeof(entrenador_t));
    if(!entrenador){
        free(salon);
        return NULL;
    }
    pokemon_t* pokemon = malloc(sizeof(pokemon_t));
    if(!pokemon){
        free(salon);
        free(entrenador);
        return NULL;
    }
    char* linea = fgets_alloc(nombre_archivo);
    size_t cantidad_vectores = vtrlen(split(linea, ';'));

    while(linea != NULL){
        if(cantidad_vectores == 2){//Compruebo que se trate de una línea de entrenador
            char** vector = split(linea, ';');
            void* aux = realloc(salon->entrenadores, sizeof(entrenador_t));
            if(!aux){
                free(salon);
                free(entrenador);
                free(pokemon);
                return NULL;
            }
            salon->entrenadores = aux;
            entrenador -> victorias = atoi(vector[1]);
        }
        if(cantidad_vectores == 6){//Compruebo que se trate de una línea de pokemon
            char** vector = split(linea, ';');
            void* aux = realloc(entrenador->equipo, sizeof(pokemon_t));
            if(!aux){
                free(salon);
                free(entrenador);
                free(pokemon);
                return NULL;
            }
            entrenador->equipo = aux;
            pokemon->defensa = atoi(vector[1]);
        }
        linea = fgets_alloc(nombre_archivo);
        cantidad_vectores = vtrlen(split(linea, ';'));
    }

    fclosen(nombre_archivo);
    return salon;
}

int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    return -1;
}

salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    return NULL;
}

entrenador_t** salon_obtener_entrenadores_mas_ganadores(salon_t* salon, int cantidad_minima_victorias){
    return NULL;
}

void salon_mostrar_entrenador(entrenador_t* entrenador){

}

void salon_destruir(salon_t* salon){
    vtrfree(salon);
    free(salon->entrenadores);
    free(salon);
}
