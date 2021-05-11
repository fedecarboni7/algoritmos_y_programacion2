#include "util.h"
#include <string.h>

size_t vtrlen(void* ptr){
    if (ptr == NULL)
        return 0;
    size_t contador = 0;
    while (((void**) ptr)[contador] != NULL){
        contador++;
    }
    return contador;
}

void* vtradd(void* ptr, void* item){
    size_t tamanio_anterior = vtrlen(ptr);
    ptr = realloc(ptr, sizeof(void*) * (tamanio_anterior + 2));
    if(!ptr)
        return NULL;
    void** puntero = ptr;
    puntero[tamanio_anterior] = item;
    puntero[tamanio_anterior + 1] = NULL;
    return ptr;
}

void vtrfree(void* ptr){
    void** puntero = ptr;
    for(int i = 0; i <= vtrlen(ptr); i++){
        free(puntero[i]);
    }
    free(ptr);
}

char** split(const char* str, char separador){
    char** ptr = NULL;
    char* palabra;
    int contador;
    size_t tamanio_str;
    size_t i;
    size_t j;
    if(str == NULL || str[0] == 0)
        return NULL;
    for(i = 0; i < strlen(str); i++){
        tamanio_str = 0;
        while(str[i] != separador){
            tamanio_str++;
            i++;
        }
        palabra = malloc(sizeof(char*)* tamanio_str + 1);
        if(!palabra)
            return NULL;
        contador = 0;
        for(j = i - tamanio_str; j <= i; j++){
            palabra[contador] = str[j];
            contador++;
        }
        palabra[tamanio_str] = '\0';
        ptr = vtradd(ptr, palabra);
    }
    if(str[i] == 0){
        palabra = malloc(sizeof(char*)* 2);
        if(!palabra)
            return NULL;
        palabra[0] = 0;
        palabra[1] = '\0';
        ptr = vtradd(ptr, palabra);
    }
    return ptr;
}

char* fgets_alloc(FILE* archivo){
    size_t tamanio = 512;
    size_t bytes_leidos = 0;
    char* buffer = malloc(tamanio);
    if (!buffer)
        return NULL;
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
    if(!archivo)
        fclose(archivo);
}
