#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "treap.h"

// por ahora solo el esqueleto, mañana le meto la implementacion del treap

int main() {
    srand(time(0));

    int q;
    scanf("%d", &q);

    Nodo* raiz = nullptr;

    while (q--) {
        char op;
        int x;
        scanf(" %c %d", &op, &x);

        if (op == 'I') {
            // insertar x en el conjunto
            insertar(raiz, x);
        }
        else if (op == 'D') {
            // eliminar x del conjunto
            eliminar(raiz, x);
        }
        else if (op == 'K') {
            // buscar el k-esimo menor
            int total = obtenerTam(raiz);
            if (x < 1 || x > total) {
                printf("invalid\n");
            } else {
                printf("%d\n", kesimo(raiz, x));
            }
        }
        else if (op == 'C') {
            // contar cuantos son menores que x
            printf("%d\n", contarMenores(raiz, x));
        }
    }

    return 0;
}
