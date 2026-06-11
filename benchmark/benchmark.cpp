#include "../include/treap.h"
#include <chrono>
#include <cstdio>
#include <cstdlib>

// Este benchmark prueba el rendimiento del treap con 200,000 operaciones
// que es el limite maximo que dice el problema ORDERSET en SPOJ.

int main() {
  printf("========================================\n");
  printf("  Benchmark del Treap (ORDERSET SPOJ)\n");
  printf("========================================\n\n");

  srand(42);
  Nodo *raiz = nullptr;
  int Q = 200000;

  printf("Iniciando prueba con %d operaciones...\n", Q);

  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < Q; i++) {
    int op = rand() % 4; // 0=I, 1=D, 2=K, 3=C
    int x = (rand() % 2000000000) -
            1000000000; // rango de -10^9 a 10^9 (como pide SPOJ)

    if (op == 0) {
      insertar(raiz, x);
    } else if (op == 1) {
      eliminar(raiz, x);
    } else if (op == 2) {
      int tam = obtenerTam(raiz);
      if (tam > 0) {
        int k = (rand() % tam) + 1;
        kesimo(raiz, k);
      }
    } else if (op == 3) {
      contarMenores(raiz, x);
    }
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duracion = end - start;

  printf("  Tiempo total: %.2f ms\n", duracion.count());
  printf("  Tamaño final del arbol: %d\n", obtenerTam(raiz));
  printf("  Operaciones por segundo: %.0f ops/s\n",
         (Q / (duracion.count() / 1000.0)));
  printf("\nBenchmark completado.\n");

  return 0;
}
