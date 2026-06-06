#include "../include/treap.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>

// este test compara el treap contra un vector ordenado
// es basicamente la solucion "tonta" O(n) vs el treap O(log n)
// si ambos dan lo mismo, el treap esta bien

// limpia el arbol
void limpiarArbol(Nodo *&raiz) {
  if (raiz == nullptr)
    return;
  limpiarArbol(raiz->izq);
  limpiarArbol(raiz->der);
  delete raiz;
  raiz = nullptr;
}

// version fuerza bruta de kth usando vector ordenado
int kthBruto(std::vector<int> &v, int k) {
  if (k < 1 || k > (int)v.size())
    return -999999; // invalid
  return v[k - 1];  // ya esta ordenado
}

// version fuerza bruta de count menores
int contarMenoresBruto(std::vector<int> &v, int val) {
  int cnt = 0;
  for (int x : v) {
    if (x < val)
      cnt++;
  }
  return cnt;
}

int main() {
  printf("=============================================\n");
  printf("  Fuerza bruta vs Treap - Validacion cruzada\n");
  printf("=============================================\n\n");

  int semillas[] = {42, 123, 777, 2026, 31415};
  int errores = 0;
  int ops_totales = 0;

  for (int s = 0; s < 5; s++) {
    srand(semillas[s]);
    printf("--- Prueba con semilla %d ---\n", semillas[s]);

    Nodo *raiz = nullptr;
    std::vector<int> vec; // el vector ordenado (fuerza bruta)

    int n = 200; // operaciones por prueba

    for (int i = 0; i < n; i++) {
      int tipo = rand() % 4; // 0=insert, 1=delete, 2=kth, 3=count

      if (tipo == 0) {
        // insertar
        int val = rand() % 100 - 50; // valores entre -50 y 49
        insertar(raiz, val);

        // fuerza bruta: insertar si no existe
        auto it = std::lower_bound(vec.begin(), vec.end(), val);
        if (it == vec.end() || *it != val) {
          vec.insert(it, val);
        }
        ops_totales++;
      } else if (tipo == 1 && !vec.empty()) {
        // eliminar un elemento que existe
        int idx = rand() % vec.size();
        int val = vec[idx];
        eliminar(raiz, val);
        vec.erase(vec.begin() + idx);
        ops_totales++;
      } else if (tipo == 2 && !vec.empty()) {
        // kth
        int k = rand() % vec.size() + 1;
        int resTreap = kesimo(raiz, k);
        int resBruto = kthBruto(vec, k);
        if (resTreap != resBruto) {
          printf("  ERROR kth: k=%d, treap=%d, bruto=%d\n", k, resTreap,
                 resBruto);
          errores++;
        }
        ops_totales++;
      } else if (tipo == 3) {
        // count menores
        int val = rand() % 120 - 60;
        int resTreap = contarMenores(raiz, val);
        int resBruto = contarMenoresBruto(vec, val);
        if (resTreap != resBruto) {
          printf("  ERROR count: val=%d, treap=%d, bruto=%d\n", val, resTreap,
                 resBruto);
          errores++;
        }
        ops_totales++;
      }

      // verifico que los tamaños coincidan
      if (obtenerTam(raiz) != (int)vec.size()) {
        printf("  ERROR tamaño: treap=%d, vector=%d\n", obtenerTam(raiz),
               (int)vec.size());
        errores++;
      }
    }

    printf("  Operaciones: %d, Tamaño final: %d\n", n, (int)vec.size());
    limpiarArbol(raiz);
  }

  printf("\n=============================================\n");
  printf("  Total operaciones: %d\n", ops_totales);
  if (errores == 0) {
    printf("  RESULTADO: Todo coincide! 0 errores\n");
  } else {
    printf("  RESULTADO: %d errores encontrados\n", errores);
  }
  printf("=============================================\n");

  return errores == 0 ? 0 : 1;
}
