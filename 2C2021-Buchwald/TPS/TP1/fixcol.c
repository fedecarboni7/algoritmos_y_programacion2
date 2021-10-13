#include <stdio.h>
#include <stdlib.h>

int abrir_archivo(){
    FILE* archivo = fopen("archivo.txt", "r" );
    if (!archivo) return -1;
    return 0;
}


int main(){
    int retorno = 0;
    retorno += abrir_archivo();
    return retorno;
}