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
  lista_t* nueva_lista = lista_crear();
  void* elemento = malloc(sizeof(int));

  pa2m_afirmar(lista_insertar(nueva_lista, elemento) == 0, "Se pudo agregar un elemento a la lista");
  pa2m_afirmar(nueva_lista->cantidad == 1, "Se obtuvo una lista con un elemento");

  lista_destruir(nueva_lista);
}

void dadaUnaLista_siAgregoElementos_laListaSeAgranda(){
  lista_t* lista = lista_crear();
  void* elemento = malloc(sizeof(char));
  lista_insertar(lista, elemento); //Lista con un elemento
  void* elemento_nuevo = malloc(sizeof(int));

  pa2m_afirmar(lista_insertar(lista, elemento_nuevo) == 0, "Se pudo agregar un elemento nuevo a la lista");
  pa2m_afirmar(lista->cantidad == 2, "Se obtuvo una lista con dos elementos");

  lista_destruir(lista);
}

int main(){
  pa2m_nuevo_grupo("Pruebas de crear lista");
  dadoQueNecesitoUnaLista_siCreoUnaListaNueva_devuelvoUnaListaVacia();
  
  pa2m_nuevo_grupo("Pruebas de lista insertar");
  dadaUnaListaVacia_siLeAgregoUnElemento_resultaEnUnaListaConUnElemento();
  dadaUnaLista_siAgregoElementos_laListaSeAgranda();

  return pa2m_mostrar_reporte();
}
