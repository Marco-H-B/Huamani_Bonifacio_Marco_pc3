#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "../include/treap.h"

// funcion auxiliar
void borrar(Nodo*& raiz) {
    if (raiz == nullptr) return;
    borrar(raiz->izq);
    borrar(raiz->der);
    delete raiz;
    raiz = nullptr;
}

int aprobados = 0;
int totales = 0;

void check(bool condicion, const char* nombre) {
    totales++;
    if (condicion) {
        printf("  [PASO] %s\n", nombre);
        aprobados++;
    } else {
        printf("  [FALLO] %s\n", nombre);
    }
}

void test_numeros_extremos() {
    printf("\n--- Test: Numeros Extremos (Limites de int) ---\n");
    Nodo* raiz = nullptr;

    int max_int = 2147483647;
    int min_int = -2147483648;

    insertar(raiz, max_int);
    insertar(raiz, min_int);
    insertar(raiz, 0);

    check(obtenerTam(raiz) == 3, "Se insertaron los limites");
    check(buscar(raiz, max_int), "Max int encontrado");
    check(buscar(raiz, min_int), "Min int encontrado");
    
    check(kesimo(raiz, 1) == min_int, "K-esimo 1 es Min Int");
    check(kesimo(raiz, 3) == max_int, "K-esimo 3 es Max Int");

    check(contarMenores(raiz, 0) == 1, "Hay 1 menor a 0");
    check(contarMenores(raiz, max_int) == 2, "Hay 2 menores al max_int");
    check(contarMenores(raiz, min_int) == 0, "No hay menores al min_int");

    borrar(raiz);
}

void test_kth_invalido() {
    printf("\n--- Test: K-esimo invalido ---\n");
    Nodo* raiz = nullptr;

    insertar(raiz, 10);
    insertar(raiz, 20);

    // K menor a 1
    check(kesimo(raiz, 0) == -1 || kesimo(raiz, 0) < 0, "K=0 se maneja de forma segura");
    check(kesimo(raiz, -5) == -1 || kesimo(raiz, -5) < 0, "K=-5 se maneja de forma segura");

    // K mayor al tamaño
    // El codigo del treap asume que K <= tam (porque el main lo filtra),
    // pero veamos si explota o devuelve algo seguro si le pasamos K grande.
    // kesimo hace: si nodo == null return -1. 
    check(kesimo(raiz, 5) == -1, "K=5 (mayor a tam) devuelve -1 (seguro)");

    borrar(raiz);
}

void test_count_extremos() {
    printf("\n--- Test: Contar menores en limites ---\n");
    Nodo* raiz = nullptr;

    insertar(raiz, 10);
    insertar(raiz, 20);
    insertar(raiz, 30);

    check(contarMenores(raiz, 5) == 0, "Valor mas chico que el minimo");
    check(contarMenores(raiz, 35) == 3, "Valor mas grande que el maximo");

    borrar(raiz);
}

int main() {
    printf("========================================\n");
    printf("  Tests Casos Borde - Treap ORDERSET\n");
    printf("========================================\n");

    test_numeros_extremos();
    test_kth_invalido();
    test_count_extremos();

    printf("\n========================================\n");
    printf("  Resultados Casos Borde: %d/%d\n", aprobados, totales);
    printf("========================================\n");

    return (aprobados == totales) ? 0 : 1;
}
