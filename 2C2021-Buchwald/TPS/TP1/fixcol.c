#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

int abrir_archivo(){
    FILE* archivo;
    archivo = fopen("archivo.txt", "r" );
    if (!archivo) return -1;
    return 0;
}

int leer_archivo(FILE* archivo){
    return int feof(archivo);
}

int main(){
    int retorno = 0;
    retorno += abrir_archivo();
    return retorno;
}