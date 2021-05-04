#include "salon.h"
#include "util.h"
#include <stdlib.h>

salon_t* salon_leer_archivo(const char* nombre_archivo){
    /* Comentado para evadir errores en make test
    
    salon_t* salon = malloc(sizeof(salon_t));
    entrenador_t* entrenador = malloc(sizeof(entrenador_t));
    pokemon_t* pokemon = malloc(sizeof(pokemon_t));
    
    char* linea = fgets_alloc(nombre_archivo);
    int cantidad_vectores = vtrlen(split(linea, ';'));

    while(linea != NULL){
        if(cantidad_vectores == 2){
            char** vector = split(linea, ';');
            //entrenador -> victorias = atoi(vector[1]);
        }
        if(cantidad_vectores == 6){
            char** vector = split(linea, ';');
            //pokemon;
        }
        linea = fgets_alloc(nombre_archivo);
        cantidad_vectores = vtrlen(split(linea, ';'));
    }

    fclosen(nombre_archivo);
    return NULL;
    */
    return NULL;
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

}
