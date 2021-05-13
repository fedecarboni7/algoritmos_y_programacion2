#include "salon.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

salon_t* salon_leer_archivo(const char* nombre_archivo){
    salon_t* salon = calloc(1, sizeof(salon_t));
    if(!salon)
        return NULL;
    FILE* archivo = fopen(nombre_archivo, "r");
    if(!archivo)
        return NULL;
    char* linea = fgets_alloc(archivo);
    size_t cantidad_vectores = vtrlen(split(linea, ';'));
    char** vector = split(linea, ';');
    entrenador_t* entrenador_actual = NULL;

    while(linea){
        if(cantidad_vectores == 2){//Compruebo que se trate de una línea de entrenador
            entrenador_actual = crear_y_agregar_entrenador(vector, salon);
            if(!entrenador_actual)
                return NULL;
        }
        else if(cantidad_vectores == 6){//Compruebo que se trate de una línea de pokemon
            pokemon_t* pokemon = crear_y_agregar_pokemon(vector, entrenador_actual);   
            if(!pokemon)
                return NULL;         
        }
        linea = fgets_alloc(archivo);
        vector = split(linea, ';');
        cantidad_vectores = vtrlen(split(linea, ';'));
    }
    fclosen(archivo);
    return salon;
}

entrenador_t* crear_y_agregar_entrenador(char** vector, salon_t* salon){
    entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
    if(!entrenador)
        return NULL;
    strcpy(entrenador->nombre, vector[0]);
    entrenador->victorias = atoi(vector[1]);
    entrenador->equipo = NULL;

    salon->entrenadores = vtradd(salon->entrenadores, entrenador);
    if(!salon->entrenadores)
        return NULL;

    return entrenador;
}

pokemon_t* crear_y_agregar_pokemon(char** vector, entrenador_t* entrenador_actual){
    pokemon_t* pokemon = calloc(1, sizeof(pokemon_t));
    if(!pokemon)
        return NULL;
    strcpy(pokemon->nombre, vector[0]);
    pokemon->nivel = atoi(vector[1]);
    pokemon->defensa = atoi(vector[2]);
    pokemon->fuerza = atoi(vector[3]);
    pokemon->inteligencia = atoi(vector[4]);
    pokemon->velocidad = atoi(vector[5]);

    entrenador_actual->equipo = vtradd(entrenador_actual->equipo, pokemon);
    if(!entrenador_actual->equipo)
        return NULL;

    return pokemon;
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
    vtrfree(salon->entrenadores);
    free(salon);
}
