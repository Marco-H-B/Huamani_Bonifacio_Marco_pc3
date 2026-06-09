#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include "../include/treap.h"

using namespace std;
using namespace std::chrono;

void liberarArbol(Nodo*& raiz) {
    if (raiz == nullptr) return;
    liberarArbol(raiz->izq);
    liberarArbol(raiz->der);
    delete raiz;
    raiz = nullptr;
}

int main() {
    srand(42);
    
    printf("==========================================\n");
    printf("  Benchmark del Treap (ORDERSET) - PC3\n");
    printf("==========================================\n\n");

    int N = 200000; // Limite de operaciones en SPOJ
    printf("Preparando %d operaciones aleatorias...\n", N);

    vector<pair<char, int>> ops;
    ops.reserve(N);

    // Generar operaciones simulando el caso de prueba real
    // 40% Inserciones, 20% Eliminaciones, 20% Kesimo, 20% Contar
    for (int i = 0; i < N; i++) {
        int r = rand() % 100;
        int val = (rand() % 2000000000) - 1000000000; // Valores grandes como en SPOJ
        
        if (r < 40) {
            ops.push_back({'I', val});
        } else if (r < 60) {
            ops.push_back({'D', val});
        } else if (r < 80) {
            int k = (rand() % 100000) + 1; // Un K cualquiera
            ops.push_back({'K', k});
        } else {
            ops.push_back({'C', val});
        }
    }

    printf("Iniciando benchmark (midiendo tiempo)...\n\n");

    Nodo* raiz = nullptr;
    int calculos_dummy = 0; // Para evitar que el compilador optimice el codigo

    auto start = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        char op = ops[i].first;
        int x = ops[i].second;

        if (op == 'I') {
            insertar(raiz, x);
        } else if (op == 'D') {
            eliminar(raiz, x);
        } else if (op == 'K') {
            int total = obtenerTam(raiz);
            if (x <= total) {
                calculos_dummy += kesimo(raiz, x);
            }
        } else if (op == 'C') {
            calculos_dummy += contarMenores(raiz, x);
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    printf("==========================================\n");
    printf("  Resultados\n");
    printf("==========================================\n");
    printf("Tiempo total para %d operaciones: %lld ms\n", N, duration.count());
    printf("Tiempo promedio por operacion: %.4f ms\n", (double)duration.count() / N);
    
    // SPOJ normalmente da 1 a 2 segundos de tiempo limite (1000ms a 2000ms)
    if (duration.count() < 1000) {
        printf("\n=> VEREDICTO: MUY RAPIDO! (Deberia pasar el Time Limit de SPOJ sobrado)\n");
    } else if (duration.count() < 2500) {
        printf("\n=> VEREDICTO: ACEPTABLE. (Podria pasar el Time Limit dependiendo del servidor)\n");
    } else {
        printf("\n=> VEREDICTO: PELIGRO. (Probablemente de Time Limit Exceeded en SPOJ)\n");
    }

    printf("Dummy calc (ignorar): %d\n", calculos_dummy);

    liberarArbol(raiz);
    return 0;
}
