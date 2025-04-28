# Notas de Implementación

Este documento contiene mis notas sobre la implementación del administrador de archivos.

## Diseño de Estructura de Datos

Para este proyecto, creé dos estructuras principales:

1. `Line`: Para almacenar cada línea de texto y su longitud.
   ```c
   typedef struct {
       char* text;
       int length;
   } Line;
   ```

2. `File`: Para almacenar el nombre del archivo y un array de punteros a `Line`.
   ```c
   typedef struct {
       char* name;
       Line** lines;
       int numLines;
       int maxLines;
   } File;
   ```

Decidí usar punteros a punteros (`Line**`) para el array de líneas porque necesitaba realocar memoria dinámicamente a medida que añadía más líneas, y era más fácil hacerlo así.

## Gestión de Memoria

La gestión de memoria fue uno de los aspectos más desafiantes de este proyecto. Tuve que asegurarme de:

1. Asignar memoria dinámicamente para cada estructura y cadena de caracteres:
   ```c
   File* file = (File*) malloc(sizeof(File));
   file->name = strdup(fileName); // Usa strdup para crear una copia de la cadena
   file->lines = (Line**) malloc(sizeof(Line*) * INITIAL_CAPACITY);
   ```

2. Liberar toda la memoria asignada para evitar fugas de memoria:
   ```c
   void freeFile(File* file) {
       if (file == NULL) return;
       
       // Liberar cada línea
       for (int i = 0; i < file->numLines; i++) {
           free(file->lines[i]->text);
           free(file->lines[i]);
       }
       
       // Liberar el nombre y el array de líneas
       free(file->name);
       free(file->lines);
       free(file);
   }
   ```

Es muy importante liberar la memoria en el orden correcto: primero el contenido interno (texto de las líneas), luego las estructuras de línea, y finalmente la estructura del archivo.

## Implementación de Comandos

Implementé cada comando como una función separada para hacer el código más modular y fácil de depurar:

1. `printFile`: Imprime todas las líneas de un archivo específico.
2. `printAll`: Imprime todas las líneas de todos los archivos.
3. `printLongest`: Encuentra e imprime la línea más larga de un archivo.
4. `printLongestFile`: Encuentra e imprime el nombre del archivo con más líneas.
5. `searchString`: Busca una cadena en todos los archivos e imprime las líneas que la contienen.
6. `sortFile`: Ordena las líneas de un archivo alfabéticamente.
7. `removeString`: Elimina todas las ocurrencias de una cadena de todos los archivos.
8. `appendFile`: Añade el contenido de un archivo a otro.

La implementación más interesante fue `sortFile`, donde tuve que implementar un algoritmo de ordenación:

```c
void sortFile(File* file) {
    // Burbuja simple para ordenar
    for (int i = 0; i < file->numLines - 1; i++) {
        for (int j = 0; j < file->numLines - i - 1; j++) {
            if (strcmp(file->lines[j]->text, file->lines[j+1]->text) > 0) {
                // Intercambiar punteros (no contenido)
                Line* temp = file->lines[j];
                file->lines[j] = file->lines[j+1];
                file->lines[j+1] = temp;
            }
        }
    }
}
```

## Análisis de Entrada

El flujo de programa es:

1. Leer el número de archivos.
2. Leer los nombres de los archivos y cargarlos en memoria.
3. Leer el nombre del archivo de comandos.
4. Abrir y procesar el archivo de comandos.

Un problema que encontré fue con los espacios al final en los archivos de entrada. Si tienes un espacio al final de la línea con el nombre del archivo de comandos, el programa intentará abrir un archivo con ese espacio en el nombre, lo que causará errores. Siempre verifica que tus archivos de entrada no tengan espacios al final.

## Probando tu Solución

1. Prepara tus archivos de prueba: crea `./hw4/file00.in`, `./hw4/file01.in`, y `./hw4/command00.in` con el contenido deseado.
   - Importante: Asegúrate de que tus archivos de entrada no tengan espacios al final. Puedes usar `cat -e test_input.txt` para verificar (verás un $ al final de cada línea).
   - Crea un archivo limpio con: `printf "2\n./hw4/file00.in\n./hw4/file01.in\n./hw4/command00.in" > test_input.txt`

2. Compila el programa: `gcc -o program program.c -Wall -Werror`

3. Ejecuta el programa:
   ```bash
   ./program < test_input.txt
   ```
   O mejor aún:
   ```bash
   printf "2\n./hw4/file00.in\n./hw4/file01.in\n./hw4/command00.in" | ./program
   ```

Por ejemplo, con estos archivos:
- `./hw4/file00.in`: contiene "Hello", "World", "123!"
- `./hw4/file01.in`: contiene "This", "is", "CS240", "Class"
- `./hw4/command00.in`: contiene varios comandos como "PRINT 0", "PRINT_ALL", etc.

## Desafíos Comunes

1. **Fugas de Memoria**: Olvidar liberar memoria puede causar fugas. Usa herramientas como Valgrind para detectarlas.
2. **Manejo de Strings**: Manipular strings en C es propenso a errores. Siempre verifica los límites y la asignación de memoria.
3. **Índices Incorrectos**: Recuerda que los arrays en C comienzan en 0, no en 1.

## Valor Educativo

Este proyecto me enseñó mucho sobre:
- Gestión dinámica de memoria en C
- Manipulación de archivos y strings
- Diseño modular de programas

Espero que estas notas sean útiles para entender mi implementación. ¡Buena suerte con tu propio proyecto!

## Notas Adicionales

Algunas cosas que aprendí:
- El uso de `malloc` y `free` es crucial para evitar fugas de memoria
- Siempre verifica los valores devueltos por funciones como `fopen` para manejar errores
- Divide tu código en funciones pequeñas y específicas para facilitar la depuración
