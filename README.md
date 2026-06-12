# Práctica Calificada 3 - CC232

**Alumno:** Huamani Bonifacio Marco Antonio  
**Código:** 20232741D  
**Curso:** CC232 - Algoritmos y Estructuras de Datos

---

## Problema asignado

**SPOJ ORDERSET - Order statistic set**  
Enlace: https://www.spoj.com/problems/ORDERSET/

Basicamente hay que mantener un conjunto de numeros enteros donde se pueda:

- **I x**: insertar x (si no esta repetido)
- **D x**: eliminar x (si existe)
- **K k**: devolver el k-esimo menor elemento, o "invalid" si k es mayor que el tamaño
- **C x**: contar cuantos elementos del conjunto son menores que x

Las restricciones son hasta 200,000 operaciones y los valores pueden ser hasta 10^9.

## Estructura usada

**Treap** (arbol binario de busqueda + heap por prioridades aleatorias).

Cada nodo guarda: clave, prioridad (random), tamaño del subarbol. Esto permite hacer las operaciones de insert, delete, kth y count en O(log n) esperado.

### Relacion con las semanas del curso:

- **Semana 5**: BST, busqueda ordenada, rotaciones, arboles aumentados
- **Semana 6**: Treap, heaps, order statistic tree

## Invariante

El treap mantiene dos propiedades al mismo tiempo:

1. **BST por clave**: todo lo de la izquierda es menor, todo lo de la derecha es mayor
2. **Heap por prioridad**: la prioridad del padre siempre es >= que la de sus hijos

Ademas cada nodo guarda el tamaño de su subarbol (`tam`) que se actualiza despues de cada split o merge.

## Complejidad

| Operacion | Complejidad esperada |
| --------- | -------------------- |
| Insertar  | O(log n)             |
| Eliminar  | O(log n)             |
| K-esimo   | O(log n)             |
| Contar    | O(log n)             |
| Total     | O(Q log n)           |
| Espacial  | O(n)                 |

## Compilacion

```bash
cmake -S . -B build
cmake --build build
```

## Ejecucion

```bash
./build/orderset < entrada.txt
```

## Pruebas

```bash
ctest --test-dir build
```

## Casos borde

- Consultar K cuando el conjunto esta vacio
- Insertar un valor que ya existe (no debe duplicar)
- Eliminar un valor que no existe (no debe hacer nada)
- K con k = 1 (el minimo) y k = n (el maximo)
- C con un valor menor que todos los elementos (debe dar 0)

## Declaracion de autoria

Este trabajo fue realizado de manera individual por Marco Antonio Huamani Bonifacio. El codigo fue desarrollado progresivamente como se puede ver en el historial de commits de Git.
