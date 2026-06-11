# Respuestas Obligatorias - Práctica Calificada 3

## Preguntas Comunes Obligatorias

**1. ¿Cuál es el problema exacto asignado?**
El problema es ORDERSET de SPOJ. Pide implementar un conjunto (Set) dinámico que soporte cuatro operaciones: Insertar un número, Eliminar un número, consultar el K-ésimo elemento más pequeño, y contar cuántos elementos son menores a un número 'X' dado.

**2. ¿Qué recibe la entrada y qué produce la salida?**
Recibe un entero `Q` (número de consultas), seguido de `Q` líneas con una letra (`I`, `D`, `K`, `C`) y un número `x`. Produce como salida la respuesta numérica para las operaciones `K` y `C`, o imprime `invalid` si se pide un elemento `K` que no existe (ej. K mayor al tamaño del árbol).

**3. ¿Cuál es la restricción que vuelve insuficiente una solución ingenua?**
El límite de operaciones es de 200,000 consultas (`Q = 200,000`) y el tiempo máximo en SPOJ suele ser estricto (1 segundo). Una solución lenta daría "Time Limit Exceeded" (TLE).

**4. ¿Cuál sería la solución ingenua y cuál es su complejidad?**
Usar un `std::vector` en C++, y por cada `K` ordenar el arreglo y buscar por índice, o recorrer todo para contar menores. La inserción y el ordenamiento tomarían `O(N)` o `O(N log N)` en el peor caso por cada consulta, haciendo que la complejidad total sea `O(Q * N)`, inaceptable para 200,000 operaciones.

**5. ¿Qué estructura de datos elegiste?**
Implementé un **Treap** (Mezcla de Tree y Heap) aumentado con el campo de tamaño de subárbol (`tam`).

**6. ¿Qué estructura de la librería cc232 se parece más?**
Se basa firmemente en el concepto de `Treap` visto en la **Semana 6**, junto con el concepto de Árboles Aumentados y Búsqueda Ordenada (BST) de la **Semana 5**.

**7. ¿Qué operación domina el tiempo?**
Las operaciones núcleo `split` y `merge`. Tanto insertar, eliminar como buscar dependen directamente de la altura del árbol gestionada por estas dos funciones.

**8. ¿Qué invariante mantiene tu estructura?**
Mantiene dos invariantes clave: el invariante de **Arbol Binario de Búsqueda (BST)** (todo hijo izquierdo es menor, el derecho es mayor) y el invariante del **Max-Heap** (la prioridad aleatoria del nodo padre es siempre mayor a la de sus hijos).

**9. ¿Dónde se actualiza ese invariante en el código?**
En las funciones `split` y `merge`. Durante la recursividad, después de enlazar los hijos correspondientes, siempre se llama a la función auxiliar `actualizar(nodo)` para garantizar que el tamaño del subárbol (`tam`) no pierda consistencia.

**10. ¿Qué caso borde puede romper una solución superficial?**
Intentar eliminar un elemento de un árbol vacío, pedir el `K`-ésimo número con un `K` excesivamente grande, o pasar valores al límite de los enteros (`INT_MAX`, `INT_MIN`).

**11. ¿Cómo manejas duplicados, empates o elementos obsoletos?**
SPOJ exige que la estructura sea un Set (Conjunto). Por ende, en la función `insertar`, hago primero una llamada a `buscar(raiz, val)`. Si el elemento ya existe, retorno inmediatamente para no duplicar nodos.

**12. ¿Cuál es la complejidad temporal por operación?**
Gracias al auto-balanceo estadístico de las prioridades del Treap, cada una de las 4 operaciones se realiza en una altura proporcional a `log N`. Por ende, cada operación toma **O(log N)** amortizado.

**13. ¿Cuál es la complejidad total?**
Dado que hay `Q` operaciones, la complejidad total es **O(Q log N)**.

**14. ¿Cuál es la complejidad espacial?**
Es **O(N)**, donde `N` es la cantidad de elementos únicos insertados en el conjunto, ya que cada uno requiere un solo bloque de memoria (un `struct Nodo`).

**15. ¿Qué parte del código sería más fácil de romper?**
Si nos olvidamos de llamar a `actualizar(nodo)` al final de cada recursión de `split` y `merge`, los tamaños de los subárboles quedarían desactualizados y la operación de K-ésimo entregaría basura.

**16. ¿Qué alternativa de estructura existe y qué perderías con ella?**
Podríamos usar un Árbol Rojo-Negro (Red-Black Tree) o AVL. Si bien asegurarían altura estricta `O(log N)`, perdería muchísima simplicidad. El Treap se balancea naturalmente con la prioridad aleatoria sin tener que programar los tediosos casos de rotaciones dobles.

**17. ¿Qué prueba propia escribiste?**
Escribí `tests/test_brute_force.cpp`, que es un validador cruzado. Compara de manera aleatoria cientos de operaciones de mi Treap contra operaciones hechas en un `std::vector` (fuerza bruta), asegurando que ninguna de mis optimizaciones rompa la lógica. Además de un benchmark de rendimiento intensivo (`benchmark.cpp`).

**18. ¿Qué cambiaste durante el bloque sin cortes?**
_(Nota para el video: Aquí debes explicar el pequeño cambio que hagas en vivo. Por ejemplo: "Agregué una pequeña validación al inicio del main para imprimir logs extra de cada inserción" o "Añadí un nuevo assert para validar punteros")._

**19. ¿Cómo sabes que el cambio no rompió la solución?**
Porque después de realizar el cambio, recompilé el proyecto limpio y ejecuté mi batería de pruebas (con CTest) como el validador de fuerza bruta, que confirmó que el núcleo de la lógica sigue inalterado.

**20. ¿Qué demuestra que no es una solución de caja negra?**
Mi implementación directa del `struct Nodo` y cómo utilicé el campo `tam` para interactuar con `k` de manera recursiva (comparando `k` con `tamIzq`). No usé librerías opacas oscuras como el `<ext/pb_ds/assoc_container.hpp>` de GNU C++ o similares.

---

## Preguntas y Retos Específicos (Problema 12 - SPOJ ORDERSET)

**1. ¿Qué significa rank(x)?**
Para nuestro problema (que equivale a la operación `C`), significa contar cuántos elementos presentes en la estructura son estrictamente menores que el valor 'X'.

**2. ¿Cómo se implementa kth sin recorrer todo el árbol?**
Aprovechando el campo `tam` (tamaño del subárbol). Durante la recursividad, calculo cuántos nodos hay en la izquierda (`tamIzq = obtenerTam(nodo->izq)`).

- Si `k <= tamIzq`, bajo por la izquierda.
- Si `k == tamIzq + 1`, estoy exactamente en el nodo objetivo y devuelvo su clave.
- Si `k` es mayor, bajo por la derecha, pero actualizando mi meta: `k = k - tamIzq - 1` para descontar los nodos que ya superé.

**3. ¿Qué cambia si hay elementos repetidos?**
Como el problema nos dice que es un conjunto estricto, no permitimos duplicados. Si los permitiéramos, tendríamos que usar un multiset y modificar el Treap, ya sea permitiendo repetidos en las hojas con prioridades distintas, o (mejor aún) añadiendo un campo adicional de "frecuencia" o "contador" al nodo para no malgastar memoria en punteros repetidos.
