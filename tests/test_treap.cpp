#include "../include/treap.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>

// funcion auxiliar para limpiar el arbol y no tener memory leaks en los tests
void limpiar(Nodo *&raiz) {
  if (raiz == nullptr)
    return;
  limpiar(raiz->izq);
  limpiar(raiz->der);
  delete raiz;
  raiz = nullptr;
}

// para contar cuantos tests pasaron
int tests_pasados = 0;
int tests_totales = 0;

void verificar(bool condicion, const char *nombre) {
  tests_totales++;
  if (condicion) {
    printf("  [OK] %s\n", nombre);
    tests_pasados++;
  } else {
    printf("  [FALLO] %s\n", nombre);
  }
}

// test 1: insertar y verificar tamaño
void test_insercion_basica() {
  printf("\n--- Test: Insercion basica ---\n");
  Nodo *raiz = nullptr;

  insertar(raiz, 10);
  insertar(raiz, 5);
  insertar(raiz, 15);

  verificar(obtenerTam(raiz) == 3, "Tamaño despues de insertar 3 elementos");
  verificar(buscar(raiz, 10), "Buscar 10 existe");
  verificar(buscar(raiz, 5), "Buscar 5 existe");
  verificar(buscar(raiz, 15), "Buscar 15 existe");
  verificar(!buscar(raiz, 7), "Buscar 7 no existe");

  limpiar(raiz);
}

// test 2: no insertar duplicados
void test_duplicados() {
  printf("\n--- Test: Duplicados ---\n");
  Nodo *raiz = nullptr;

  insertar(raiz, 10);
  insertar(raiz, 10);
  insertar(raiz, 10);

  verificar(obtenerTam(raiz) == 1, "Tamaño sigue siendo 1 con duplicados");
  verificar(buscar(raiz, 10), "El 10 sigue existiendo");

  limpiar(raiz);
}

// test 3: eliminar elementos
void test_eliminacion() {
  printf("\n--- Test: Eliminacion ---\n");
  Nodo *raiz = nullptr;

  insertar(raiz, 10);
  insertar(raiz, 5);
  insertar(raiz, 15);
  insertar(raiz, 3);
  insertar(raiz, 7);

  eliminar(raiz, 5);
  verificar(obtenerTam(raiz) == 4, "Tamaño despues de eliminar 1");
  verificar(!buscar(raiz, 5), "El 5 ya no existe");
  verificar(buscar(raiz, 3), "El 3 sigue ahi");
  verificar(buscar(raiz, 7), "El 7 sigue ahi");

  // eliminar algo que no existe
  eliminar(raiz, 100);
  verificar(obtenerTam(raiz) == 4,
            "Tamaño no cambia al eliminar algo inexistente");

  limpiar(raiz);
}

// test 4: kesimo elemento
void test_kesimo() {
  printf("\n--- Test: K-esimo menor ---\n");
  Nodo *raiz = nullptr;

  // inserto en desorden a proposito
  insertar(raiz, 30);
  insertar(raiz, 10);
  insertar(raiz, 50);
  insertar(raiz, 20);
  insertar(raiz, 40);

  // el orden seria: 10, 20, 30, 40, 50
  verificar(kesimo(raiz, 1) == 10, "1er menor = 10");
  verificar(kesimo(raiz, 2) == 20, "2do menor = 20");
  verificar(kesimo(raiz, 3) == 30, "3er menor = 30");
  verificar(kesimo(raiz, 4) == 40, "4to menor = 40");
  verificar(kesimo(raiz, 5) == 50, "5to menor = 50");

  limpiar(raiz);
}

// test 5: contar menores
void test_contar_menores() {
  printf("\n--- Test: Contar menores ---\n");
  Nodo *raiz = nullptr;

  insertar(raiz, 10);
  insertar(raiz, 20);
  insertar(raiz, 30);
  insertar(raiz, 40);
  insertar(raiz, 50);

  verificar(contarMenores(raiz, 10) == 0, "Menores que 10 = 0");
  verificar(contarMenores(raiz, 25) == 2, "Menores que 25 = 2 (10 y 20)");
  verificar(contarMenores(raiz, 50) == 4, "Menores que 50 = 4");
  verificar(contarMenores(raiz, 51) == 5, "Menores que 51 = 5 (todos)");
  verificar(contarMenores(raiz, 1) == 0, "Menores que 1 = 0 (ninguno)");

  limpiar(raiz);
}

// test 6: arbol vacio
void test_arbol_vacio() {
  printf("\n--- Test: Arbol vacio ---\n");
  Nodo *raiz = nullptr;

  verificar(obtenerTam(raiz) == 0, "Tamaño de arbol vacio = 0");
  verificar(!buscar(raiz, 5), "Buscar en arbol vacio = false");
  verificar(contarMenores(raiz, 5) == 0, "Contar menores en arbol vacio = 0");

  // eliminar de arbol vacio no deberia explotar
  eliminar(raiz, 5);
  verificar(obtenerTam(raiz) == 0, "Eliminar de arbol vacio no rompe nada");
}

// test 7: caso del ejemplo de SPOJ
void test_ejemplo_spoj() {
  printf("\n--- Test: Ejemplo de SPOJ ---\n");
  Nodo *raiz = nullptr;

  // entrada del ejemplo:
  // I -1, I -1, I 2, C 0, K 2, D -1, K 1, K 2
  insertar(raiz, -1);
  insertar(raiz, -1); // duplicado, no hace nada
  insertar(raiz, 2);

  verificar(obtenerTam(raiz) == 2, "Despues de I -1, I -1, I 2 -> tamaño 2");

  // C 0 -> cuantos menores que 0? solo el -1
  verificar(contarMenores(raiz, 0) == 1, "C 0 = 1");

  // K 2 -> el 2do menor: -1, 2 -> es 2
  verificar(kesimo(raiz, 2) == 2, "K 2 = 2");

  // D -1 -> eliminar -1
  eliminar(raiz, -1);
  verificar(obtenerTam(raiz) == 1, "Despues de D -1 -> tamaño 1");

  // K 1 -> el 1er menor: solo queda 2
  verificar(kesimo(raiz, 1) == 2, "K 1 = 2");

  // K 2 -> no hay 2do elemento, deberia ser "invalid"
  // en el main se chequea con el tamaño, aca solo verificamos que tam < 2
  verificar(obtenerTam(raiz) < 2, "K 2 con 1 elemento -> seria invalid");

  limpiar(raiz);
}

// test 8: muchas inserciones y eliminaciones
void test_estres_basico() {
  printf("\n--- Test: Estres basico (100 ops) ---\n");
  Nodo *raiz = nullptr;

  // inserto del 0 al 99
  for (int i = 0; i < 100; i++) {
    insertar(raiz, i);
  }
  verificar(obtenerTam(raiz) == 100, "100 inserciones -> tamaño 100");

  // verifico kth
  verificar(kesimo(raiz, 1) == 0, "1er menor = 0");
  verificar(kesimo(raiz, 50) == 49, "50mo menor = 49");
  verificar(kesimo(raiz, 100) == 99, "100mo menor = 99");

  // elimino los pares
  for (int i = 0; i < 100; i += 2) {
    eliminar(raiz, i);
  }
  verificar(obtenerTam(raiz) == 50,
            "Despues de eliminar pares -> 50 elementos");
  verificar(kesimo(raiz, 1) == 1, "1er menor ahora es 1");

  limpiar(raiz);
}

int main() {
  srand(42); // semilla fija para que los tests sean reproducibles

  printf("========================================\n");
  printf("  Tests unitarios del Treap - ORDERSET\n");
  printf("========================================\n");

  test_insercion_basica();
  test_duplicados();
  test_eliminacion();
  test_kesimo();
  test_contar_menores();
  test_arbol_vacio();
  test_ejemplo_spoj();
  test_estres_basico();

  printf("\n========================================\n");
  printf("  Resultado: %d/%d tests pasados\n", tests_pasados, tests_totales);
  printf("========================================\n");

  return (tests_pasados == tests_totales) ? 0 : 1;
}
