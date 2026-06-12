#include "../include/treap.h"

// split: parte el arbol en dos partes
// izq se queda con los menores o iguales a clave
// der se queda con los mayores a clave
void split(Nodo *nodo, int clave, Nodo *&izq, Nodo *&der) {
  if (nodo == nullptr) {
    izq = nullptr;
    der = nullptr;
    return;
  }

  // si el valor del nodo es menor o igual, entonces este nodo y su izquierda
  // se van al arbol 'izq', y seguimos partiendo su derecha
  if (nodo->clave <= clave) {
    izq = nodo;
    split(nodo->der, clave, nodo->der, der);
    actualizar(izq);
  } else {
    // si es mayor, este nodo y su derecha se van a 'der'
    der = nodo;
    split(nodo->izq, clave, izq, nodo->izq);
    actualizar(der);
  }
}

// merge: junta dos arboles asumiendo que todo en izq es menor a todo en der
void merge(Nodo *&resultado, Nodo *izq, Nodo *der) {
  if (izq == nullptr) {
    resultado = der;
    return;
  }
  if (der == nullptr) {
    resultado = izq;
    return;
  }

  // el que tiene mayor prioridad va arriba para mantener la propiedad de heap
  if (izq->prioridad > der->prioridad) {
    resultado = izq;
    merge(resultado->der, izq->der, der);
  } else {
    resultado = der;
    merge(resultado->izq, izq, der->izq);
  }
  actualizar(resultado);
}

// busqueda basica de bst para ver si existe el valor
bool buscar(Nodo *nodo, int val) {
  if (nodo == nullptr)
    return false;
  if (nodo->clave == val)
    return true;
  if (val < nodo->clave)
    return buscar(nodo->izq, val);
  return buscar(nodo->der, val);
}

// insertar un elemento al treap
void insertar(Nodo *&raiz, int val) {
  if (buscar(raiz, val))
    return; // SPOJ dice que es un set, no repetidos

  Nodo *nuevo = new Nodo(val);
  Nodo *izq = nullptr;
  Nodo *der = nullptr;

  // parto el arbol en los menores a val y mayores a val
  split(raiz, val, izq, der);

  // y los vuelvo a juntar con el nuevo nodo al medio
  merge(raiz, izq, nuevo);
  merge(raiz, raiz, der);
}

// eliminar un elemento
void eliminar(Nodo *&raiz, int val) {
  if (!buscar(raiz, val))
    return; // si no esta ni me gasto

  Nodo *izq = nullptr;
  Nodo *der = nullptr;
  Nodo *medio = nullptr; // aca va a caer el nodo a borrar

  // parto en <= val-1 (que seria menor estricto) y el resto
  split(raiz, val - 1, izq, der);
  // ahora de ese resto saco al nodo que quiero borrar
  split(der, val, medio, der);

  // limpio memoria
  delete medio;

  // vuelvo a pegar las dos mitades
  merge(raiz, izq, der);
}

// encontrar el k-esimo elemento mas chico (1-indexado)
int kesimo(Nodo *nodo, int k) {
  if (nodo == nullptr)
    return -1; // por las dudas

  int tamIzq = obtenerTam(nodo->izq);

  // si k <= al tamaño de la izquierda, entonces mi k-esimo esta en la rama
  // izquierda
  if (k <= tamIzq) {
    return kesimo(nodo->izq, k);
  }
  // si k es justo el de la izquierda + 1, encontre a mi nodo
  if (k == tamIzq + 1) {
    return nodo->clave;
  }

  // si no, toca buscar a la derecha, pero le resto todo lo que deje a la
  // izquierda y el nodo actual
  return kesimo(nodo->der, k - tamIzq - 1);
}

// contar cuantos nodos son estrictamente menores que val
int contarMenores(Nodo *nodo, int val) {
  if (nodo == nullptr)
    return 0;

  if (nodo->clave < val) {
    // este nodo es menor, asi que cuenta el, toda su izquierda,
    // y lo que encontremos en su derecha
    int sumamos = obtenerTam(nodo->izq) + 1;
    return sumamos + contarMenores(nodo->der, val);
  } else {
    // este nodo es mayor o igual, entonces solo me fijo en su rama izquierda
    return contarMenores(nodo->izq, val);
  }
}

int contarEnRango(Nodo *raiz, int A, int B) {
  int limiteSup = contarMenores(raiz, B + 1);
  int limiteInf = contarMenores(raiz, A);

  return limiteSup - limiteInf;
}