#include "salon.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

salon_t* salon_leer_archivo(const char* nombre_archivo){
    salon_t* salon = malloc(sizeof(salon_t));
    if(!salon)
        return NULL;
    entrenador_t* entrenador = malloc(sizeof(entrenador_t));
    if(!entrenador)
        return NULL;
    FILE* archivo = fopen(nombre_archivo, "r");
    if(!archivo)
        return NULL;
    char* linea = fgets_alloc(archivo);
    size_t cantidad_vectores = vtrlen(split(linea, ';'));
    char** vector = split(linea, ';');
    int cant_entrenadores = 0;
    int cant_pokemones = 0;

    while(linea){
        if(cantidad_vectores == 2){//Compruebo que se trate de una línea de entrenador
            entrenador = crear_entrenador(vector, entrenador);
            cant_entrenadores++;
        }
        linea = fgets_alloc(archivo);
        vector = split(linea, ';');
        cantidad_vectores = vtrlen(split(linea, ';'));
        
        while(cantidad_vectores == 6 && linea){//Compruebo que se trate de una línea de pokemon
            pokemon_t* pokemon = crear_pokemon(vector);
            entrenador->equipo[cant_pokemones] = pokemon;
            cant_pokemones++;
            linea = fgets_alloc(archivo);
            vector = split(linea, ';');
            cantidad_vectores = vtrlen(split(linea, ';'));
        }
    }
    fclosen(archivo);
    return salon;
}

entrenador_t* crear_entrenador(char** vector, entrenador_t* entrenador){
    strcpy(entrenador->nombre, vector[0]);
    entrenador->victorias = atoi(vector[1]);
    return entrenador;
}

pokemon_t* crear_pokemon(char** vector){
    pokemon_t* pokemon = malloc(sizeof(pokemon_t));
    if(!pokemon)
        return NULL;
    strcpy(pokemon->nombre, vector[0]);
    pokemon->nivel = atoi(vector[1]);
    pokemon->defensa = atoi(vector[2]);
    pokemon->fuerza = atoi(vector[3]);
    pokemon->inteligencia = atoi(vector[4]);
    pokemon->velocidad = atoi(vector[5]);

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
    vtrfree(salon);
    free(salon->entrenadores);
    free(salon);
}
