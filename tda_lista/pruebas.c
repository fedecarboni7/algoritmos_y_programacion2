#include "lista.h"
#include "pa2mm.h"

void dadoQueNecesitoUnaLista_siCreoUnaListaNueva_devuelvoUnaListaVacia(){
  lista_t* nueva_lista = lista_crear();

  pa2m_afirmar(nueva_lista->nodo_inicio == NULL, "Se obtuvo una lista con un nodo inicio igual a NULL");
  pa2m_afirmar(nueva_lista->nodo_fin == NULL, "Se obtuvo una lista con un nodo fin igual a NULL");
  pa2m_afirmar(nueva_lista->cantidad == 0, "Se obtuvo una lista con cantidad igual a 0");

  free(nueva_lista);
}

void dadaUnaListaVacia_siLeAgregoUnElemento_resultaEnUnaListaNoVacia(){
  lista_t* nueva_lista = lista_crear();
  void* elemento = realloc(0, sizeof(char)*5);
  elemento = "algo";
  int resultado = lista_insertar(nueva_lista, elemento);

  pa2m_afirmar(resultado == 0, "Se pudo agregar un elemento a la lista");
  pa2m_afirmar(nueva_lista->cantidad != 0, "Se obtuvo una lista no vacía");

  free(nueva_lista);
}

int main() {
  pa2m_nuevo_grupo("Pruebas de crear lista");
  dadoQueNecesitoUnaLista_siCreoUnaListaNueva_devuelvoUnaListaVacia();
  
  pa2m_nuevo_grupo("Pruebas de lista insertar");
  dadaUnaListaVacia_siLeAgregoUnElemento_resultaEnUnaListaNoVacia();

  return pa2m_mostrar_reporte();
}
