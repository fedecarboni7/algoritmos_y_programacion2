// Importar bibliotecas
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Constantes

const int CONSTANTE = 8;

// define  vectores, archivos /formatos de lectura o cuando rompen las constantes.

#define MAX_VECTOR 5
#define MAX_NOMBRE 50

#define PALABRA "Mensaje secreto"

// Existen la variables globales pero no las van a usar. F


// Los comentarios se pueden escribir asi pero es solo de una linea

/*
O Los podes escribir asi
Y te duran mas lineas
*/

// Creando nuestros propios tipos de datos. Structs
/*
  Lo que nos permiten los structs es trabajar con la abstraccion, de manera en que
  podemos representar en los sistemas, personas, objetos o lo que sea apartir de los datos
  que queremos saber


*/

typedef struct duenio{
  int edad;
  char nombre[MAX_NOMBRE];
}duenio_t

typedef struct gato{
  char color_pelo;
  bool es_gordo;
  int anios;
  char nombre[MAX_NOMBRE];
  duenio_t esclavo;
  struct gato* hijos;  // Puntero a struct gato
}gato_t;


int main(){

  //Sintaxis

  //En python estan acostumbrados a un tipado dinamico
  //Lo que significa que una variable podia hacer lo siguiente

  variable = 1
  variable = 'hola';

  /*
  Cuando lo intente compilar van a ver que no van a poder
  Y aca entra en cuenta que es un lenguaje de tipado estatico
  El lenguaje lo que tiene es que le tenes que decir de que tipo es
  cada una de las variables, y su tipo no puede cambiar. El final de cada linea
  siempre se marca con un ;

  Los siguientes tipos de datos se categorizan en primitivos y estructurados
  los tipos de datos primitivos son tipos de datos que ya vienen con el lenguaje
  C y son
  */


  // Declaracion de valores e inicializacion

  int ejemplo;   //Declaracion, contiene basura

  ejemplo = 9;   //Asignacion

  int ejemplo2 = 0; //Inicializacion

  // Numero de 4 bytes, el que van a usar la mayoria de las veces
  int numero = 4;

  //Short numero de 2 bytes, es chico rara vez lo van a usar
  short numerito = 1;

  //Long numero de 8 bytes, pueden tomar valores muy grandes o muy negativos

  long numerazo = 100000000000;

  //size_t  numero de 8 bytes, es SIEMPRE positivo, lo vamos a usar siempre para
  //        indicar cantidades debido a que es siempre positivo

  size_t cant_numeros = 3;

  //float  es de 4 bytes, es un numero con coma, no almacena bien numeros grandes

  float con_coma = 0.75;

  // double es de 8 bytes un numero con coma de mayor precision, es mas confiable
  //         para representar numeros con coma

  double con_coma_mejor = 0.000000075;

  // char es un unico caracter, pesa 1 byte

  char letra = 'h';


  // Guarda un valor de verdad, requiere la inclusion de la biblioteca stdbool
  // Solo puede tomar dos valores, true o false, se lo puede inicializar con una comparacion

  bool comparacion = true;

  comparacion = (4 == 5); //!= distinto  >   <   <=   >=


  //Interaccion con el usuario

  //Muestra un numero por la terminal
  printf("El numero impreso %i %c %s\n\t", numero, letra, string);

  //Pedir un numero por la terminal

  scanf("%i", &numero);

  printf("%i\n", numero);

  //Vectores y Matrices
  // Los vectores se pueden visualizar como tiradas todas continuas

  int vector[MAX_VECTOR];     //Buena practica

  int vector_2[5];

  size_t tamanio = 5;

  //Aca estoy declarando dos vectores del mismo largo, las dos formas funcionan pero la primera se considera una buena pracitca
  // debido a que si queremos cambiar el largo de todos los vectores simplemente agarramos entramos a la constante y lo cambiamos y ya esta.

  //Este vector esta lleno de basura, hay que inicializarlo. La primera posicion del vector es la posicion 0

  numero = vector[0];    // Se esta guardando dentro de numero el primer elemento de un vector, tambien se puede usar una variables
  int i = 0;

  numero = vector[i];

  /*
   Los vectores en esencia, son todos estos tipos de datos puestos uno al lado del otro en memoria.
   Sin embargo, cuando intentamos acceder a una posicion

   */

  int matriz[MAX_VECTOR][MAX_VECTOR];   //Es un vector de vectores. Se lo puede pensar como una matriz de dos dimensiones
  matriz[0][0]= 4;

  // Los vectores de caracteres los llamamos string y tiene un manejo especial a traves de la biblioteca string.h

  char string[MAX_NOMBRE];


  strcpy(dst,"source");
  strlen(string);
  strcmp(string1,string2);


  // Manejo de struct

  gato_t michi;    // De esta manera se acaba de crear un struct gato con basura en cada uno de sus campos

  michi.anios = 2;
  michi.es_gordo = false;
  michi.color_pelo = 'N';
  strcpy(michi.nombre, "Gato");     // Copia el string de la derecha y guarda la copia en el string de la izquierda

  michi.esclavo.edad = 45;

  gato_t neko = michi;

  // Si se paso un struct por referencia

  michi->anios = 2;
  (*michi).anios = 2;
  michi->esclavo.edad = 35;


  return 0;
}




/*
  Errores de compilacion a tener en cuenta

- Olvidarte el ;
* Usar el = para comparar en vez de ==
* Usar variables sin inicializar
* Tratar de acceder a campos de un NULL como si fuera un struct
- Olvidarte de desreferenciar el puntero cuando haces pasaje por referencia
- Pueden mostrar que te tira el compilador cuando escribis mal el nombre de una variable o función


Las que tienen un "-" son errores que te tira el compilador asi que pueden mostrar el mensaje de error.
Los que tienen un "*" son errores que no te tira el compilador pero que tienen que buscar y reconocer.

*/
