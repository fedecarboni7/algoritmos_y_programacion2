#include "salon.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

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
    if(!pokemon){
        return NULL;
        }
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

entrenador_t** ordenar_entrenadores_por_victorias(entrenador_t** vtr_entrenadores){
    entrenador_t* entrenador_aux;
    size_t cantidad_entrenadores = vtrlen(vtr_entrenadores);

    for(int entrenador_a = 0; entrenador_a < cantidad_entrenadores; entrenador_a++){
        for(int entrenador_b = 0; entrenador_b < cantidad_entrenadores; entrenador_b++){
            if(vtr_entrenadores[entrenador_b]->victorias > vtr_entrenadores[entrenador_a]->victorias){
                entrenador_aux = vtr_entrenadores[entrenador_a];
                vtr_entrenadores[entrenador_a] = vtr_entrenadores[entrenador_b];
                vtr_entrenadores[entrenador_b] = entrenador_aux;     
            }    
        }
    }
    return vtr_entrenadores;
}

salon_t* salon_leer_archivo(const char* nombre_archivo){
    salon_t* salon = calloc(1, sizeof(salon_t));
    if(!salon){
        return NULL;
        }
    FILE* archivo = fopen(nombre_archivo, "r");
    if(!archivo){
        free(salon);
        return NULL;
        }
    char* linea = fgets_alloc(archivo);
    char** vector = split(linea, ';');
    size_t cantidad_vectores = vtrlen(vector);
    entrenador_t* entrenador_actual = NULL;

    while(linea){
        if(cantidad_vectores == 2){//Compruebo que se trate de una línea de entrenador
            entrenador_actual = crear_y_agregar_entrenador(vector, salon);
            if(!entrenador_actual){
                free(salon);
                return NULL;
            }
        }
        else if(cantidad_vectores == 6){//Compruebo que se trate de una línea de pokemon
            pokemon_t* pokemon = crear_y_agregar_pokemon(vector, entrenador_actual);   
            if(!pokemon){
                free(salon);
                return NULL;
            }
        }
        free(linea);
        vtrfree(vector);
        linea = fgets_alloc(archivo);
        vector = split(linea, ';');
        cantidad_vectores = vtrlen(vector);
    }
    free(linea);
    vtrfree(vector);
    fclosen(archivo);
    return salon;
}

int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    FILE* archivo = fopen(nombre_archivo,"w");
    if(!archivo)
        return -1;
        
    size_t cantidad_entrenadores = vtrlen(salon->entrenadores);
    if(cantidad_entrenadores == 0)
        return -1;

    for(size_t contador_entrenadores = 0; contador_entrenadores < cantidad_entrenadores; contador_entrenadores++){
        char* nombre_entrenador = salon->entrenadores[contador_entrenadores]->nombre;
        int victorias_entrenador = salon->entrenadores[contador_entrenadores]->victorias;
        fprintf(archivo,"%s;%i\n", nombre_entrenador, victorias_entrenador);
        size_t cantidad_pokemones = vtrlen(salon->entrenadores[contador_entrenadores]->equipo);
        for(size_t contador_pokemones = 0; contador_pokemones < cantidad_pokemones; contador_pokemones++){
            char* nombre_pokemon = salon->entrenadores[contador_entrenadores]->equipo[contador_pokemones]->nombre;
            int nivel_pokemon = salon->entrenadores[contador_entrenadores]->equipo[contador_pokemones]->nivel;
            int defensa_pokemon = salon->entrenadores[contador_entrenadores]->equipo[contador_pokemones]->defensa;
            int fuerza_pokemon = salon->entrenadores[contador_entrenadores]->equipo[contador_pokemones]->fuerza;
            int inteligencia_pokemon = salon->entrenadores[contador_entrenadores]->equipo[contador_pokemones]->inteligencia;
            int velocidad_pokemon = salon->entrenadores[contador_entrenadores]->equipo[contador_pokemones]->velocidad;
            fprintf(archivo,"%s;%i;%i;%i;%i;%i\n", nombre_pokemon,nivel_pokemon,defensa_pokemon,fuerza_pokemon,inteligencia_pokemon,velocidad_pokemon);
        }
    }
    fclosen(archivo);
    return (int)cantidad_entrenadores;
}

salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    if(!salon || !entrenador)
        return NULL;
    entrenador_t** vector_entrenadores = vtradd(salon->entrenadores,entrenador);
    vector_entrenadores = ordenar_entrenadores_por_victorias(vector_entrenadores);
    salon->entrenadores = vector_entrenadores;
    return salon;
}

entrenador_t** salon_obtener_entrenadores_mas_ganadores(salon_t* salon, int cantidad_minima_victorias){
    if(!salon)
        return NULL;
    if(cantidad_minima_victorias == 0)
        return salon->entrenadores;
    entrenador_t** vtr_entrenadores = NULL;
    size_t cantidad_entrenadores = vtrlen(salon->entrenadores);

    for(int entrenador = 0; entrenador < cantidad_entrenadores; entrenador++){
        entrenador_t* entrenador_actual = salon->entrenadores[entrenador];
        if(entrenador_actual->victorias >= cantidad_minima_victorias)
            vtr_entrenadores = vtradd(vtr_entrenadores, entrenador_actual);
    }
    return vtr_entrenadores;
}

void salon_mostrar_entrenador(entrenador_t* entrenador){
    size_t cantidad_pokemones = vtrlen(entrenador->equipo);
    printf("\nEl entrenador %s tiene %i victorias y los siguientes pokemones:\n",entrenador->nombre,entrenador->victorias);
    if(cantidad_pokemones == 0)
        printf("0 pokemones\n");
    else{
        for(int pokemon = 0; pokemon < cantidad_pokemones; pokemon++){
            char* nombre_pokemon = entrenador->equipo[pokemon]->nombre;
            int nivel_pokemon = entrenador->equipo[pokemon]->nivel;
            int defensa_pokemon = entrenador->equipo[pokemon]->defensa;
            int fuerza_pokemon = entrenador->equipo[pokemon]->fuerza;
            int inteligencia_pokemon = entrenador->equipo[pokemon]->inteligencia;
            int velocidad_pokemon = entrenador->equipo[pokemon]->velocidad;
            printf("%i. %s\n", pokemon+1, nombre_pokemon);
            printf("Nivel: %i | Defensa: %i | Fuerza: %i | Inteligencia: %i | Velocidad: %i\n", nivel_pokemon, defensa_pokemon, fuerza_pokemon, inteligencia_pokemon, velocidad_pokemon);
        }
    }
}

void salon_destruir(salon_t* salon){
    for(size_t i = 0; i < vtrlen(salon->entrenadores); i++)
        vtrfree(salon->entrenadores[i]->equipo);
    vtrfree(salon->entrenadores);
    free(salon);
}
