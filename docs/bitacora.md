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

Hoy me dedique a probar el rendimiento del Treap y a asegurarme de que no se rompa con casos raros.

1. **Casos Borde** (`tests/test_casos_borde.cpp`): Escribi pruebas especificas para ver que pasa si insertamos `INT_MAX`, `INT_MIN` o el `0`. Todo funciono perfecto. Tambien probe buscar el k-esimo con K=0 o K negativo, o K mayor al tamaño del arbol. En vez de crashear (Segmentation Fault), el codigo devuelve -1, lo cual es muy seguro. Pase los 13/13 tests de bordes.

2. **Benchmark** (`benchmark/benchmark_treap.cpp`): Simule el entorno de SPOJ generando 200,000 operaciones aleatorias gigantescas (insertar, borrar, buscar). Las medi usando `std::chrono` y el resultado me dejo sorprendido: procesar las 200,000 operaciones tomo solo **37 ms**! SPOJ suele dar entre 1 a 2 segundos de limite de tiempo, asi que mi implementacion es absurdamente rapida y pasara sobrado.

Tambien añadi los nuevos ejecutables en el `CMakeLists.txt` y deje todo listo. 

Por ultimo, subi la resolucion de la Actividad 5 al repo en la carpeta de actividades.

Mañana (Dia 5) preparare el reporte escrito y empezare a armar el guion para el video final.
