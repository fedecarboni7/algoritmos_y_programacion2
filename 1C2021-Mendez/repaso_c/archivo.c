#include <stdio.h>
#include <string.h>

#define MAX_NOMBRE 500
#define FORMATO_LECTURA "%[^;];%i;%[^;];%[^;];%i\n"
#define FORMATO_ESCRITURA "%s;%i;%s;%s;%i\n"

typedef struct medallista{
  char pais[MAX_NOMBRE];
  int anio;
  char disciplina[MAX_NOMBRE];
  char nombre[MAX_NOMBRE];
  int puntos;
}medallista_t;

void preguntar_nuevo_medallista( medallista_t* nuevo){
  printf("De que pais es el nuevo medallista?\n");
  scanf("%s", nuevo->pais);
  printf("Año en el que gano?\n");
  scanf("%i", &(nuevo->anio) );
  printf("En que deporte gano?\n");
  scanf("%s", nuevo->disciplina);
  printf("El nombre y apellido del master?\n");
  scanf("%s", nuevo->nombre);
  nuevo->puntos = 50;
}

void escribir_nuevos( FILE* viejo, FILE* actualizado){
  medallista_t actual;
  int leidos = fscanf( viejo, FORMATO_LECTURA, actual.pais, &actual.anio, actual.disciplina, actual.nombre, &actual.puntos);
  while(leidos != EOF){
    fprintf(actualizado, FORMATO_ESCRITURA, actual.pais, actual.anio, actual.disciplina, actual.nombre, actual.puntos);
    leidos = fscanf( viejo, FORMATO_LECTURA, actual.pais, &actual.anio, actual.disciplina, actual.nombre, &actual.puntos);
  }
  preguntar_nuevo_medallista(&actual);
  fprintf(actualizado, FORMATO_ESCRITURA, actual.pais, actual.anio, actual.disciplina, actual.nombre, actual.puntos);
}

int main(){

  FILE* archivo = fopen("archivo_medallistas.csv","r");
  if(!archivo){
    printf("No se pudo abrir el medallista\n");
    return -1;
  }
  FILE* nuevo = fopen("Escrito.csv","w");
  if(!nuevo){
    fclose(archivo);
    return -1;
  }
  escribir_nuevos(archivo, nuevo);

  fclose(archivo);
  fclose(nuevo);
  return 0;
}
