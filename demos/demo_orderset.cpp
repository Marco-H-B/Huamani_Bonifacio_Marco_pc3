#include "../include/treap.h"
#include <cstdio>
#include <cstdlib>

// este demo muestra el estado del treap despues de cada operacion

// imprime los elementos en orden (inorder)
void imprimirInorden(Nodo *nodo) {
  if (nodo == nullptr)
    return;
  imprimirInorden(nodo->izq);
  printf("%d ", nodo->clave);
  imprimirInorden(nodo->der);
}

// imprime info del arbol
void mostrarEstado(Nodo *raiz) {
  printf("  Tamaño: %d\n", obtenerTam(raiz));
  printf("  Elementos (inorden): ");
  if (raiz == nullptr) {
    printf("(vacio)");
  } else {
    imprimirInorden(raiz);
  }
  printf("\n");
  if (raiz != nullptr) {
    printf("  Raiz: clave=%d, prioridad=%d\n", raiz->clave, raiz->prioridad);
  }
  printf("\n");
}

int main() {
  srand(42);

  printf("==========================================\n");
  printf("  Demo interactivo - Treap para ORDERSET\n");
  printf("==========================================\n\n");

  Nodo *raiz = nullptr;

  // operaciones del ejemplo de SPOJ
  printf(">> I -1 (insertar -1)\n");
  insertar(raiz, -1);
  mostrarEstado(raiz);

  printf(">> I -1 (insertar -1 de nuevo, es duplicado)\n");
  insertar(raiz, -1);
  mostrarEstado(raiz);

  printf(">> I 2 (insertar 2)\n");
  insertar(raiz, 2);
  mostrarEstado(raiz);

  printf(">> C 0 (contar menores que 0)\n");
  int cnt = contarMenores(raiz, 0);
  printf("  Resultado: %d\n\n", cnt);

  printf(">> K 2 (2do menor)\n");
  int total = obtenerTam(raiz);
  if (2 > total) {
    printf("  Resultado: invalid\n\n");
  } else {
    printf("  Resultado: %d\n\n", kesimo(raiz, 2));
  }

  printf(">> D -1 (eliminar -1)\n");
  eliminar(raiz, -1);
  mostrarEstado(raiz);

  printf(">> K 1 (1er menor)\n");
  total = obtenerTam(raiz);
  if (1 > total) {
    printf("  Resultado: invalid\n\n");
  } else {
    printf("  Resultado: %d\n\n", kesimo(raiz, 1));
  }

  printf(">> K 2 (2do menor)\n");
  total = obtenerTam(raiz);
  if (2 > total) {
    printf("  Resultado: invalid\n\n");
  } else {
    printf("  Resultado: %d\n\n", kesimo(raiz, 2));
  }

  // ahora hago unas operaciones extra para que se vea mas interesante
  printf("==========================================\n");
  printf("  Operaciones adicionales\n");
  printf("==========================================\n\n");

  printf(">> Insertando: 5, 3, 7, 1, 4, 6, 9\n");
  int vals[] = {5, 3, 7, 1, 4, 6, 9};
  for (int v : vals) {
    insertar(raiz, v);
  }
  mostrarEstado(raiz);

  printf(">> C 5 (cuantos menores que 5)\n");
  printf("  Resultado: %d\n\n", contarMenores(raiz, 5));

  printf(">> K 4 (4to menor)\n");
  printf("  Resultado: %d\n\n", kesimo(raiz, 4));

  printf(">> D 3 (eliminar 3)\n");
  eliminar(raiz, 3);
  mostrarEstado(raiz);

  printf(">> D 7 (eliminar 7)\n");
  eliminar(raiz, 7);
  mostrarEstado(raiz);

  printf(">> K 1 al K %d (todos los elementos en orden)\n", obtenerTam(raiz));
  for (int i = 1; i <= obtenerTam(raiz); i++) {
    printf("  K %d = %d\n", i, kesimo(raiz, i));
  }

  printf("\n>> Rango [2, 6] (cuantos ay entre 2 y 6)\n");
  printf("Resultado en rango: %d\n", contarEnRango(raiz, 2, 6));

  printf("\nDemo terminado.\n");
  return 0;
}
