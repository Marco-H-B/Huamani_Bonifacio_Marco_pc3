## Actividad 5 - CC232

### Estudiante

- Nombre: Huamani Bonifacio Marco Antonio
- Código: 20232741D

### Bloque 1 - Nucleo conceptual

1. **Arbol enlazado vs implicito en arreglo**: Un arbol enlazado usa nodos con punteros a sus hijos y padre, cada nodo esta en una posicion de memoria diferente. Un arbol implicito en arreglo guarda los nodos en un vector y calcula las posiciones de los hijos con formulas matematicas (hijo izq = 2i+1, hijo der = 2i+2). El enlazado es mas flexible para inserciones y eliminaciones, el implicito es mas compacto y rapido para acceder.

2. **Que guarda un BinNode**: Guarda el dato (la clave), un puntero al padre (`parent`), un puntero al hijo izquierdo (`left`), un puntero al hijo derecho (`right`), y la altura del nodo. Con eso puedes navegar hacia arriba y hacia abajo por el arbol.

3. **Por que parent permite succ(), pred() y actualizar alturas**: Porque con el puntero al padre puedes subir por el arbol. Para encontrar el sucesor inorden a veces necesitas subir hasta encontrar un ancestro donde giraste a la izquierda. Para actualizar alturas, despues de insertar o borrar un nodo subes actualizando las alturas de cada ancestro hasta la raiz.

4. **Responsabilidad de BinTree vs BinNode**: BinTree es el "dueño" del arbol: guarda la raiz, el tamaño total y se encarga de crear/destruir nodos, adjuntar subarboles y desglosar ramas. BinNode es solo un nodo individual que conoce a sus vecinos (padre e hijos).

5. **Que agrega BinaryTree sobre BinTree**: BinaryTree agrega recorridos (inorden, preorden, postorden, por niveles), iteradores para recorrer el arbol en orden, profundidad, altura, tamaño de subarbol y una representacion ASCII para imprimir el arbol. Es la capa de "navegacion y consulta".

6. **Propiedad adicional de BST**: Un BST tiene la propiedad de que para cada nodo, todos los valores en su subarbol izquierdo son menores y todos los del subarbol derecho son mayores. Esto permite hacer busquedas eficientes en O(log n) si el arbol esta balanceado.

7. **Propiedad adicional del BinaryHeap minimo**: Un heap minimo tiene la propiedad de que cada padre es menor o igual que sus hijos. Esto garantiza que el minimo siempre esta en la raiz y se puede acceder en O(1).

8. **Comparacion propiedad BST vs propiedad heap**: El BST ordena globalmente: puedes recorrer todo el arbol en orden. El heap solo garantiza una relacion local padre-hijo: el padre es mayor (o menor) que sus hijos, pero los hermanos no tienen orden entre si. Por eso el heap es bueno para sacar el min/max pero no para recorrer en orden.

9. **Inorden de BST produce secuencia ordenada**: Porque el recorrido inorden visita primero el subarbol izquierdo (todos menores), luego la raiz, luego el subarbol derecho (todos mayores). Si aplicas eso recursivamente, los elementos salen en orden creciente.

10. **Heap no permite recorrer en orden**: Porque la relacion de orden solo es padre-hijo, no entre hermanos. El hijo izquierdo puede ser mayor o menor que el derecho. Para recorrer en orden tendrias que extraer repetidamente el minimo, lo que destruye el heap.

### Bloque 2 - Navegacion, altura, profundidad y tamaño

1. **Funciones de BinNode**: `hasLeft()` dice si tiene hijo izquierdo, `hasRight()` si tiene hijo derecho, `isRoot()` si no tiene padre, `isLeaf()` si no tiene ningun hijo, `isLeftChild()` si es el hijo izquierdo de su padre, `isRightChild()` si es el hijo derecho.

2. **succ() bajando al subarbol derecho**: Si el nodo tiene hijo derecho, el sucesor inorden es el nodo mas a la izquierda del subarbol derecho. Bajas a la derecha una vez y luego bajas a la izquierda todo lo que puedas.

3. **succ() subiendo por ancestros**: Si el nodo NO tiene hijo derecho, tienes que subir por los padres. Subes mientras seas hijo derecho de tu padre. Cuando encuentras un ancestro donde eres hijo izquierdo, ese ancestro es tu sucesor.

4. **pred() simetrico**: Si tiene hijo izquierdo, bajas a la izquierda y luego a la derecha todo lo que puedas. Si no tiene hijo izquierdo, subes mientras seas hijo izquierdo y cuando encuentras donde eres hijo derecho, ese ancestro es tu predecesor.

5. **Dibujo de arbol con sucesor y predecesor**:

```
        50
       /  \
      30    70
     / \   / \
    20  40 60  80
```

- Nodo 30: pred=20, succ=40
- Nodo 50: pred=40, succ=60
- Nodo 70: pred=60, succ=80

6. **depth(u)**: Calcula la distancia desde la raiz hasta el nodo u. Se implementa subiendo por los punteros parent y contando cuantos pasos das hasta llegar a la raiz.

7. **height(u)**: Calcula la distancia mas larga desde el nodo u hasta una hoja. Se implementa bajando recursivamente: la altura es 1 + max(altura del hijo izq, altura del hijo der).

8. **subtreeSize(u)**: Cuenta cuantos nodos hay en el subarbol que cuelga de u (incluyendo a u). Es 1 + size(izq) + size(der).

9. **Demostracion depth(u) + height(u) <= height(T)**: depth(u) es la distancia de la raiz a u. height(u) es la distancia de u a la hoja mas lejana de su subarbol. La altura del arbol height(T) es la distancia de la raiz a la hoja mas lejana de todo el arbol. Como el camino de la raiz a u (depth) + el camino de u a su hoja mas lejana (height) es un camino de la raiz a alguna hoja, y height(T) es el camino mas largo posible, entonces depth(u) + height(u) <= height(T).

10. **Igualdad**: Se alcanza la igualdad cuando u esta en el camino mas largo del arbol (desde la raiz hasta la hoja mas profunda). Es decir, u es un ancestro de la hoja que determina la altura del arbol.

### Bloque 3 - Recorridos y trazado guiado

| Recorrido            | Version   | Estructura auxiliar | Secuencia (arbol de ejemplo) | Correctitud y costo       |
| -------------------- | --------- | ------------------- | ---------------------------- | ------------------------- |
| Preorden recursivo   | recursiva | Call stack          | 50,30,20,40,70,60,80         | O(n) tiempo, O(h) espacio |
| Preorden iterativo   | iterativa | Stack explicita     | 50,30,20,40,70,60,80         | O(n) tiempo, O(h) espacio |
| Inorden recursivo    | recursiva | Call stack          | 20,30,40,50,60,70,80         | O(n) tiempo, O(h) espacio |
| Inorden iterativo #1 | stack     | Stack explicita     | 20,30,40,50,60,70,80         | O(n), baja por izquierda  |
| Inorden iterativo #2 | succ()    | Puntero parent      | 20,30,40,50,60,70,80         | O(n), usa sucesor         |
| Inorden iterativo #3 | directo   | Stack + flag        | 20,30,40,50,60,70,80         | O(n)                      |
| Postorden recursivo  | recursiva | Call stack          | 20,40,30,60,80,70,50         | O(n) tiempo               |
| Postorden iterativo  | iterativa | Stack explicita     | 20,40,30,60,80,70,50         | O(n), mas complejo        |
| Por niveles          | iterativo | Queue               | 50,30,70,20,40,60,80         | O(n), ancho del nivel     |

1. Visitar en preorden significa procesar el nodo antes de visitar sus hijos. Raiz primero, luego izquierda, luego derecha.

2. Visitar en inorden es procesar izquierda primero, luego raiz, luego derecha. En un BST da los elementos ordenados.

3. Visitar en postorden es procesar los hijos primero y la raiz al final. Util para liberar memoria (borras hijos antes que padre).

4. Visitar por niveles es recorrer fila por fila, de arriba a abajo y de izquierda a derecha. Usas una cola.

5. Los recorridos recursivos son O(n) porque cada nodo se visita exactamente una vez.

6. Las versiones iterativas tambien son O(n) porque cada nodo entra y sale de la pila exactamente una vez.

7. En un arbol balanceado, la memoria auxiliar del recorrido recursivo es O(log n) porque la profundidad maxima de la pila de llamadas es la altura.

8. En un arbol degenerado (tipo lista), la memoria es O(n) porque la altura puede ser n.

9. La pila explicita y la pila de llamadas hacen esencialmente lo mismo, pero con la explicita puedes ver el contenido, pausar, etc. La de llamadas es automatica pero opaca.

10. La cola del recorrido por niveles crece segun el ancho del arbol. En un arbol completo el ultimo nivel tiene n/2 nodos, asi que la cola puede tener hasta n/2 elementos. En un arbol degenerado, el ancho maximo es 1.

### Bloque 4 - Demos

| Archivo                     | Salida importante                             | Idea estructural            | Argumento de costo/diseño        |
| --------------------------- | --------------------------------------------- | --------------------------- | -------------------------------- |
| demo_binary_tree.cpp        | Recorridos pre/in/post/niveles                | Arbol enlazado con punteros | O(n) por recorrido, O(h) espacio |
| demo_bst.cpp                | Inorden sale ordenado, find/lower/upper       | BST con propiedad de orden  | O(log n) busqueda si balanceado  |
| demo_heap.cpp               | Minimo siempre en raiz, extract sale ordenado | Heap implicito en arreglo   | O(log n) insert/remove, O(1) top |
| demo_capitulo5_panorama.cpp | Comparacion de las tres estructuras           | Vision general              | Cada una para un proposito       |

1. La salida del recorrido inorden muestra los valores en orden creciente. Si comparas con preorden y postorden, puedes verificar que cada recorrido visita los nodos en el orden correcto.

2. La parte donde llamas succ() y pred() desde un nodo y la salida coincide con el orden inorden. Si succ(30)=40 y en inorden 40 viene justo despues de 30, esta correcto.

3. El ascii art permite ver la forma del arbol: si esta balanceado, si esta degenerado, que nodo es raiz, etc. Es util para depurar y para sustentar.

4. Si recorres el BST en inorden y la salida esta ordenada, eso es evidencia directa de que la propiedad BST se mantiene.

5. `find` busca un nodo cuya clave es >= x (como lower_bound), `findEQ` busca exactamente x, `lowerBound` da el primer elemento >= x, `upperBound` da el primer elemento > x. Se distinguen mejor cuando buscas un valor que no existe en el arbol.

6. Despues de insertar varios elementos, el top del heap siempre es el minimo. Eso demuestra que la propiedad de min-heap se mantiene.

7. Construir con add() insertas uno por uno y cada insercion sube con bubbleUp. Con heapify() copias todo el arreglo y reparas de abajo hacia arriba. Los arreglos finales pueden ser diferentes pero ambos son heaps validos.

8. La comparacion resume que el arbol enlazado es la base, el BST agrega busqueda ordenada y el heap agrega acceso rapido al extremo (min o max).

### Bloque 5 - Pruebas e invariantes

1. La prueba publica valida insert, find, findEQ, lowerBound, upperBound, remove y que el inorden sea correcto.

2. Se inserta un valor que ya existe y se verifica que el tamaño no cambie. El BST no acepta duplicados.

3. Se compara que el inorden recursivo de el mismo resultado que las tres versiones iterativas. Si todas coinciden, los recorridos estan bien implementados.

4. Se espera que `findEQ(8)` devuelva un puntero al nodo con clave 8 (o nullptr si no existe).

5. `lowerBound(9)` devuelve el primer nodo con clave >= 9, y `upperBound(8)` devuelve el primer nodo con clave > 8. Si 9 no existe, lowerBound(9) da el siguiente mayor.

6. `isBST()` verifica que para cada nodo, todos los de la izquierda sean menores y todos los de la derecha sean mayores.

7. Despues de remove(), se verifica que el inorden siga ordenado, que el tamaño se reduzca en 1 y que isBST() siga siendo true.

8. `checkParentLinks()` verifica que si un nodo apunta a un hijo, ese hijo apunte de vuelta al padre correcto. Detecta inconsistencias en los punteros.

9. La prueba publica valida add, top, remove y que extraer repetidamente de el resultado en orden.

10. Si extraes repetidamente el minimo de un min-heap, la secuencia tiene que salir ordenada de menor a mayor. Eso demuestra que la propiedad de heap funciona correctamente.

11. Se valida attachAsRC, secede y removeSubtree. Que despues de adjuntar un subarbol los padres e hijos sean correctos, que secede separe sin destruir, y que removeSubtree libere memoria.

12. Las pruebas internas agregan rotaciones (que conserven BST), bubbleUp y trickleDown individuales, profundidad y altura de nodos especificos, y sucesor/predecesor de varios nodos.

13. Pasar las pruebas publicas demuestra que las operaciones dan el resultado correcto para esos casos especificos.

14. No demuestra que funcione para TODOS los casos. Tampoco demuestra que la complejidad sea la esperada ni que los invariantes se mantengan en general.

15. Porque las pruebas solo verifican "funciona para estos inputs". Los invariantes explican POR QUE funciona en general y la complejidad dice QUE TAN RAPIDO funciona. Sin esos tres aspectos la defensa esta incompleta.

### Bloque 6 - Lectura cercana de codigo

1. Los invariantes de BinNode son: si un nodo tiene padre, el padre debe apuntar de vuelta a el como hijo izquierdo o derecho. Si tiene hijo izquierdo, ese hijo debe tener como padre a este nodo. Igual con el derecho.

2. insertAsLC/insertAsRC rechazan si el hijo ya existe porque sobreescribirian un subarbol existente. Eso perderia nodos y romperia la estructura.

3. `size()` de BinNode recorre recursivamente: 1 + size(izq) + size(der). Visita cada nodo del subarbol una vez.

4. `leftmost()` baja por los hijos izquierdos hasta llegar a un nodo sin hijo izquierdo. `rightmost()` hace lo mismo pero por la derecha.

5. `succ()`: Si tiene hijo derecho, baja a la derecha y luego al leftmost de ese subarbol. Si no tiene hijo derecho, sube por los padres mientras sea hijo derecho. Cuando encuentras un ancestro donde eres hijo izquierdo, ese ancestro es el sucesor.

6. `pred()`: Simetrico. Si tiene hijo izquierdo, baja a la izquierda y luego al rightmost. Si no, sube mientras sea hijo izquierdo y el primer ancestro donde eres hijo derecho es tu predecesor.

7. `root_` es un puntero a la raiz del arbol y `size_` guarda el numero total de nodos. BinTree los mantiene actualizados.

8. `updateHeight(Node*)` recalcula la altura de un nodo como 1 + max(altura izq, altura der).

9. `updateHeightAbove(Node*)` llama updateHeight desde ese nodo hacia arriba, subiendo por los padres hasta la raiz. Es necesario porque al insertar o borrar un nodo, las alturas de todos sus ancestros pueden cambiar.

10. `attachAsLC/attachAsRC` toman un subarbol de otro arbol y lo enganchan como hijo izquierdo/derecho. Actualizan los punteros parent y actualizan alturas. El arbol fuente queda vacio.

11. `removeSubtree` elimina un subarbol y libera toda la memoria. `secede` despega un subarbol pero no lo destruye, lo convierte en un arbol independiente.

12. Porque los nodos desprendidos por secede siguen siendo validos y pueden usarse como un arbol separado. Destruirlos seria perder informacion util.

13. Porque removeSubtree se usa cuando realmente quieres borrar esos nodos. Si no liberas la memoria, tienes un memory leak.

14. `checkParentLinks()` verifica la consistencia bidireccional: para cada nodo, si dice que tiene hijo izquierdo, ese hijo debe apuntar de vuelta al padre correcto. Si encuentra una inconsistencia, significa que alguna operacion rompio los punteros.

15. `firstNode` devuelve el nodo mas a la izquierda (el menor en inorden). `lastNode` el mas a la derecha. `nextNode` devuelve succ() y `prevNode` devuelve pred().

16. Porque succ() siempre da el siguiente nodo en el orden inorden. Si empiezas en firstNode y llamas succ repetidamente, recorres todos los nodos en orden creciente.

17. `asciiArt()` imprime el arbol de forma visual en texto. Permite ver rapidamente la estructura, verificar si esta balanceado, donde estan los hijos, etc.

### Bloque 7 - BST

1. La propiedad BST dice que para todo nodo x: todos los nodos en el subarbol izquierdo tienen clave < x.clave, y todos los del subarbol derecho tienen clave > x.clave.

2. Porque el inorden visita izquierda (menores), raiz, derecha (mayores). Si aplicas eso recursivamente desde la raiz, los elementos salen en orden creciente.

3. `find` devuelve el nodo con clave >= x (primer candidato). `findEQ` devuelve el nodo solo si la clave es exactamente x. `lowerBound` devuelve el primer nodo >= x. `upperBound` devuelve el primer nodo > x.

4. Porque `findEQ(x)` falla si x no esta en el arbol (devuelve nullptr). Pero `lowerBound(x)` devuelve el siguiente mayor, asi que no falla mientras haya algun nodo >= x.

5. BST construido insertando 7,3,10,1,5,8,12,4,6:

```
        7
       / \
      3    10
     / \   / \
    1   5  8  12
       / \
      4   6
```

6. Inorden: 1,3,4,5,6,7,8,10,12. Preorden: 7,3,1,5,4,6,10,8,12. Postorden: 1,4,6,5,3,8,12,10,7. Por niveles: 7,3,10,1,5,8,12,4,6.

7. `lowerBound(9)`: Empieza en 7, 9>7 va a la derecha. En 10, 9<10 guarda 10 como candidato y va a la izquierda. En 8, 9>8 va a la derecha, no hay hijo. Devuelve 10.
   `upperBound(8)`: Busca el primer elemento > 8. Empieza en 7, 8>7 va a la derecha. En 10, 8<10 guarda 10 y va izquierda. En 8, 8=8, busca > 8, va a la derecha, no hay. Devuelve 10.

8. Eliminacion de hoja: simplemente se borra y se actualiza el padre. Un hijo: el hijo reemplaza al nodo eliminado. Dos hijos: se busca el sucesor inorden, se intercambia con el nodo a eliminar, y luego se borra el sucesor (que tiene a lo mas un hijo).

9. `splice` es la operacion que saca un nodo del arbol reconectando su unico hijo (si tiene) con su padre. Se usa cuando el nodo a eliminar tiene 0 o 1 hijo.

10. Despues de eliminar, deben seguir siendo ciertos: propiedad BST (inorden ordenado), consistencia de punteros parent, y tamaño correcto.

11. `remove(3)` en las pruebas: si sacas el 3, el subarbol izquierdo (1,5,4,6) se reorganiza. El inorden debe seguir siendo 1,4,5,6,7,8,10,12 (ordenado sin el 3).

12. `rotateLeft` toma un nodo x y sube a su hijo derecho y. x pasa a ser hijo izquierdo de y, y el hijo izquierdo de y pasa a ser hijo derecho de x.

13. `rotateRight` es simetrico: toma un nodo y sube a su hijo izquierdo x. y pasa a ser hijo derecho de x, y el hijo derecho de x pasa a ser hijo izquierdo de y.

14. La rotacion preserva BST porque solo mueve nodos dentro del rango permitido. El subarbol que se "transfiere" entre nodos siempre esta en el rango correcto (mayor que uno y menor que el otro).

15. Construir un BST balanceado desde un arreglo ordenado te da un arbol de altura minima O(log n). Se toma el elemento del medio como raiz y se aplica recursivamente a cada mitad.

16. En un BST balanceado la busqueda es O(log n) porque la altura es log n. En un BST degenerado (tipo lista) la busqueda es O(n) porque la altura es n.

### Bloque 8 - Heap

1. Porque un heap binario completo llena los niveles de izquierda a derecha, sin huecos. Eso permite mapear cada nodo a una posicion del vector sin necesidad de punteros.

2. Si la raiz esta en indice 0, el hijo izquierdo del nodo i esta en 2i+1 y el derecho en 2i+2. Esto se deduce del hecho de que en cada nivel hay exactamente el doble de nodos que en el anterior. El padre de i esta en (i-1)/2 (division entera).

3. Min-heap: para todo nodo i (excepto la raiz), el valor de i es mayor o igual que el valor de su padre. Equivalentemente: parent(i) <= i para todo i.

4. `top()` devuelve el minimo porque la propiedad de min-heap garantiza que la raiz es el menor elemento. No necesitas buscar.

5. `bubbleUp(i)`: Compara el nodo i con su padre. Si i es menor que su padre, los intercambia y repite con la nueva posicion de i (ahora esta en la posicion del padre). Se detiene cuando i ya es mayor o igual que su padre, o cuando llega a la raiz.

6. `trickleDown(i)`: Compara el nodo i con sus hijos. Elige al hijo menor. Si i es mayor que ese hijo, los intercambia y repite. Se detiene cuando i es menor que ambos hijos o cuando llega a una hoja.

7. Porque despues de sacar la raiz (el minimo), necesitas llenar ese hueco. Mueves el ultimo elemento a la raiz para mantener la propiedad de completitud, pero eso rompe la propiedad de orden, asi que aplicas trickleDown para reparar.

8. `isHeap()` verifica que para cada nodo i, el valor de i no sea mayor (en max-heap) o menor (en min-heap) que los valores de sus hijos. Si algun nodo viola esto, el heap es invalido.

9. Insertar n elementos uno por uno: cada insercion puede subir hasta la altura actual del heap. El i-esimo insert puede costar O(log i). Sumando todo da O(n log n). Heapify de Floyd: procesa los nodos de abajo hacia arriba, cada nodo baja a lo mucho su altura. Sumando da O(n).

10. Porque el i-esimo elemento se inserta en un heap de tamaño i, y bubbleUp puede hacer hasta log(i) intercambios. Sumando log(1) + log(2) + ... + log(n) = O(n log n).

11. Floyd hace trickleDown desde la mitad del arreglo hacia atras. Las hojas (mitad de los nodos) no necesitan bajar nada. Los nodos a una altura h necesitan bajar a lo mucho h niveles. Sumando: la mayoria de los nodos son hojas (bajo costo) y pocos nodos estan arriba (alto costo). La suma telescopica da O(n).

12. Heap con {7,3,10,1,5,8,2}. Heapify da: [1,3,2,7,5,8,10] (min-heap). Extracciones: 1->3->2->5->7->8->10. Sale ordenado porque siempre sacas el minimo.

13. El heap conviene cuando necesitas consultar/extraer el minimo (o maximo) repetidamente: O(1) consultar, O(log n) extraer. El BST conviene cuando necesitas busquedas ordenadas (find, lowerBound, upperBound) y recorrido inorden: O(log n) busqueda, O(n) recorrido.

### Bloque 9 - Cierre comparativo

Cuando pasamos de listas, pilas y colas a arboles, heaps y BSTs, cambian varias cosas importantes:

- **Representacion enlazada**: Los arboles usan nodos con punteros a padre e hijos. Esto permite insertar y eliminar nodos en cualquier posicion sin mover todo lo demas, a diferencia de las listas basadas en arreglo.

- **Representacion implicita**: El heap binario demuestra que no siempre necesitas punteros. Si la estructura es completa y compacta, puedes usar un arreglo y formulas matematicas para navegar. Es mas eficiente en memoria y cache.

- **Propiedad estructural vs propiedad de orden**: La propiedad estructural es la forma del arbol (completo, enlazado, etc.). La propiedad de orden es la regla sobre los valores (BST: izquierda < raiz < derecha, heap: padre <= hijos). Son independientes: puedes tener un arbol completo que no sea BST ni heap.

- **Recorridos como conversion arbol a secuencia**: Un recorrido (pre/in/post/niveles) convierte la estructura bidimensional del arbol en una secuencia lineal. Cada recorrido da un orden diferente, y el inorden es especialmente util en BSTs porque produce la secuencia ordenada.

- **Alturas y enlaces parent**: Mantener la altura actualizada en cada nodo permite detectar desbalances. El enlace parent permite subir por el arbol para actualizar alturas y encontrar sucesores/predecesores sin necesidad de buscar desde la raiz.

- **BST y busqueda ordenada**: El BST permite busquedas, insercion y eliminacion en O(log n) si esta balanceado. El inorden da los elementos ordenados. Es la estructura natural para conjuntos y diccionarios ordenados.

- **Heap, prioridad y costos**: El heap es la estructura natural para colas de prioridad. add es O(log n), remove es O(log n), top es O(1). Heapify de Floyd construye en O(n). Es mas eficiente que un BST cuando solo necesitas el extremo.

- **Evidencia para defender correctitud**: La evidencia mas solida combina pruebas automatizadas (que verifican resultados), demostraciones (que muestran el comportamiento visualmente), invariantes (que explican por que funciona en general), trazados manuales (que muestran paso a paso) y analisis de complejidad (que dice que tan rapido es).

### Autoevaluacion breve

- Que puedo defender con seguridad: la propiedad BST, como funciona inorden, y la diferencia entre heap y BST.
- Que todavia confundo: los detalles de las tres versiones iterativas del inorden, me cuesta diferenciarlas.
- Que evidencia usaria en una sustentacion: el recorrido inorden del BST saliendo ordenado y las extracciones del heap saliendo ordenadas.
- Que parte del codigo me parece mas importante revisar otra vez: succ() y pred(), porque los uso en la PC3 con el Treap.
