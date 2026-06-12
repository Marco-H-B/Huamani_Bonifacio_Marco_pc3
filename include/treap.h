#ifndef TREAP_H
#define TREAP_H

#include <cstdio>
#include <cstdlib>
#include <ctime>

// esto es un nodo del treap
// cada nodo guarda su valor (clave), una prioridad random y el tamaño de su
// subarbol
struct Nodo {
  int clave;
  int prioridad;
  int tam; // tamaño del subarbol que cuelga de este nodo
  Nodo *izq;
  Nodo *der;

  Nodo(int val) {
    clave = val;
    prioridad = rand();
    tam = 1;
    izq = nullptr;
    der = nullptr;
  }
};

// para saber el tamaño de un subarbol sin que explote si es null
inline int obtenerTam(Nodo *nodo) {
  if (nodo == nullptr)
    return 0;
  return nodo->tam;
}

// recalcula el tamaño de un nodo sumando sus hijos + 1
inline void actualizar(Nodo *nodo) {
  if (nodo != nullptr) {
    nodo->tam = 1 + obtenerTam(nodo->izq) + obtenerTam(nodo->der);
  }
}

// split: parte el arbol en dos
// todo lo que es < clave va a izq, lo demas a der
void split(Nodo *nodo, int clave, Nodo *&izq, Nodo *&der);

// merge: junta dos arboles asumiendo que todo en izq < todo en der
void merge(Nodo *&resultado, Nodo *izq, Nodo *der);

// insertar un valor (si ya existe no hace nada)
void insertar(Nodo *&raiz, int val);

// eliminar un valor (si no existe no hace nada)
void eliminar(Nodo *&raiz, int val);

// devuelve el k-esimo menor elemento (1-indexado)
int kesimo(Nodo *nodo, int k);

// cuenta cuantos elementos son menores que val
int contarMenores(Nodo *nodo, int val);

// busca si un valor ya existe en el arbol
bool buscar(Nodo *nodo, int val);

int contarEnRango(Nodo *raiz, int A, int B);

#endif
