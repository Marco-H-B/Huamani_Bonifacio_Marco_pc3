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

Mañana voy a implementar las funciones del treap: split, merge, insert, erase, kth y countLess.
