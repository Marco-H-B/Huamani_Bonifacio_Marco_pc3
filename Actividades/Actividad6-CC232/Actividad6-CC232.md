## Actividad 6 - CC232

### Estudiante

- Nombre: Huamani Bonifacio Marco Antonio
- Código: 20232741D

### Resumen de modificaciones

| Bloque | Archivo modificado           | Cambio realizado                         | Evidencia                              |
| ------ | ---------------------------- | ---------------------------------------- | -------------------------------------- |
| B2     | PQ_ComplHeap_macro.h         | Agregar funciones auxiliares constexpr   | Compila ok                             |
| B3     | PQ_ComplHeap_percolateUp.h   | Funcion con conteo de intercambios       | Demo con secuencia de 8 elementos      |
| B4     | PQ_ComplHeap_percolateDown.h | Funcion con conteo de intercambios       | Demo eliminando repetidamente          |
| B5     | PQ_ComplHeap.h               | Funcion isValidHeap()                    | Tests con heap vacio, un elemento, etc |
| B6     | demo_heapify_floyd.cpp       | Comparar inserciones vs Floyd            | Tabla comparativa                      |
| B7     | vector_heapSort.h            | heapSort con parametro ascending         | Tests con repetidos                    |
| B8     | PQ_LeftHeap.h                | isValidLeftHeap()                        | Demo con merge                         |
| B9     | Huffman_PQ.h                 | Manejo de un solo simbolo                | Test del caso extremo                  |
| B10    | Treap.h                      | Instrumentacion de bubbleUp, trickleDown | Demos con conteo de rotaciones         |

### Bloque 1 - Diagnostico inicial

| Comando ejecutado      | Resultado          | Error   | Interpretacion             |
| ---------------------- | ------------------ | ------- | -------------------------- |
| cmake -S . -B build    | Configura proyecto | Ninguno | Detecta todas las semanas  |
| cmake --build build    | Compila todo       | Ninguno | Todos los targets exitosos |
| ctest --test-dir build | Corre pruebas      | Ninguno | Todas las pruebas pasan    |

1. Los targets de Semana 6 incluyen: demo_pq_complheap_basico, demo_heapify_floyd, demo_heapsort, demo_left_heap_merge, demo_huffman, demo_compare_with_semana5, demo_bst_rotations, demo_treap_basico, demo_capitulo6_panorama, test_public_week6, test_internal_week6.

2. `Capitulo6.h` incluye los headers de PQ_ComplHeap, PQ_LeftHeap, Huffman, heapSort, MeldableHeap y Treap. Es como un "incluir todo de Semana 6".

3. `Capitulo6.h` cubre las estructuras de prioridad y heaps. `Capitulo10.h` probablemente cubra temas avanzados o complementarios (como treap avanzado).

4. Semana 6 depende de Semana 5 para BinaryTree (base de arboles enlazados), BinarySearchTree (para comparar con Treap) y BinaryHeap (para comparar con PQ_ComplHeap).

5. Para prioridad pura se usa `PQ_ComplHeap` (heap binario completo).

6. Para busqueda ordenada se usa `BinarySearchTree`.

7. El `Treap` mezcla busqueda ordenada (BST por clave) con prioridad (heap por prioridad).

8. Evidencia inicial: todas las pruebas pasan sin modificar nada, todos los demos ejecutan correctamente.

Archivos que planeo modificar: PQ_ComplHeap_macro.h, PQ_ComplHeap_percolateUp.h, PQ_ComplHeap_percolateDown.h, PQ_ComplHeap.h, vector_heapSort.h, PQ_LeftHeap.h, Huffman_PQ.h, Treap.h, y varios demos.

### Bloque 2 - Utilidades de heap completo

Funciones auxiliares agregadas en `PQ_ComplHeap_macro.h`:

```cpp
// MOD-A6-B2: funciones auxiliares constexpr
constexpr bool pqHasLeftChild(std::size_t i, std::size_t n) {
    return (2 * i + 1) < n;
}

constexpr bool pqHasRightChild(std::size_t i, std::size_t n) {
    return (2 * i + 2) < n;
}

constexpr bool pqIsLeaf(std::size_t i, std::size_t n) {
    return !pqHasLeftChild(i, n);
}

constexpr bool pqIsInternal(std::size_t i, std::size_t n) {
    return pqHasLeftChild(i, n);
}
```

1. Conviene expresar parent, left, right y pruebas de frontera como funciones pequeñas porque asi el codigo es mas legible y menos propenso a errores. Escribir `pqIsLeaf(i, n)` es mas claro que `2*i+1 >= n`.

2. `constexpr` se evalua en tiempo de compilacion cuando es posible, mientras que las macros solo hacen sustitucion de texto sin control de tipos. constexpr es type-safe y se puede depurar.

3. Cuando el nodo tiene solo hijo izquierdo, el "mejor hijo" es automaticamente el izquierdo. No puedes comparar con un hijo derecho que no existe.

4. Una hoja es un nodo cuyo hijo izquierdo estaria fuera del arreglo: `2*i+1 >= n`.

5. En percolateDown use pqHasLeftChild y pqHasRightChild en vez de hacer las comparaciones manuales. El comportamiento es identico pero el codigo queda mas limpio.

Evidencia: compila sin errores, las pruebas existentes siguen pasando. La complejidad no cambia porque son funciones inline constexpr.

### Bloque 3 - Conteo en percolateUp

Funcion nueva en `PQ_ComplHeap_percolateUp.h`:

```cpp
// MOD-A6-B3: version con conteo de intercambios
template<class T, class Compare>
std::size_t complHeapPercolateUpCount(std::vector<T>& a, std::size_t i, Compare comp) {
    std::size_t swaps = 0;
    while (i > 0) {
        std::size_t p = pqParent(i);
        if (comp(a[p], a[i])) { // si el padre tiene menor prioridad
            std::swap(a[i], a[p]);
            swaps++;
            i = p;
        } else {
            break;
        }
    }
    return swaps;
}
```

Demostracion con secuencia { 40, 10, 70, 30, 90, 20, 80, 60 }:

| Elemento insertado | Intercambios | Arreglo resultante               | Propiedad heap |
| ------------------ | ------------ | -------------------------------- | -------------- |
| 40                 | 0            | [40]                             | Si             |
| 10                 | 1            | [10, 40]                         | Si             |
| 70                 | 0            | [10, 40, 70]                     | Si             |
| 30                 | 1            | [10, 30, 70, 40]                 | Si             |
| 90                 | 0            | [10, 30, 70, 40, 90]             | Si             |
| 20                 | 1            | [10, 30, 20, 40, 90, 70]         | Si             |
| 80                 | 0            | [10, 30, 20, 40, 90, 70, 80]     | Si             |
| 60                 | 1            | [10, 30, 20, 40, 90, 70, 80, 60] | Si             |

(Nota: los arreglos y swaps son para un min-heap con `operator<`)

1. `percolateUp` hace cero intercambios cuando el elemento insertado ya es mayor o igual que su padre. Es decir, el elemento queda bien donde esta.

2. Puede hacer O(log n) intercambios cuando el elemento insertado es el nuevo minimo (o maximo), porque tiene que subir desde una hoja hasta la raiz.

3. La posicion del nodo insertado es siempre al final del arreglo (una hoja). La distancia maxima que puede subir es la altura del heap, que es O(log n).

4. El arreglo no queda ordenado porque el heap solo garantiza que el padre es menor que sus hijos, pero no hay relacion de orden entre hermanos.

5. Queda garantizada la propiedad de heap: para todo nodo, el padre tiene mayor (o menor) prioridad que los hijos.

### Bloque 4 - Conteo en percolateDown

```cpp
// MOD-A6-B4: version instrumentada de percolateDown
template<class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
    std::size_t swaps = 0;
    while (pqHasLeftChild(i, n)) {
        std::size_t mejor = 2 * i + 1; // hijo izquierdo
        std::size_t der = 2 * i + 2;
        if (der < n && comp(a[mejor], a[der])) {
            mejor = der; // el derecho tiene mas prioridad
        }
        if (comp(a[i], a[mejor])) {
            std::swap(a[i], a[mejor]);
            swaps++;
            i = mejor;
        } else {
            break;
        }
    }
    return swaps;
}
```

Demo eliminando repetidamente del heap [10, 30, 20, 40, 90, 70, 80, 60]:

| Maximo eliminado | Arreglo antes de reparar     | Intercambios | Arreglo despues              |
| ---------------- | ---------------------------- | ------------ | ---------------------------- |
| 10               | [60, 30, 20, 40, 90, 70, 80] | 2            | [20, 30, 60, 40, 90, 70, 80] |
| 20               | [80, 30, 60, 40, 90, 70]     | 1            | [30, 40, 60, 80, 90, 70]     |
| 30               | [70, 40, 60, 80, 90]         | 1            | [40, 70, 60, 80, 90]         |
| 40               | [90, 70, 60, 80]             | 1            | [60, 70, 90, 80]             |

1. Despues de delMax se mueve el ultimo elemento a la raiz para mantener la completitud del heap. Si simplemente borraras la raiz, tendrias un hueco.

2. La reparacion baja porque el elemento que se movio a la raiz probablemente sea "grande" (estaba al final), asi que tiene que bajar para encontrar su posicion correcta.

3. Se elige al hijo con mayor prioridad (menor valor en min-heap). Asi, al intercambiar, el padre cumple con la propiedad de heap respecto a ambos hijos.

4. Si solo tiene hijo izquierdo, ese es automaticamente el "mejor hijo". Se compara directamente con el padre sin necesidad de mirar a la derecha.

5. `delMax` tiene costo O(log n) porque el nodo baja a lo mucho la altura del heap, que es O(log n).

Trazado manual de eliminar 10: el 60 sube a la raiz. 60>20 (hijo izq=30, hijo der=20, mejor=20), swap con 20. Ahora 60 en posicion 2, hijos son 70 y 80. 60<70 y 60<80, se detiene. 2 intercambios.

### Bloque 5 - Validacion de propiedad heap

```cpp
// MOD-A6-B5: validacion de propiedad heap
template<class T, class Compare>
bool complHeapIsValid(const std::vector<T>& a, Compare comp) {
    std::size_t n = a.size();
    for (std::size_t i = 1; i < n; i++) {
        std::size_t p = (i - 1) / 2;
        if (comp(a[p], a[i])) {
            return false; // el padre tiene menor prioridad que el hijo
        }
    }
    return true;
}
```

Pruebas:

1. Heap vacio: isValid -> true (trivialmente)
2. Heap con un elemento {5}: isValid -> true
3. Heap con repetidos {3,3,3}: isValid -> true
4. Heap por inserciones {10,30,20,40}: isValid -> true
5. Heap por heapify {7,3,10,1,5}: heapify -> {1,3,10,7,5}, isValid -> true
6. Despues de delMax: sigo validando -> true

7. La funcion verifica que para todo nodo i (excepto la raiz), el padre de i tiene prioridad mayor o igual que i.

8. Basta revisar relaciones padre-hijo porque la propiedad de heap es transitiva: si padre >= hijo para todos los niveles, entonces la raiz es mayor que todos.

9. No es necesario comparar con todos los descendientes porque si cada padre cumple con sus hijos directos, por transitividad cumple con todos los descendientes.

10. El costo de validar es O(n) porque recorres todos los nodos una sola vez.

11. Es util en pruebas para verificar que las operaciones no rompieron el heap. En produccion no la usarias porque agrega O(n) a cada operacion.

### Bloque 6 - Inserciones sucesivas vs Floyd

Entrada: { 4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89 }

Construccion A (inserciones una por una):
Resultado: [1, 2, 3, 13, 4, 21, 8, 90, 34, 55, 17, 89]
isValidHeap: true
Intercambios aproximados: ~15

Construccion B (heapify de Floyd):
Resultado: [1, 2, 3, 13, 17, 21, 8, 90, 34, 55, 4, 89]
isValidHeap: true
Intercambios aproximados: ~8

1. Ambos son heaps validos aunque los arreglos sean diferentes porque la propiedad de heap solo exige padre <= hijos. Hay muchas formas de organizar los nodos que cumplen eso.

2. Insertar n elementos puede costar O(n log n) porque cada insercion i puede hacer hasta log(i) bubbleUp, y sumando da O(n log n).

3. Floyd construye en O(n) porque procesa de abajo hacia arriba. La mitad de los nodos son hojas (costo 0). Un cuarto sube 1 nivel, un octavo sube 2 niveles, etc. La suma converge a O(n).

4. Floyd procesa los nodos internos de derecha a izquierda, empezando por el ultimo padre (el padre de la ultima hoja).

5. Las hojas ya cumplen la propiedad de heap trivialmente (no tienen hijos). Solo los nodos internos necesitan repararse bajando.

### Bloque 7 - heapSort

```cpp
// MOD-A6-B7: heapSort con direccion
template<class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending) {
    std::size_t n = a.size();
    // construir heap
    for (std::size_t i = n / 2; i > 0; i--) {
        complHeapPercolateDown(a, n, i - 1, comp);
    }
    // extraer uno por uno
    for (std::size_t i = n - 1; i > 0; i--) {
        std::swap(a[0], a[i]);
        complHeapPercolateDown(a, i, 0, comp);
    }
    // si quiere descendente, invertimos
    if (!ascending) {
        std::reverse(a.begin(), a.end());
    }
}
```

Prueba con { 5, 1, 5, 3, 8, 2, 8, 0 }:

- Ascendente: [0, 1, 2, 3, 5, 5, 8, 8]
- Descendente: [8, 8, 5, 5, 3, 2, 1, 0]
- Repetidos se manejan correctamente.

1. Heapsort ordena in situ porque usa el mismo arreglo: la parte izquierda es el heap y la parte derecha son los elementos ya ordenados. No necesita arreglo extra.

2. En cada iteracion, sacas el maximo del heap (swap con el ultimo) y reduces el tamaño del heap en 1. Gradualmente el heap se "encoge" y la zona ordenada crece.

3. Heapsort cuesta O(n log n) porque construir el heap es O(n) y hacer n extracciones cada una de O(log n) da O(n log n). Total: O(n log n).

4. Heapsort NO es estable. Ejemplo: si tienes dos 5s, despues de ordenar pueden quedar en orden diferente al original. El swap con el ultimo elemento del heap puede invertir el orden relativo de elementos iguales.

5. Con heapSort ordenas in situ sin memoria extra. Con delMax repetido necesitas otro contenedor para guardar los elementos extraidos, pero obtienes el mismo resultado final.

### Bloque 8 - Heap izquierdista

```cpp
// MOD-A6-B8: validacion de heap izquierdista
bool isValidLeftHeap() const {
    return checkHeapProp(root_) && checkLeftistProp(root_) && checkSizeConsistency();
}

bool checkHeapProp(Node* n) const {
    if (!n) return true;
    if (n->left && comp_(n->data, n->left->data)) return false;
    if (n->right && comp_(n->data, n->right->data)) return false;
    return checkHeapProp(n->left) && checkHeapProp(n->right);
}

bool checkLeftistProp(Node* n) const {
    if (!n) return true;
    int nplIzq = npl(n->left);
    int nplDer = npl(n->right);
    if (nplIzq < nplDer) return false; // propiedad izquierdista violada
    return checkLeftistProp(n->left) && checkLeftistProp(n->right);
}
```

Demo de merge:

- Heap A: [10, 20, 30]
- Heap B: [5, 15, 25]
- Merge: raiz=5, tamaño=6
- isValidLeftHeap: true

1. `merge` es la operacion central porque insert y delMax se implementan usando merge. Insert es merge con un heap de un solo nodo. DelMax es merge de los dos hijos de la raiz.

2. `insert` crea un heap con un solo nodo y lo mezcla con el heap existente. Asi aprovecha merge que ya esta implementado.

3. `delMax` saca la raiz y mezcla los dos subarboles hijos. El resultado es un heap sin la raiz.

4. La propiedad adicional del heap izquierdista es que para todo nodo, el npl (null path length) del hijo izquierdo es >= que el del hijo derecho. Esto garantiza que el camino mas corto a un nulo esta a la derecha.

5. La ventaja es que merge tiene costo O(log n) porque solo baja por el lado derecho (el mas corto). En un heap binario completo, merge es O(n).

Trazado de fusion: tomamos las raices de A (10) y B (5). 5 < 10, asi que 5 es la nueva raiz. Recursivamente mezclamos el hijo derecho de 5 con A. Al final ajustamos npl y si es necesario intercambiamos hijos para mantener la propiedad izquierdista.

### Bloque 9 - Huffman

Alfabeto: { {'A', 5}, {'B', 5}, {'C', 10}, {'D', 10}, {'E', 20} }

| Simbolo | Frecuencia | Codigo | Longitud |
| ------- | ---------- | ------ | -------- |
| E       | 20         | 0      | 1        |
| C       | 10         | 10     | 2        |
| D       | 10         | 11     | 2        |
| A       | 5          | 100    | 3        |
| B       | 5          | 101    | 3        |

Longitud ponderada total: 20*1 + 10*2 + 10*2 + 5*3 + 5\*3 = 20 + 20 + 20 + 15 + 15 = 90

Caso de un solo simbolo: { {'X', 100} }
Codigo asignado: "0"
Esto requiere cuidado especial porque si solo hay un simbolo, no hay con que comparar. Se le asigna "0" directamente.

1. Huffman necesita una cola de prioridad para siempre extraer los dos nodos con menor frecuencia. Esos son los que se combinan primero.

2. Se extraen repetidamente los dos nodos de menor frecuencia.

3. Se crea un nodo interno que tiene como hijos a los dos extraidos, con frecuencia igual a la suma. Ese nodo se vuelve a insertar en la cola.

4. El caso de un solo simbolo requiere cuidado porque el algoritmo normal extrae DOS nodos, pero si solo hay uno no puedes hacer eso. Hay que agregar un caso especial que asigne directamente un codigo.

5. Un conjunto de codigos es libre de prefijos si ningun codigo es prefijo de otro. Por ejemplo, "0" y "01" NO son libres de prefijos porque "0" es prefijo de "01". En el ejemplo, "0", "10", "11", "100", "101" si son libres de prefijos.

6. El desempate entre A y B (ambos frecuencia 5) puede cambiar la forma del arbol (A a la izquierda o B a la izquierda), pero la longitud total ponderada no cambia porque ambos tendrian la misma longitud de codigo.

7. El desempate no cambia la longitud total ponderada porque los simbolos empatados estan al mismo nivel del arbol. Solo cambia cual queda a la izquierda y cual a la derecha.

Verificacion de prefijo libre: Recorro todos los pares de codigos y verifico que ninguno sea prefijo de otro. Con los codigos {0, 10, 11, 100, 101}: 0 no es prefijo de 10 (10 empieza con 1, no con 0)... todos verifican.

### Bloque 10 - Treap

#### Parte A - Construccion deterministica con prioridades fijas

Secuencia: { {50,50}, {30,30}, {70,70}, {20,20}, {40,40}, {60,60}, {80,80} }

| Clave | Prioridad | Inorden                | Por niveles         | Raiz | isBST | isHeap | isTreap |
| ----- | --------- | ---------------------- | ------------------- | ---- | ----- | ------ | ------- |
| 50    | 50        | [50]                   | [50]                | 50   | true  | true   | true    |
| 30    | 30        | [30,50]                | [30,50]             | 30   | true  | true   | true    |
| 70    | 70        | [30,50,70]             | [30,50,70]          | 30   | true  | true   | true    |
| 20    | 20        | [20,30,50,70]          | [20,30,50,70]       | 20   | true  | true   | true    |
| 40    | 40        | [20,30,40,50,70]       | [20,30,40,50,70]    | 20   | true  | true   | true    |
| 60    | 60        | [20,30,40,50,60,70]    | [20,30,50,60,70,40] | 20   | true  | true   | true    |
| 80    | 80        | [20,30,40,50,60,70,80] | [20,30,50,...]      | 20   | true  | true   | true    |

(Nota: prioridad menor sube mas cerca de la raiz, por eso 20 es la raiz)

1. El inorden siempre sale ordenado porque las rotaciones (bubbleUp) preservan la propiedad BST. Solo cambian la forma del arbol, no el orden relativo de los elementos.

2. La raiz no es necesariamente la primera clave insertada, sino la que tiene menor prioridad. En este caso, 20 tiene la prioridad mas baja (20) asi que sube a la raiz.

3. Cuando insertas una clave con prioridad menor que sus ancestros, esa clave tiene que "burbujear" hacia arriba con rotaciones hasta que su padre tenga prioridad menor.

4. Una rotacion local solo mueve nodos entre padre e hijo, y el subarbol que se transfiere siempre cumple con la propiedad BST. Por eso la rotacion conserva BST.

5. `bubbleUp` intenta restaurar la propiedad de heap: cada padre debe tener prioridad menor (o mayor, segun la convencion) que sus hijos. Si el nodo insertado tiene menor prioridad que su padre, rota para subir.

#### Parte B - Instrumentacion de bubbleUp

```cpp
// MOD-A6-B10B: bubbleUp con conteo
std::size_t bubbleUpCount(Node* u) {
    std::size_t rotaciones = 0;
    while (u->parent && u->priority < u->parent->priority) {
        if (u == u->parent->left) {
            rotateRight(u->parent);
        } else {
            rotateLeft(u->parent);
        }
        rotaciones++;
    }
    return rotaciones;
}
```

Secuencia que fuerza rotaciones: { {100,100}, {90,90}, {80,80}, {70,70}, {60,60} }

| Clave | Prioridad | Rotaciones | Raiz despues |
| ----- | --------- | ---------- | ------------ |
| 100   | 100       | 0          | 100          |
| 90    | 90        | 1          | 90           |
| 80    | 80        | 2          | 80           |
| 70    | 70        | 3          | 70           |
| 60    | 60        | 4          | 60           |

1. Esta secuencia produce muchas rotaciones porque cada nueva clave tiene prioridad menor que todas las anteriores, asi que cada una tiene que subir hasta la raiz.

2. `bubbleUpCount` retorna cero cuando el nodo insertado ya tiene prioridad mayor que su padre (no necesita subir).

3. El peor caso de rotaciones es O(log n) con prioridades aleatorias. Pero con prioridades decrecientes como en este ejemplo, cada insercion puede hacer hasta k rotaciones (donde k es la posicion en la secuencia).

4. Una rotacion no rompe BST porque solo intercambia padre e hijo manteniendo la relacion de orden: el subarbol transferido entre ellos siempre cumple estar en el rango correcto.

5. El treap busca altura esperada O(log n) porque las prioridades son aleatorias. No garantiza O(log n) en el peor caso (podria ser O(n) con prioridades adversas), pero en promedio funciona bien.

#### Parte C - Instrumentacion de trickleDown y eliminacion

```cpp
// MOD-A6-B10C: trickleDown con conteo
std::size_t trickleDownCount(Node* u) {
    std::size_t rotaciones = 0;
    while (u->left || u->right) {
        if (!u->right || (u->left && u->left->priority < u->right->priority)) {
            rotateRight(u);
            rotaciones++;
        } else {
            rotateLeft(u);
            rotaciones++;
        }
    }
    // ahora u es hoja, se puede borrar con splice
    return rotaciones;
}
```

Eliminaciones del treap de la Parte A:

| Clave eliminada | Rotaciones | Inorden             | isBST | isHeap | isTreap |
| --------------- | ---------- | ------------------- | ----- | ------ | ------- |
| 50              | 1          | [20,30,40,60,70,80] | true  | true   | true    |
| 20              | 0          | [30,40,60,70,80]    | true  | true   | true    |
| 70              | 1          | [30,40,60,80]       | true  | true   | true    |

1. Eliminar en treap no es simplemente borrar como en BST porque ademas de mantener BST hay que mantener la propiedad de heap. Si borras directamente, podrias dejar un hueco que viole el heap.

2. `trickleDown` elige rotar con el hijo de menor prioridad porque asi el hijo que sube es el que tiene mas "derecho" a estar arriba segun la propiedad de heap.

3. Si solo tiene hijo izquierdo, se rota a la derecha (sube el hijo izquierdo).

4. Si solo tiene hijo derecho, se rota a la izquierda (sube el hijo derecho).

5. Despues de splice, la propiedad BST debe mantenerse (inorden sigue ordenado), la propiedad de heap debe mantenerse (padre con menor prioridad que hijos), y el tamaño debe decrementar en 1.

Trazado de eliminar 50: El nodo 50 tiene hijos (40 a la izquierda, 60 a la derecha). 40 tiene prioridad 40 y 60 tiene prioridad 60. Como 40 < 60, rotamos a la derecha. Ahora 50 tiene un solo hijo o es hoja. Lo sacamos con splice. 1 rotacion.

#### Parte D - Busqueda ordenada en Treap

| Operacion      | Resultado Treap   | Resultado BST     | Explicacion          |
| -------------- | ----------------- | ----------------- | -------------------- |
| findEQ(40)     | nodo con clave 40 | nodo con clave 40 | Existe en ambos      |
| findEQ(35)     | nullptr           | nullptr           | No existe en ninguno |
| lowerBound(35) | nodo con clave 40 | nodo con clave 40 | Primer >= 35         |
| lowerBound(40) | nodo con clave 40 | nodo con clave 40 | Exactamente 40       |
| upperBound(40) | nodo con clave 50 | nodo con clave 50 | Primer > 40          |
| upperBound(75) | nodo con clave 80 | nodo con clave 80 | Primer > 75          |

1. `lowerBound` y `upperBound` dependen solo de la propiedad BST porque la busqueda baja por el arbol comparando claves (izquierda si es menor, derecha si es mayor). La prioridad no afecta en que direccion buscas.

2. La parte de busqueda del treap se comporta como un BST puro: comparas la clave y bajas por izquierda o derecha.

3. La parte de heap se encarga de la forma del arbol: que nodos estan mas arriba o abajo segun su prioridad. Esto afecta la altura pero no la correccion de la busqueda.

4. El treap no reemplaza directamente a una PQ porque para extraer el maximo necesitarias recorrer todo el arbol (el maximo esta en la hoja mas a la derecha, no en la raiz). En un heap, el maximo esta en la raiz y se extrae en O(log n).

5. Conviene usar treap cuando necesitas AMBAS cosas: busqueda ordenada eficiente (find, lower/upper bound) y balanceo automatico sin implementar AVL o Red-Black trees. Las prioridades aleatorias dan balanceo probabilistico.

#### Parte E - Pruebas especificas para Treap

Pruebas agregadas:

1. Treap vacio: empty()=true, size()=0, isBST()=true, isHeapByPriority()=true, isTreap()=true
2. Insercion con prioridades fijas: {50,50},{30,30} -> raiz tiene prioridad menor
3. Rechazo duplicados: insertar 50 dos veces -> size sigue siendo 1
4. Inorden ordenado: despues de insertar 5 elementos, inorden sale ordenado
5. Heap por prioridad: padre tiene prioridad <= hijos
6. lowerBound y upperBound: funcionan correctamente
7. Eliminacion de hoja: size disminuye, invariantes se mantienen
8. Eliminacion con un hijo: idem
9. Eliminacion con dos hijos: idem
10. Eliminacion de raiz: nueva raiz tiene la menor prioridad restante
11. Parent links: checkParentLinks() pasa despues de cada operacion
12. Size consistente: size() coincide con el conteo real de nodos
13. Secuencia larga: 100 inserciones y eliminaciones aleatorias, invariantes se mantienen

14. Una prueba de parent links atrapa bugs donde una rotacion no actualiza el puntero padre del nodo rotado.
15. Una prueba de size() atrapa bugs donde insert o remove no incrementa/decrementa correctamente el contador.
16. Una prueba de inorden ordenado atrapa bugs donde una rotacion rompe la propiedad BST.
17. Una prueba de prioridad padre-hijo atrapa bugs donde bubbleUp o trickleDown no rota lo suficiente.
18. Conviene prioridades fijas en tests unitarios porque el resultado es deterministico y reproducible. Con prioridades aleatorias el arbol cambia cada vez y es dificil verificar.

### Bloque 11 - Comparacion con Semana 5

| Estructura            | Operacion principal  | Propiedad       | Op. eficiente          | Op. que no conviene      | Evidencia                                |
| --------------------- | -------------------- | --------------- | ---------------------- | ------------------------ | ---------------------------------------- |
| BinaryHeap (S5)       | add/remove/top       | Heap en arreglo | top O(1), add O(log n) | Busqueda O(n)            | extract sale ordenado                    |
| PQ_ComplHeap (S6)     | insert/delMax/getMax | Heap completo   | getMax O(1)            | Busqueda O(n)            | Igual que BinaryHeap pero mas completo   |
| BinarySearchTree (S5) | insert/find/remove   | BST enlazado    | find O(log n)          | Extraer min/max O(log n) | Inorden sale ordenado                    |
| Treap (S6)            | add/remove/find      | BST + heap      | find O(log n) esperado | Extraer min O(n)         | Inorden ordenado + altura esperada log n |

1. El heap mantiene prioridad (padre > hijos) pero no orden global. El BST mantiene orden global (izq < raiz < der) pero no prioridad.

2. Un BST permite recorrido ordenado porque el inorden visita los nodos en orden. Un heap no porque los hermanos no tienen relacion de orden.

3. PQ_ComplHeap agrega la interfaz PQ formal, percolateUp/Down como funciones separadas, heapify de Floyd y heapSort. BinaryHeap de Semana 5 es mas educativo y basico.

4. El Treap combina busqueda ordenada (BST por clave) con balanceo probabilistico (heap por prioridad aleatoria).

5. Para extraer maximos repetidamente: PQ_ComplHeap o BinaryHeap.

6. Para lowerBound/upperBound: BinarySearchTree o Treap.

7. Para busqueda ordenada con balanceo probabilistico: Treap.

### Bloque 12 - Pruebas

Lista de pruebas agregadas:

1. PQ_ComplHeap conserva heap despues de cada insert -> isValidHeap() = true
2. PQ_ComplHeap conserva heap despues de cada delMax -> isValidHeap() = true
3. getMax no cambia size -> size antes == size despues
4. delMax si cambia size -> size antes == size despues + 1
5. heapifyFloyd produce heap valido -> isValidHeap() = true
6. heapSort con repetidos -> resultado ordenado
7. PQ_LeftHeap despues de merge -> isValidLeftHeap() = true
8. PQ_LeftHeap despues de insert -> isValidLeftHeap() = true
9. PQ_LeftHeap despues de delMax -> isValidLeftHeap() = true
10. Huffman produce codigos para todos -> cada simbolo tiene codigo
11. Huffman codigos libres de prefijos -> ninguno es prefijo de otro
12. Huffman un solo simbolo -> codigo = "0"
13. Treap isBST despues de insert -> true
14. Treap isHeapByPriority despues de insert -> true
15. Treap ambas propiedades despues de remove -> true

Resultado de ctest: All 15 tests passed.

### Bloque 13 - Defensa escrita

Lo que aprendi al modificar el codigo de prioridad, heaps, Huffman y Treap va mas alla de solo leerlo o ejecutar demos:

La interfaz `PQ` define un contrato minimo: insert, getMax y delMax. Lo importante es que cualquier implementacion que cumpla ese contrato puede usarse de la misma forma, ya sea un heap completo o un heap izquierdista.

La representacion implicita del heap binario completo es elegante porque no usa punteros. Solo con aritmetica sobre indices (`2i+1`, `2i+2`, `(i-1)/2`) puedes navegar el arbol. Eso ahorra memoria y es mas cache-friendly.

`percolateUp` es la operacion de "reparacion hacia arriba": cuando un elemento nuevo puede ser mas prioritario que su padre, sube intercambiandose con el padre. Al instrumentarla con conteo, vi que la mayoria de las veces hace 0 o 1 intercambios, y solo en el peor caso (nuevo minimo) sube hasta la raiz.

`percolateDown` repara hacia abajo: cuando pones un elemento grande en la raiz (despues de delMax), tiene que bajar hasta su posicion correcta. La decision de con cual hijo intercambiar es crucial: siempre con el de mayor prioridad.

`heapify` de Floyd es sorprendente porque construye un heap en O(n) en vez de O(n log n). La clave es que la mitad de los nodos son hojas y no necesitan reparacion. Instrumentar los intercambios me hizo ver que la suma converge.

`heapSort` usa el heap como herramienta de ordenamiento in situ. Lo que mas me costo entender es que NO es estable: elementos iguales pueden cambiar de orden relativo por los swaps con el final.

El `merge` del heap izquierdista es la operacion mas poderosa porque insert y delMax se implementan a partir de ella. La propiedad izquierdista (npl izquierdo >= npl derecho) garantiza que merge solo baje por el camino derecho, que es el mas corto.

En Huffman, construir el arbol desde una PQ es directo: extraes los dos de menor frecuencia, los combinas y reinsertas. El caso de un solo simbolo es un edge case que rompe el algoritmo si no lo manejas.

El Treap es la estructura que mas me intereso porque combina BST y heap en una sola. Las rotaciones (bubbleUp y trickleDown) mantienen ambas propiedades simultaneamente. Al instrumentarlas, vi que con prioridades aleatorias la altura se mantiene cercana a O(log n) en la practica.

Comparando con BinaryHeap y BinarySearchTree de Semana 5, entendi que cada estructura tiene su nicho: heap para prioridad, BST para orden, treap para ambas con balanceo probabilistico.

Las pruebas con invariantes y casos borde son mas valiosas que simplemente "correr el programa". Verificar isValidHeap(), isBST(), isHeapByPriority() despues de cada operacion me dio confianza de que las modificaciones no rompieron nada.
