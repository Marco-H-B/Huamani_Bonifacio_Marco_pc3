# Bitacora de desarrollo - PC3

## Dia 1 - Jueves 4 de junio

Hoy empece con la practica. Lo primero que hice fue leer bien el problema que me toco: SPOJ ORDERSET. Basicamente hay que poder insertar, eliminar, buscar el k-esimo menor y contar cuantos son menores que un valor dado.

Despues de leer un rato, decidi usar un **Treap** porque en la semana 5 y 6 vimos arboles balanceados y el treap es justo lo que necesito: un BST que se balancea solo con prioridades aleatorias. Ademas, si le agrego un campo de tamaño a cada nodo puedo hacer kth y count en O(log n).

Lo que hice hoy:
- Cree la estructura del repositorio (carpetas include, src, docs, tests, etc)
- Configure el .gitignore para no subir builds ni ejecutables
- Arme el CMakeLists.txt basico con C++17
- Cree el archivo treap.h con la estructura del Nodo y las firmas de las funciones
- Hice el esqueleto del main.cpp que lee la entrada del SPOJ
- Llene el README con la info del problema

## Dia 2 - Viernes 5 de junio

Hoy me puse a programar en serio la logica del Treap.
Cree el archivo `treap.cpp` y fui implementando funcion por funcion:
- Primero hice el `split` y el `merge`, que son la base de todo. Con eso el resto es mas facil.
- Despues agregue `insertar` y `eliminar`, usando split y merge. Me acorde de chequear si el elemento ya existia para no meter repetidos (el problema dice que es un conjunto).
- Para responder las consultas de SPOJ implemente `kesimo` aprovechando el campo `tam` que guarda el tamaño de cada subarbol, y `contarMenores` sumando los tamaños de los hijos izquierdos cuando bajo a la derecha.

Tambien modifique el `CMakeLists.txt` para que incluya `treap.cpp` a la hora de compilar. 

Para mañana (dia 3) voy a armar los tests unitarios para asegurarme que todo ande bien, hacer la comparacion contra fuerza bruta y revisar que compile y corra todo limpio.

## Dia 3 - Viernes 6 de junio

Hoy me dedique a probar que todo funcione bien. Cree tres cosas nuevas:

1. **Tests unitarios** (`tests/test_treap.cpp`): Tiene 8 tests con 38 verificaciones en total. Prueba insercion, duplicados, eliminacion, kth, contarMenores, arbol vacio, el ejemplo exacto de SPOJ y un test de estres con 100 elementos. Todos pasaron.

2. **Fuerza bruta** (`tests/test_brute_force.cpp`): Este es el que voy a usar para el reto del video. Genera operaciones aleatorias (insert, delete, kth, count) y las ejecuta tanto en el treap como en un vector ordenado. Si ambos dan lo mismo, el treap esta bien. Probe con 5 semillas diferentes y 900 operaciones totales, 0 errores.

3. **Demo interactivo** (`demos/demo_orderset.cpp`): Ejecuta paso a paso las operaciones del ejemplo de SPOJ y unas extras, mostrando el estado del treap (tamaño, elementos, raiz) despues de cada operacion.

Tambien tuve que arreglar un detalle: las funciones `obtenerTam` y `actualizar` que estaban definidas en el header daban error de "multiple definition" al compilar con varios .cpp. Las marque como `inline` y se arreglo.

Actualice el CMakeLists para incluir los tests con enable_testing() y add_test(), y guarde los resultados en la carpeta resultados/.

Para el dia 4 me toca hacer los casos borde mas especificos y el benchmark.

## Dia 4 - Lunes 8 de junio

Hoy me puse a probar el rendimiento del treap, porque SPOJ tira Time Limit Exceeded (TLE) si el codigo no es eficiente (el problema da 200,000 operaciones).

Cree el archivo `benchmark/benchmark.cpp`. Lo que hace es generar 200,000 operaciones aleatorias entre inserciones, eliminaciones, consultas kth y consultas count, con claves en el rango de -10^9 a 10^9 que pide SPOJ.

Lo compile activando las optimizaciones de C++ (`-O3`) y el resultado me dejo re tranquilo: 200k operaciones en apenas ~40 ms (unas 5 millones de ops/s). Teniendo en cuenta que SPOJ normalmente da 1 segundo de limite, estoy sobradisimo de tiempo. Guarde la salida en `resultados/benchmark.txt` para mostrarlo en el video si me da el tiempo.

Tambien aproveche de subir la resolucion de la Actividad 5 al repositorio de la PC3.
Para mañana (dia 5) hare unos ultimos detalles y quiza empiece a grabar o preparar las diapositivas del video.

## Dia 5 - Martes 9 de junio

Hoy dedique el dia basicamente a organizar todo el proyecto, dejarlo limpio y subir la ultima actividad.

Subi al repositorio mi resolucion detallada de la Actividad 6. Tambien me asegure de que no quedara ningun archivo basura o temporal por ahi tirado (borre un par de `.txt` de los logs de errores vacios que se habian generado cuando corria los tests del treap).

Aparte de eso, me pase un buen rato haciendo pruebas generales, compilando de cero todo para verificar que mis instrucciones en el `CMakeLists.txt` esten perfectas y revisando que todo este listo. Mañana (dia 6) voy a realizar la grabacion del video de sustentacion, donde voy a mostrar la solucion, correr el demo interactivo, probar la comparacion de fuerza bruta y los benchmarks para demostrar que funciona a la perfeccion.
