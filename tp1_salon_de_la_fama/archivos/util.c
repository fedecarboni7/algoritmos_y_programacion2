#include "util.h"
#include <string.h>

size_t buscar_posicion_separador(const char* str, char separador, size_t posicion){
    while(str[posicion] != separador && str[posicion] != '\0')
        posicion++;
    return posicion;
}

char* duplicar_string(const char* str, size_t posicion_separador, size_t posicion_inicio){
    size_t tamanio = posicion_separador - posicion_inicio;
    char*palabra = malloc(sizeof(char*)* tamanio+1);
    if(!palabra){
        return NULL;
        }
    for(size_t contador = 0; contador < tamanio; contador++)
        palabra[contador] = str[posicion_inicio + contador];
    
    palabra[tamanio] = 0;
    return palabra;
}

size_t vtrlen(void* ptr){
    if(ptr == NULL){
        return 0;
        }
    size_t contador = 0;
    while(((void**) ptr)[contador] != NULL){
        contador++;
    }
    return contador;
}

void* vtradd(void* ptr, void* item){
    size_t tamanio_anterior = vtrlen(ptr);
    ptr = realloc(ptr, sizeof(void*) * (tamanio_anterior + 2));
    if(!ptr){
        return NULL;
        }
    void** puntero = ptr;
    puntero[tamanio_anterior] = item;
    puntero[tamanio_anterior + 1] = NULL;
    return ptr;
}

void vtrfree(void* ptr){
    void** puntero = ptr;
    for(size_t i = 0; i < vtrlen(ptr); i++)
        free(puntero[i]);
    free(ptr);
}

char** split(const char* str, char separador){
    if(!str || strlen(str) == 0)
        return NULL;
    char** vector = NULL;
    size_t posicion_inicio = 0;
    while(posicion_inicio <= strlen(str)){
        size_t posicion_separador = buscar_posicion_separador(str, separador, posicion_inicio);
        char* palabra = duplicar_string(str, posicion_separador, posicion_inicio);
        if(!palabra){
            free(palabra);
            return NULL;
        }
        vector = vtradd(vector, palabra);
        if(!vector){
            vtrfree(vector);
            free(palabra);
            return NULL;
        }
        posicion_inicio = posicion_separador+1;
    }
    return vector;
}

char* fgets_alloc(FILE* archivo){
    size_t tamanio = 512;
    size_t bytes_leidos = 0;
    char* buffer = malloc(tamanio);
    if (!buffer){
        return NULL;
        }
    while (fgets(buffer + bytes_leidos, (int)tamanio - (int)bytes_leidos, archivo)){
        size_t leido = strlen(buffer + bytes_leidos);
        if (leido > 0 && *(buffer + bytes_leidos + leido - 1) == '\n'){
            return buffer;
        } else {
            char* auxiliar = realloc(buffer,  tamanio * 2);
            if(!auxiliar) {
                free(buffer);
                return NULL;
            }
            buffer = auxiliar;
            tamanio *= 2;
        }
        bytes_leidos += leido;
    }
    if(bytes_leidos == 0){
        free(buffer);
        return NULL;
    }
    return buffer;
}

void fclosen(FILE* archivo){
    if(archivo)
        fclose(archivo);
}
