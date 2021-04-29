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
    ((void**) ptr)[tamanio_anterior] = item;
    ((void**) ptr)[tamanio_anterior + 1] = NULL;
    return ptr;
}

void vtrfree(void* ptr){

}

char** split(const char* str, char separador){
    char** ptr = NULL;
    char* palabra = malloc(sizeof(char*));
    int contador;
    size_t tamanio_str;
    size_t i;
    size_t j;
    if(str == NULL || str[0] == 0)
        return NULL;
    for(i = 0; i < strlen(str); i++){
        palabra = NULL;
        tamanio_str = 0;
        while(str[i] != separador){
            tamanio_str++;
            i++;
        }
        palabra = malloc(sizeof(char*)* tamanio_str + 1);
        contador = 0;
        for(j = i - tamanio_str; j <= i; j++){
            palabra[contador] = str[j];
            contador++;
        }
        palabra[tamanio_str] = '\0';
        ptr = vtradd(ptr, palabra);
    }
    if(str[i+1] == 0){
        palabra = malloc(sizeof(char*)* 2);
        palabra[0] = 0;
        palabra[1] = '\0';
        ptr = vtradd(ptr, palabra);
    }
    return ptr;
}

char* fgets_alloc(FILE* archivo){
    return NULL;
}

void fclosen(FILE* archivo){

}
