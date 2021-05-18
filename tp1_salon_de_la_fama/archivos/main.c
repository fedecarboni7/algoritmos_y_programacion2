#include "salon.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    printf("Crear un salon usando el archivo 'salon_original.sal'\n");
    salon_t* salon = salon_leer_archivo("salon_original.sal");
    if (!salon){
        salon_destruir(salon);
        return -1;
    }

    printf("\nObtener los entrenadores con al menos 3 ligas ganadas y mostrarlos por pantalla.\n");
    entrenador_t** entrenador_con_tres_o_mas_victorias = salon_obtener_entrenadores_mas_ganadores(salon, 3);
    if(!entrenador_con_tres_o_mas_victorias)
        return -1;
    size_t cantidad_entrenadores_con_tres_o_mas_victorias = vtrlen(entrenador_con_tres_o_mas_victorias);
    
    for(int i = 0; i < cantidad_entrenadores_con_tres_o_mas_victorias; i++){
        salon_mostrar_entrenador(entrenador_con_tres_o_mas_victorias[i]);
    }
    free(entrenador_con_tres_o_mas_victorias);

    printf("\nAgregar 2 entrenadores al salon con 5 y 7 victorias respectivamente.\n");
    entrenador_t* entrenador_1 = malloc(sizeof(entrenador_t));
    if(!entrenador_1)
        return -1;
    entrenador_t* entrenador_2 = malloc(sizeof(entrenador_t));
    if(!entrenador_2)
        return -1;
        
    strcpy(entrenador_1->nombre, "Nacho");
    entrenador_1->victorias = 5;
    entrenador_1->equipo = NULL;
    strcpy(entrenador_2->nombre, "Fede");
    entrenador_2->victorias = 7;
    entrenador_2->equipo = NULL;
    salon_agregar_entrenador(salon,entrenador_1);
    salon_agregar_entrenador(salon,entrenador_2);

    printf("\nObtener los entrenadores con al menos 5 ligas ganadas y mostrarlos por pantalla.\n");
    entrenador_t** entrenador_con_cinco_o_mas_victorias = salon_obtener_entrenadores_mas_ganadores(salon, 5);
    if(!entrenador_con_cinco_o_mas_victorias)
        return -1;
    size_t cantidad_entrenadores_con_cinco_o_mas_victorias = vtrlen(entrenador_con_cinco_o_mas_victorias);
    
    for(int i = 0; i < cantidad_entrenadores_con_cinco_o_mas_victorias; i++){
        salon_mostrar_entrenador(entrenador_con_cinco_o_mas_victorias[i]);
    }
    free(entrenador_con_cinco_o_mas_victorias);

    printf("\nGuardar el salon a un nuevo archivo 'salon_modificado.sal'\n");
    salon_guardar_archivo(salon, "salon_modificado.sal");
    salon_destruir(salon);

    printf("\nSalir con valor de retorno 0\n");
    return 0;
}
