## Actividad 4-CC232

### Estudiante

- Nombre completo: Huamani Bonifacio Marco Antonio
- Código: 20232741D

#### Bloque 1 (respuestas)

1. **Diferencia LIFO vs FIFO**: LIFO es cuando lo ultimo que metes es lo primero que sacas, como una pila de platos: pones uno encima y sacas el de arriba. FIFO es lo contrario, como una fila del banco: el primero que llega es el primero que atienden. En el codigo, la pila usa `push` y `pop` por el mismo lado (el final del vector), mientras que la cola mete por atras y saca por delante.

2. **Por que Stack resuelve "lo ultimo pendiente"**: Porque cuando tienes un problema donde vas avanzando y te quedas con cosas por resolver, lo natural es que la mas reciente sea la que atiendes primero. Por ejemplo, cuando evaluas parentesis: el ultimo parentesis que abriste es el primero que deberias cerrar. La pila hace exactamente eso: te da acceso rapido al ultimo elemento que guardaste.

3. **Por que Queue modela procesos de espera**: Porque en la vida real la gente hace fila y se atiende en orden de llegada. Si tienes clientes que llegan a un banco, el primero que llego es el primero que se atiende. La cola respeta ese orden: encolas al final y desencolas al inicio.

4. **Reemplazar recursion por estructura explicita**: Cuando haces recursion, la computadora usa una pila interna (el call stack) para guardar cada llamada pendiente. Si en vez de eso usas un Stack propio, tu controlas que se guarda y cuando se saca. La idea es la misma pero tu tienes el control y no dependes de la pila del sistema (que tiene limite).

5. **Informacion minima para reconstruir solucion parcial**: Necesitas guardar lo suficiente para saber "donde me quede" y "que ya probe". Por ejemplo en N-Reinas guardas en que fila y columna pusiste cada reina. Con eso puedes saber si la siguiente reina entra en conflicto y si necesitas retroceder.

6. **Comparacion de conversion de base recursiva e iterativa**: Ambas hacen lo mismo: dividen entre la base, sacan el residuo y lo guardan en una pila. La diferencia es que la recursiva usa las llamadas del sistema como pila (cada llamada guarda el residuo), mientras que la iterativa usa un ciclo while y una pila explicita. Al final ambas producen el mismo resultado porque el orden de los residuos se invierte al sacarlos de la pila.

7. **Verificacion iterativa de parentesis necesita almacenar aperturas**: Porque cuando ves un parentesis de cierre, necesitas saber cual fue el ultimo de apertura que no se ha cerrado todavia. Si no guardaras las aperturas, no podrias saber si el cierre corresponde al tipo correcto. La pila te dice justamente eso: el tope es la apertura mas reciente pendiente.

8. **Evaluador necesita dos pilas**: Una pila es para los operandos (numeros) y otra para los operadores. Necesitas las dos porque cuando llega un operador nuevo, tienes que comparar su prioridad con el operador del tope. Si el tope tiene mayor o igual prioridad, sacas ese operador, sacas dos operandos, calculas y apilas el resultado. Si usaras una sola pila mezclando numeros y operadores seria un desastre.

9. **N-Reinas y laberinto como backtracking**: En ambos casos tienes que probar opciones, y si una opcion no funciona, regresas al estado anterior y pruebas la siguiente. En N-Reinas pones una reina, si genera conflicto la quitas y pruebas la siguiente columna. En el laberinto avanzas por un camino, si llegas a un callejon sin salida regresas e intentas otro camino. La pila te permite recordar por donde pasaste para poder retroceder.

10. **Simulacion bancaria no se modela con pila**: Porque en un banco la gente se atiende en orden de llegada, no en orden inverso. Si usaras una pila, el ultimo cliente que llega seria el primero en ser atendido y eso no tiene sentido. La cola respeta el orden FIFO que es como funciona un banco real.

11. **Relacion estructura auxiliar, estado parcial y correctitud**: La estructura auxiliar (pila o cola) guarda el estado parcial del problema que estas resolviendo. Si la estructura mantiene bien ese estado, entonces tu algoritmo va a dar resultados correctos. Por ejemplo, si la pila de parentesis siempre tiene las aperturas pendientes en el orden correcto, entonces el algoritmo detecta bien los desbalances.

12. **Diferencia entre resolver un problema y simular un proceso**: Resolver un problema es encontrar LA respuesta (como las soluciones de N-Reinas). Simular un proceso es reproducir paso a paso como funciona algo en el tiempo (como el banco donde ves clientes llegando, haciendo fila y siendo atendidos). En la simulacion no buscas una respuesta unica, sino observar como se comporta el sistema.

#### Bloque 2 (tabla y respuestas)

| Archivo                     | Salida importante                                      | Estructura central                | Concepto que defiende        |
| --------------------------- | ------------------------------------------------------ | --------------------------------- | ---------------------------- |
| demo_stack_queue.cpp        | Orden de push/pop en stack vs enqueue/dequeue en queue | Stack y Queue                     | LIFO vs FIFO                 |
| demo_base_conversion.cpp    | Mismo resultado para recursiva e iterativa             | Stack como acumulador de residuos | Recursion vs iteracion       |
| demo_paren_rpn.cpp          | Deteccion de parentesis balanceados y evaluacion RPN   | Stack para aperturas y operadores | Verificacion y evaluacion    |
| demo_nqueens.cpp            | Numero de soluciones y checks por cada n               | Stack implicito (backtracking)    | Busqueda exhaustiva con poda |
| demo_maze.cpp               | Coordenadas del camino encontrado                      | Stack explicito de celdas         | Backtracking en laberinto    |
| demo_bank.cpp               | Estado de las colas en cada instante t                 | Queue por ventanilla              | Simulacion FIFO              |
| demo_capitulo4_panorama.cpp | Resumen de todas las estructuras de la semana          | Stack y Queue combinados          | Vision panoramica            |

1. La parte donde se hace push y luego pop vs enqueue y dequeue. Con el stack sacas los elementos en orden inverso, con la queue en el mismo orden. Eso deja clarisima la diferencia entre tope (el ultimo) y frente (el primero).

2. Se ve que ambas funciones (toBaseRecursive y toBaseIterative) devuelven exactamente la misma cadena para el mismo numero y base. Si ambas dan lo mismo, las dos son correctas.

3. Los parentesis balanceados son prerequisito para que la expresion se pueda convertir a RPN y evaluar. Si no estan balanceados, la RPN no tiene sentido y el valor final tampoco.

4. `solutions` es cuantas configuraciones validas de reinas se encontraron, y `checks` es cuantas veces se verifico si una reina entraba en conflicto. No miden lo mismo porque para encontrar una solucion necesitas hacer muchas verificaciones (la mayoria fallan).

5. La secuencia de coordenadas muestra el camino desde la entrada hasta la salida del laberinto. Si hay retroceso, se ve porque hay celdas marcadas como BACKTRACKED que no estan en el camino final.

6. Cada lista impresa muestra el estado de cada ventanilla en el instante t: cuantos clientes tiene en la cola, quienes estan esperando, etc. Es como una foto del banco en ese momento.

7. La parte final donde junta todo lo de la semana en un solo demo: pilas, colas, conversion, parentesis, reinas, laberinto y banco. Eso resume que una misma semana cubre tanto las estructuras basicas como sus aplicaciones.

#### Bloque 3 (respuestas)

1. La prueba publica del Stack valida push, pop, top, size y empty. Lo basico: que puedas meter y sacar elementos y que el tamaño sea correcto.

2. Para Queue valida enqueue, dequeue, front, size y empty. Igual, lo minimo para asegurar que la cola funciona.

3. Valida que toBaseRecursive y toBaseIterative den el mismo resultado para varios numeros y bases.

4. Valida que parentesis correctos dan true y parentesis incorrectos dan false, tanto para la version recursiva como la iterativa.

5. Valida que la evaluacion de expresiones de el valor correcto y que la RPN generada sea la esperada.

6. Valida que placeQueens(n) devuelva el numero correcto de soluciones para valores conocidos como n=4 (2 soluciones) y n=8 (92 soluciones).

7. Valida que el laberinto encuentre un camino valido desde la entrada hasta la salida.

8. Valida que bestWindow elija la ventanilla con la cola mas corta.

9. Las pruebas internas cubren casos mas extremos: pilas con muchos elementos, colas con operaciones intercaladas, expresiones con operadores unarios, laberintos sin salida, etc.

10. Porque las pruebas solo te dicen si funciona para esos casos especificos. No te dicen POR QUE funciona. Para eso necesitas entender los invariantes (por ejemplo: "la pila siempre tiene las aperturas pendientes en orden") y la complejidad (por ejemplo: "cada operacion es O(1) amortizado").

11. Un error conceptual que podria sobrevivir: si la conversion de base solo se prueba con base 10 y 2, podria haber un bug para base 16 que nunca se detecta. O si N-Reinas solo se prueba con n=4, un error en la poda podria pasar desapercibido para n mayor.

#### Bloque 4 (respuestas y experimentos 1-2)

1. El cociente dice cuanto falta por convertir, el residuo es el digito actual en la nueva base, y la pila guarda los residuos en orden inverso para que al sacarlos queden en el orden correcto (de mas significativo a menos significativo).

2. Porque los residuos se calculan del digito menos significativo al mas significativo. Al apilarlos y luego desapilarlos, se invierte el orden y quedan bien.

3. Con la recursion, el call stack del sistema guarda automaticamente cada residuo en cada llamada. Con la pila explicita, tu mismo haces push de cada residuo. El resultado es el mismo pero con la pila explicita tienes mas control y no te arriesgas a un stack overflow si el numero es muy grande.

4. `divideParentheses` intenta encontrar el punto medio donde se puede separar una cadena de parentesis en dos mitades balanceadas. Es como una idea de dividir y conquistar aplicada a la verificacion de parentesis.

5. La version recursiva mostrada solo maneja un tipo de parentesis `()`. Si aparecen `[]` o `{}`, no los reconoce. La version iterativa con pila si puede manejar multiples tipos porque compara el cierre con la apertura del tope.

6. Porque en la version iterativa, cada vez que ves un cierre, miras el tope de la pila. Si no coincide con el tipo de apertura que deberias cerrar, sabes inmediatamente que esta mal. No tienes que esperar al final.

7. Para conversion de base me parece mas natural la iterativa porque es un ciclo simple con while. Para parentesis me parece mas expresiva la recursiva cuando solo hay un tipo de delimitador, pero la iterativa es mas poderosa cuando hay varios tipos.

##### Experimento 1

| Numero | Base | Salida recursiva | Salida iterativa | ¿Coinciden? | Comentario         |
| ------ | ---- | ---------------- | ---------------- | ----------- | ------------------ |
| 255    | 2    | 11111111         | 11111111         | Si          | 8 bits, todos en 1 |
| 255    | 16   | FF               | FF               | Si          | Un byte completo   |
| 100    | 8    | 144              | 144              | Si          | 100 en octal       |
| 1000   | 3    | 1101001          | 1101001          | Si          | Base poco comun    |
| 42     | 5    | 132              | 132              | Si          | Numero arbitrario  |

##### Experimento 2

| Expresion        | Resultado recursivo | Resultado iterativo | ¿Coinciden? | Que explica                             |
| ---------------- | ------------------- | ------------------- | ----------- | --------------------------------------- |
| "" (vacia)       | true                | true                | Si          | Cadena vacia es valida                  |
| "hola"           | true                | true                | Si          | Sin parentesis es valida                |
| "(())"           | true                | true                | Si          | Anidamiento correcto                    |
| "(()"            | false               | false               | Si          | Falta un cierre                         |
| "([)]"           | -                   | false               | -           | Cruce incorrecto (iterativa lo detecta) |
| "{[()]}"         | -                   | true                | -           | Multiples tipos correctos               |
| "((((((()))))))" | true                | true                | Si          | Anidamiento profundo                    |
| ")(("            | false               | false               | Si          | Empieza con cierre                      |

#### Bloque 5 (respuestas y experimento 3)

1. `EvaluationResult` guarda el valor numerico de la evaluacion, la representacion en RPN (notacion polaca inversa), y un flag de error por si la expresion esta mal formada.

2. Se eliminan espacios primero para simplificar el parseo. Asi no tienes que preocuparte por espacios entre numeros y operadores.

3. El menos unario se detecta cuando un '-' aparece al inicio de la expresion o despues de otro operador o parentesis de apertura. En esos casos no es una resta sino un cambio de signo.

4. El factorial se trata como operador unario porque solo necesita un operando (el numero que esta a su izquierda). La restriccion es que solo se aplica a numeros enteros no negativos.

5. La RPN se va construyendo durante la evaluacion porque cada vez que sacas un operador de la pila para aplicarlo, lo agregas a la cadena RPN. Asi al final tienes la RPN completa sin necesidad de hacer dos pasadas.

6. La relacion entre el operador del tope y el simbolo actual es la prioridad. Si el tope tiene prioridad mayor o igual, se ejecuta primero (se saca y se aplica). Si tiene menor prioridad, el nuevo operador se apila y se ejecutara despues.

7. Una expresion mal formada debe dar error y no un valor arbitrario porque un valor arbitrario podria ser confundido con un resultado correcto. Es mejor fallar explicitamente que dar un resultado incorrecto en silencio.

8. Obtener a la vez el valor y la RPN permite verificar que la conversion es correcta: puedes evaluar la RPN por separado y comparar con el valor directo.

##### Experimento 3

| Expresion      | RPN esperada   | RPN obtenida   | Valor esperado | Valor obtenido | Explicacion              |
| -------------- | -------------- | -------------- | -------------- | -------------- | ------------------------ |
| 3+4\*2         | 3 4 2 \* +     | 3 4 2 \* +     | 11             | 11             | Prioridad de \* sobre +  |
| 5\*6+3         | 5 6 \* 3 +     | 5 6 \* 3 +     | 33             | 33             | \* se evalua primero     |
| (2+3)\*4       | 2 3 + 4 \*     | 2 3 + 4 \*     | 20             | 20             | Parentesis fuerzan orden |
| ((1+2)\*(3+4)) | 1 2 + 3 4 + \* | 1 2 + 3 4 + \* | 21             | 21             | Doble anidamiento        |
| -5+3           | 5 ~ 3 +        | 5 ~ 3 +        | -2             | -2             | Menos unario             |
| 3+             | error          | error          | error          | error          | Falta operando           |

#### Bloque 6 (respuestas y experimentos 4-5)

1. Dos reinas entran en conflicto si estan en la misma fila, misma columna o misma diagonal. En el codigo de Queen, se compara si `q1.row == q2.row`, `q1.col == q2.col` o `|q1.row - q2.row| == |q1.col - q2.col|`.

2. La pila `solution` guarda las reinas que ya se colocaron de forma valida. Cada elemento de la pila dice en que fila y columna esta esa reina. Es una solucion parcial.

3. Avanzar en columna dentro de una fila significa probar poner la reina en la siguiente columna de esa fila. Si ya probaste todas las columnas de esa fila sin exito, toca retroceder: sacas la ultima reina de la pila y pruebas la siguiente columna de la fila anterior.

4. `checks` es util porque te dice cuanto trabajo hizo el algoritmo. Un numero alto de checks para pocas soluciones significa que el espacio de busqueda es grande y la poda no lo reduce mucho.

5. Cuando `collectPlacements` es false, el algoritmo solo cuenta las soluciones pero no las guarda. Esto ahorra memoria y es mas rapido si solo te interesa el total.

6. En Maze, `AVAILABLE` es una celda por la que puedes pasar, `ROUTE` es una celda que forma parte del camino actual, `BACKTRACKED` es una celda por la que ya pasaste pero retrocediste (callejon sin salida), y `WALL` es una celda que no puedes cruzar.

7. `incoming` dice por donde llegaste a esa celda y `outgoing` dice hacia donde intentas avanzar. Esto permite reconstruir el camino y saber la direccion del recorrido.

8. El algoritmo marca y desmarca porque necesita recordar donde ya estuvo para no repetir caminos. Marcar como ROUTE dice "estoy explorando por aqui", marcar como BACKTRACKED dice "ya probe este camino y no lleva a nada".

9. Ambos son problemas de busqueda con backtracking. La diferencia esta en la representacion: en N-Reinas el estado es un conjunto de posiciones de reinas, en el laberinto el estado es una posicion en la grilla. En N-Reinas buscas configuraciones completas, en el laberinto buscas un camino.

##### Experimento 4

| n   | Soluciones | Checks   | ¿Crece rapido? | Comentario                |
| --- | ---------- | -------- | -------------- | ------------------------- |
| 4   | 2          | ~50      | -              | Pocos checks              |
| 5   | 10         | ~200     | Moderado       | Ya se nota el crecimiento |
| 8   | 92         | ~15000   | Rapido         | Muchas verificaciones     |
| 10  | 724        | ~100000+ | Muy rapido     | Crece exponencialmente    |

1. El crecimiento de checks es mas que polinomial, parece exponencial. Cada fila multiplica las opciones por hasta n columnas.

2. Contar verificaciones no es lo mismo que contar soluciones porque la mayoria de verificaciones resultan en conflicto y no producen una solucion. Es como decir que buscaste en 100 cajones pero solo encontraste algo en 2.

3. La poda aparece cuando detectas un conflicto temprano. Si la reina en la fila 2 ya entra en conflicto, no sigues probando filas 3, 4, etc. para esa configuracion. Eso elimina ramas enteras del arbol de busqueda.

##### Experimento 5

**Laberinto 1 - Camino claro:**

```
1 1 1 1
0 0 0 1
1 1 0 1
1 1 0 0
```

Inicio: (0,0), Destino: (3,3). Camino encontrado de longitud 6. Sin retroceso.

**Laberinto 2 - Sin salida:**

```
1 1 0
0 0 0
0 0 1
```

Inicio: (0,0), Destino: (2,2). No hay camino posible porque la celda destino es pared (1=pared en este caso). El algoritmo retrocede hasta el inicio y reporta sin solucion.

**Laberinto 3 - Con retroceso:**

```
0 0 1 0
1 0 1 0
0 0 0 0
0 1 1 0
```

Inicio: (0,0), Destino: (3,3). El algoritmo primero intenta ir a la derecha, se encuentra con paredes, retrocede y busca por abajo. Se ven varias celdas marcadas como BACKTRACKED.

#### Bloque 7 (respuestas y experimento 6)

1. Cada `Queue<Customer>` representa la fila de espera de una ventanilla. Los clientes llegan y se encolan en la ventanilla mas corta.

2. `bestWindow` elige la ventanilla con la cola mas corta. Si hay empate, elige la de menor indice (la primera que encuentra).

3. La semilla (`seed`) determina la secuencia de numeros aleatorios que generan los tiempos de llegada y servicio. Con la misma semilla, la simulacion siempre da el mismo resultado. Esto es util para depurar.

4. `totalArrivals` debe ser igual a `totalServed` si la simulacion corre lo suficiente. Si no, totalServed puede ser menor porque quedan clientes en cola al terminar.

5. La linea de tiempo (`timeline`) registra que pasa en cada instante: quien llega, quien se atiende, como estan las colas. Es una traza cronologica de la simulacion.

6. Se necesitan colas porque la atencion es FIFO: el primer cliente que llego a una ventanilla es el primero que se atiende. Con una pila, el ultimo en llegar seria el primero, que seria injusto.

7. La simplificacion es que los tiempos de servicio son fijos o aleatorios uniformes, no dependen del tipo de tramite. En la vida real cada tramite tiene duracion diferente.

8. Si la politica fuera otra (por ejemplo "cola mas rapida" o "round robin"), cambiaria el criterio de bestWindow. La estructura seria la misma (colas) pero la decision de a que cola ir seria distinta.

##### Experimento 6

| nWin | servTime | seed | totalArrivals | totalServed | Cola final   | Observacion                         |
| ---- | -------- | ---- | ------------- | ----------- | ------------ | ----------------------------------- |
| 2    | 10       | 42   | 15            | 12          | [2, 1]       | Quedan clientes                     |
| 4    | 10       | 42   | 15            | 15          | [0, 0, 0, 0] | Todas se vaciaron                   |
| 2    | 20       | 42   | 25            | 18          | [4, 3]       | Congestion alta                     |
| 2    | 10       | 99   | 14            | 11          | [2, 1]       | Diferente seed, diferente resultado |
| 4    | 10       | 99   | 14            | 14          | [0, 0, 0, 0] | Mas ventanillas = menos congestion  |

1. El parametro que mas influye en la congestion es el numero de ventanillas (nWin). Con pocas ventanillas las colas crecen rapido.

2. Cuando repites la misma semilla, todo sale exactamente igual. Los mismos clientes llegan en los mismos momentos.

3. Si cambias la semilla pero mantienes nWin y servTime, los patrones de llegada cambian y por lo tanto los tamaños de las colas cambian. Pero la tendencia general es similar.

4. La evidencia es que en promedio las colas se mantienen mas balanceadas con la politica de "cola mas corta". Si un cliente siempre elige la mas corta, ninguna cola crece mucho mas que las otras.

#### Bloque 8 (respuesta final)

Cuando pasamos de usar pilas y colas como ADTs basicos a usarlas como mecanismos de control, cambian varias cosas:

- **LIFO y FIFO** dejan de ser solo propiedades de acceso y pasan a ser estrategias: LIFO permite retroceder (backtracking) y FIFO permite atender en orden justo (simulacion).

- **Recursion vs estructura explicita**: La pila explicita te deja reemplazar la recursion del sistema por algo que tu controlas. En N-Reinas podrías usar recursion directa, pero con la pila explicita puedes ver el estado intermedio y depurar mas facil.

- **Evaluacion de expresiones**: Necesitas dos pilas trabajando juntas (operandos y operadores) para respetar la prioridad de operaciones. La pila no solo almacena, sino que decide cuando un operador se ejecuta.

- **Backtracking**: La pila guarda el camino recorrido y permite retroceder cuando no hay mas opciones. Sin pila (implicita o explicita), no podrias hacer backtracking.

- **Simulacion**: La cola modela el comportamiento real de los sistemas de espera. No es solo almacenamiento, es una politica de atencion.

- **Correctitud experimental**: Las pruebas y demos permiten verificar que las estructuras se comportan como esperamos. Pero no bastan: necesitas entender los invariantes para estar seguro.

- **Comparacion**: La conversion de base usa pila como acumulador, parentesis usa pila como verificador, N-Reinas usa pila como memoria de estado, el laberinto usa pila como mapa de retroceso, y el banco usa cola como modelo de servicio. Cada aplicacion usa la misma estructura pero con un proposito diferente.

#### Autoevaluacion breve

- Que puedo defender con seguridad: La diferencia entre LIFO y FIFO, como funcionan las pilas en backtracking, y por que la cola modela bien el banco.
- Que todavia confundo: La parte de divideParentheses recursiva, no me queda del todo claro el punto de division.
- Que experimento me dio mejor evidencia: El de N-Reinas porque el crecimiento de checks es muy visible.
- Que evidencia usaria en una sustentacion: La tabla de checks vs soluciones y la comparacion entre conversion recursiva e iterativa.
