#include "lista.h"
#include "pa2mm.h"

void dadoQueNecesitoUnaLista_siCreoUnaListaNueva_devuelvoUnaListaVacia(){
  lista_t* nueva_lista = lista_crear();

  pa2m_afirmar(nueva_lista->nodo_inicio == NULL, "Se obtuvo una lista con un nodo inicio igual a NULL");
  pa2m_afirmar(nueva_lista->nodo_fin == NULL, "Se obtuvo una lista con un nodo fin igual a NULL");
  pa2m_afirmar(nueva_lista->cantidad == 0, "Se obtuvo una lista con cantidad igual a 0");

  lista_destruir(nueva_lista);
}

void dadaUnaListaVacia_siLeAgregoUnElemento_resultaEnUnaListaConUnElemento(){
  lista_t* lista_null = NULL;
  lista_t* nueva_lista = lista_crear();
  void* elemento = malloc(sizeof(int));

  pa2m_afirmar(lista_insertar(lista_null, elemento) == -1, "Dada una lista nula, devuelvo -1");
  pa2m_afirmar(lista_insertar(nueva_lista, elemento) == 0, "Se pudo agregar un elemento a la lista");
  pa2m_afirmar(nueva_lista->nodo_inicio->elemento == elemento && elemento == nueva_lista->nodo_fin->elemento ,"El primer y ultimo elemento de la lista es el elemento que agregué");

  free(elemento);
  lista_destruir(nueva_lista);
}

void dadaUnaLista_siAgregoElementos_laListaSeAgranda(){
  lista_t* lista = lista_crear();
  void* elemento = malloc(sizeof(char));
  lista_insertar(lista, elemento);

  pa2m_afirmar(lista_insertar(lista, elemento) == 0, "Se pudo agregar un elemento nuevo a la lista");
  pa2m_afirmar(lista_elementos(lista) == 2, "Se obtuvo una lista con dos elementos");
  pa2m_afirmar(lista_insertar(lista, elemento) == 0, "Se pudo agregar un elemento nuevo a la lista");
  pa2m_afirmar(lista_elementos(lista) == 3, "Se obtuvo una lista con tres elementos");

  free(elemento);
  lista_destruir(lista);
}

void dadaUnaLista_siPidoElElementoDeUnaPosicion_reciboEseElemento(){
  lista_t* lista = lista_crear();
  void* elemento = malloc(sizeof(char));
  void* elemento1 = malloc(sizeof(int));
  void* elemento2 = malloc(sizeof(float));
  lista_insertar(lista, elemento);
  lista_insertar(lista, elemento1);
  lista_insertar(lista, elemento2);

  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == elemento, "El primer elemento de la lista es el primer agregado");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == elemento1, "El segundo elemento de la lista es el segundo agregado");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == elemento2, "El tercer elemento de la lista es el tercer agregado");

  free(elemento);
  free(elemento1);
  free(elemento2);
  lista_destruir(lista);
}

void dadaUnaLista_siLeAgregoElementos_puedoSaberConCuantosElementosCuenta(){
  lista_t* lista = lista_crear();
  void* elemento = malloc(sizeof(char));

  pa2m_afirmar(lista_elementos(lista) == 0, "La lista no tiene elementos o no existe");
  lista_insertar(lista, elemento);
  pa2m_afirmar(lista_elementos(lista) == 1, "La lista tiene un elemento");
  lista_insertar(lista, elemento);
  pa2m_afirmar(lista_elementos(lista) == 2, "La lista tiene dos elementos");
  lista_insertar(lista, elemento);
  pa2m_afirmar(lista_elementos(lista) == 3, "La lista tiene tres elementos");

  free(elemento);
  lista_destruir(lista);
}

void dadaUnaLista_siLePasoUnElementoYunaPosicion_elElementoSeAgregaEnEsaPosicionDeLaLista(){
  lista_t* lista = lista_crear();
  void* primer_elemento = malloc(sizeof(int));
  void* elemento = malloc(sizeof(char));
  void* ultimo_elemento = malloc(sizeof(float));
  void* otro_elemento = malloc(sizeof(double));

  pa2m_afirmar(lista_insertar_en_posicion(lista, primer_elemento, 20) == 0, "Si paso una lista vacía, el elemento se agrega en la primer posición");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == primer_elemento, "El elemento agregado es el que se encuentra en la primer posicion de la lista");
  pa2m_afirmar(lista->nodo_inicio->elemento == primer_elemento, "El elemento agregado queda al principio de la lista");
  
  pa2m_afirmar(lista_insertar_en_posicion(lista, elemento, 20) == 0, "Si paso una posicion inválida, el elemento se agrega en la última posición");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == elemento, "El elemento agregado es el que se encuentra en la segunda posicion de la lista");
  pa2m_afirmar(lista->nodo_fin->elemento == elemento, "El elemento agregado queda en final de la lista");

  pa2m_afirmar(lista_insertar_en_posicion(lista, ultimo_elemento, 2) == 0, "Se pudo agregar algo como tercer elemento de la lista");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == ultimo_elemento, "El elemento agregado es el que se encuentra en la tercer posicion de la lista");
  pa2m_afirmar(lista->nodo_fin->elemento == ultimo_elemento, "El elemento agregado queda en final de la lista");
  pa2m_afirmar(lista_elementos(lista) == 3, "La cantidad de elementos en la lista es igual a la cantidad de elementos agregados");

  pa2m_afirmar(lista_insertar_en_posicion(lista, elemento, 20) == 0, "Si paso una posicion inválida, el elemento se agrega en la última posición");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == elemento, "El elemento agregado es el que se encuentra en la segunda posicion de la lista");
  pa2m_afirmar(lista->nodo_fin->elemento == elemento, "El elemento agregado queda en final de la lista");
  pa2m_afirmar(lista_elementos(lista) == 4, "La cantidad de elementos en la lista es igual a la cantidad de elementos agregados");

  pa2m_afirmar(lista_insertar_en_posicion(lista, otro_elemento, 0) == 0, "Si paso la primer posicion, el elemento se agrega al inicio de la lista");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == otro_elemento, "El elemento agregado es el que se encuentra en la primer posicion de la lista");
  pa2m_afirmar(lista->nodo_inicio->elemento == otro_elemento, "El elemento agregado queda al principio de la lista");
  pa2m_afirmar(lista_elementos(lista) == 5, "La cantidad de elementos en la lista es igual a la cantidad de elementos agregados");
  
  free(elemento);
  free(primer_elemento);
  free(ultimo_elemento);
  free(otro_elemento);
  lista_destruir(lista);
}

void dadaUnaLista_siLaListaTieneElementos_seBorraElUltimoElementoDeLaLista(){
  lista_t* lista = lista_crear();
  void* elemento = malloc(sizeof(char));
  void* otro_elemento = malloc(sizeof(int));

  lista_insertar(lista, otro_elemento);
  lista_insertar(lista, elemento);
  lista_insertar(lista, otro_elemento);
  lista_insertar(lista, elemento);
  pa2m_afirmar(lista_borrar(lista) == 0, "Se borró el último elemento de la lista");
  pa2m_afirmar(lista_elementos(lista) == 3, "La lista ahora tiene 3 elementos");
  pa2m_afirmar(lista->nodo_fin->elemento == otro_elemento, "El último elemento de la lista es el que estaba anteúltimo");
  pa2m_afirmar(lista_borrar(lista) == 0, "Se borró el último elemento de la lista");
  pa2m_afirmar(lista_elementos(lista) == 2, "La lista ahora tiene 2 elementos");
  pa2m_afirmar(lista_borrar(lista) == 0, "Se borró el último elemento de la lista");
  pa2m_afirmar(lista_elementos(lista) == 1, "La lista ahora tiene 1 elemento");
  pa2m_afirmar(lista->nodo_fin->elemento == otro_elemento, "El último elemento de la lista es el que estaba anteúltimo");
  pa2m_afirmar(lista_borrar(lista) == 0, "Se borró el último elemento de la lista");
  pa2m_afirmar(lista_elementos(lista) == 0, "La lista quedó vacía");
  pa2m_afirmar(lista_borrar(lista) == -1, "Dada una lista sin elementos devuelvo -1");

  free(elemento);
  free(otro_elemento);
  lista_destruir(lista);
}

void dadaUnaLista_siLePasoLaPosicionDeUnElemento_seBorraElElementoDeEsaPosicionDeLaLista(){
  lista_t* lista = lista_crear();
  void* elemento = malloc(sizeof(char));

  lista_insertar(lista, elemento);
  lista_insertar(lista, elemento);
  lista_insertar(lista, elemento);
  lista_insertar(lista, elemento);
  pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == 0, "Se borró el primer elemento de la lista");
  pa2m_afirmar(lista_elementos(lista) == 3, "La lista ahora tiene 3 elementos");
  pa2m_afirmar(lista_borrar_de_posicion(lista, 123) == 0, "Dada una posición inválida, se borró el último elemento de la lista");
  pa2m_afirmar(lista_elementos(lista) == 2, "La lista ahora tiene 2 elementos");
  pa2m_afirmar(lista_borrar_de_posicion(lista, 1) == 0, "Se borró el segundo elemento de la lista");
  pa2m_afirmar(lista_elementos(lista) == 1, "La lista ahora tiene 1 elemento");
  pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == 0, "Se borró el primer elemento de la lista");
  pa2m_afirmar(lista_elementos(lista) == 0, "La lista quedó vacía");

  free(elemento);
  lista_destruir(lista);
}

int main(){
  pa2m_nuevo_grupo("Pruebas de crear lista");
  dadoQueNecesitoUnaLista_siCreoUnaListaNueva_devuelvoUnaListaVacia();
  
  pa2m_nuevo_grupo("Pruebas de lista insertar");
  dadaUnaListaVacia_siLeAgregoUnElemento_resultaEnUnaListaConUnElemento();
  dadaUnaLista_siAgregoElementos_laListaSeAgranda();

  pa2m_nuevo_grupo("Pruebas de lista cantidad de elementos");
  dadaUnaLista_siLeAgregoElementos_puedoSaberConCuantosElementosCuenta();

  pa2m_nuevo_grupo("Pruebas de lista elemento en posición");
  dadaUnaLista_siPidoElElementoDeUnaPosicion_reciboEseElemento();

  pa2m_nuevo_grupo("Pruebas de lista insertar en posición");
  dadaUnaLista_siLePasoUnElementoYunaPosicion_elElementoSeAgregaEnEsaPosicionDeLaLista();
  
  pa2m_nuevo_grupo("Pruebas de lista borrar");
  dadaUnaLista_siLaListaTieneElementos_seBorraElUltimoElementoDeLaLista();

  pa2m_nuevo_grupo("Pruebas de lista borrar de posición");
  dadaUnaLista_siLePasoLaPosicionDeUnElemento_seBorraElElementoDeEsaPosicionDeLaLista();

  return pa2m_mostrar_reporte();
}
