# File Manager - Implementation Guide

## English Version

### Understanding the Assignment

This assignment challenges you to create a file management system that can read multiple text files and perform various operations on them. The key constraint is that you must implement this using **only pointers** - no array bracket notation allowed. This restriction serves as an excellent opportunity to develop a deeper understanding of C memory management and pointer arithmetic.

### Core Requirements

1. **File Input**: Read files from stdin and store their contents in memory
2. **Command Processing**: Execute commands from a specified command file
3. **Pointer-Only Implementation**: No array bracket notation (`[]`) allowed anywhere in the code
4. **Operation Implementation**: Implement functions for printing, searching, sorting, removing text, and concatenating files

### Implementation Approach

#### Data Structure Design

For this solution, I've designed two primary structures:

```c
typedef struct {
    char *content;
    size_t length;
} Line;

typedef struct {
    char *path;
    Line *lines;
    int line_count;
} File;
```

This design offers several advantages:
- Each line's content and length are encapsulated together
- Lines belonging to the same file are grouped logically
- File metadata (path, line count) is easily accessible

#### Memory Management Techniques

Memory management is particularly challenging when restricted to pointers:

1. **Dynamic Memory Allocation**: You'll need to allocate memory for file paths, line arrays, and line content
2. **Pointer Arithmetic**: Instead of the familiar `array[i]`, you must use expressions like `*(array + i)` or `array + i`
3. **Proper Cleanup**: To prevent memory leaks, carefully free all allocated memory

A typical pattern for accessing line content looks like this:
```c
Line *current_line = (files + i)->lines + j;
char *line_content = current_line->content;
```

Students often struggle with this syntax initially, but it becomes more intuitive with practice.

#### Command Implementation Strategies

Each command is implemented as a dedicated function:

- **PRINT/PRINT_ALL**: Iterate through files/lines and output with appropriate separators
- **PRINT_LONGEST**: Traverse lines to find the one with maximum length
- **PRINT_LONGEST_FILE**: Compare line counts across files
- **SEARCH**: Use `strstr()` to locate substrings within content
- **SORT**: Leverage `qsort()` with a custom comparator
- **REMOVE**: Create new strings with occurrences removed
- **APPEND**: Combine file contents with careful memory reallocation

### Testing Guidelines

Follow these steps to thoroughly test your implementation:

1. **Compilation**:
   ```bash
   gcc file_manager.c -o program
   ```

2. **Test File Preparation**:
   - Create text files with varied content and line lengths
   - Prepare a command file with a range of operations to test

3. **Execution Methods**:
   ```bash
   # Using input redirection - be careful with trailing spaces!
   ./program < test_input.txt
   
   # Using a pipe (generally more reliable)
   printf "2\nfile1.txt\nfile2.txt\ntest_commands.txt\n" | ./program
   ```

4. **Handling Input File Issues**:
   One common pitfall is trailing spaces in input files. These can cause the program to fail because it searches for incorrectly named files.

   To check for trailing spaces:
   ```bash
   cat -e test_input.txt  # Displays $ at line ends - spaces will appear before the $
   ```

   To create a clean input file:
   ```bash
   # Creates a file without trailing spaces
   printf "2\nfile1.txt\nfile2.txt\ntest_commands.txt" > test_input.txt
   ```

5. **Recommended Test Setup**:
   - `file1.txt`: Simple text file with varied content
   - `file2.txt`: Another text file with different content
   - `test_commands.txt`: File containing commands to test functionality
   - `test_input.txt`: Input specification file

6. **Thorough Testing Strategy**:
   - Test commands individually to verify basic functionality
   - Test command combinations to ensure state is maintained correctly
   - Test edge cases like empty files, long lines, etc.

### Common Challenges and Solutions

1. **Memory Management**: Ensure proper allocation/deallocation to prevent leaks
2. **Pointer Arithmetic**: Practice replacing bracket notation with pointer expressions
3. **String Handling**: Take care with string operations, especially when modifying content
4. **Command Parsing**: Implement robust parsing to handle command parameters correctly

### Educational Value

This assignment offers valuable lessons in:
- Advanced pointer manipulation in C
- Dynamic memory management
- File I/O operations
- String processing techniques

While the restriction against array brackets may seem artificial, it cultivates a deeper understanding of how pointers work under the hood - knowledge that will serve you well in systems programming and beyond.

---

## Versión en Español

### Comprensión del Ejercicio

Este ejercicio te desafía a crear un sistema de gestión de archivos capaz de leer múltiples archivos de texto y realizar diversas operaciones sobre ellos. La restricción clave es que debes implementarlo usando **solamente punteros** - sin notación de corchetes para arrays. Esta limitación sirve como una excelente oportunidad para desarrollar un entendimiento más profundo de la gestión de memoria y aritmética de punteros en C.

### Requisitos Fundamentales

1. **Entrada de Archivos**: Leer archivos desde stdin y almacenar su contenido en memoria
2. **Procesamiento de Comandos**: Ejecutar comandos desde un archivo de comandos especificado
3. **Implementación Exclusiva con Punteros**: No se permite notación de corchetes (`[]`) en ninguna parte del código
4. **Implementación de Operaciones**: Desarrollar funciones para imprimir, buscar, ordenar, eliminar texto y concatenar archivos

### Enfoque de Implementación

#### Diseño de Estructuras de Datos

Para esta solución, he diseñado dos estructuras principales:

```c
typedef struct {
    char *content;
    size_t length;
} Line;

typedef struct {
    char *path;
    Line *lines;
    int line_count;
} File;
```

Este diseño ofrece varias ventajas:
- Cada línea encapsula su contenido y longitud juntos
- Las líneas pertenecientes al mismo archivo se agrupan lógicamente
- Los metadatos del archivo (ruta, número de líneas) son fácilmente accesibles

#### Técnicas de Gestión de Memoria

La gestión de memoria es particularmente desafiante cuando se restringe a punteros:

1. **Asignación Dinámica de Memoria**: Necesitarás asignar memoria para rutas de archivo, arrays de líneas y contenido de líneas
2. **Aritmética de Punteros**: En lugar del familiar `array[i]`, debes usar expresiones como `*(array + i)` o `array + i`
3. **Limpieza Adecuada**: Para prevenir fugas de memoria, libera cuidadosamente toda la memoria asignada

Un patrón típico para acceder al contenido de una línea se ve así:
```c
Line *current_line = (files + i)->lines + j;
char *line_content = current_line->content;
```

Los estudiantes suelen tener dificultades con esta sintaxis inicialmente, pero se vuelve más intuitiva con la práctica.

#### Estrategias de Implementación de Comandos

Cada comando se implementa como una función dedicada:

- **PRINT/PRINT_ALL**: Itera a través de archivos/líneas y genera salida con separadores apropiados
- **PRINT_LONGEST**: Recorre las líneas para encontrar la de longitud máxima
- **PRINT_LONGEST_FILE**: Compara el número de líneas entre archivos
- **SEARCH**: Utiliza `strstr()` para localizar subcadenas dentro del contenido
- **SORT**: Aprovecha `qsort()` con un comparador personalizado
- **REMOVE**: Crea nuevas cadenas eliminando las ocurrencias
- **APPEND**: Combina contenidos de archivos con cuidadosa reasignación de memoria

### Pautas de Prueba

Sigue estos pasos para probar exhaustivamente tu implementación:

1. **Compilación**:
   ```bash
   gcc file_manager.c -o program
   ```

2. **Preparación de Archivos de Prueba**:
   - Crea archivos de texto con contenido variado y líneas de diferentes longitudes
   - Prepara un archivo de comandos con diversas operaciones para probar

3. **Métodos de Ejecución**:
   ```bash
   # Usando redirección de entrada - ¡cuidado con espacios al final!
   ./program < test_input.txt
   
   # Usando una tubería (generalmente más confiable)
   printf "2\nfile1.txt\nfile2.txt\ntest_commands.txt\n" | ./program
   ```

4. **Manejo de Problemas con Archivos de Entrada**:
   Un error común son los espacios al final de las líneas en archivos de entrada. Estos pueden causar que el programa falle porque busca archivos con nombres incorrectos.

   Para verificar espacios al final:
   ```bash
   cat -e test_input.txt  # Muestra $ al final de cada línea - los espacios aparecerán antes del $
   ```

   Para crear un archivo de entrada limpio:
   ```bash
   # Crea un archivo sin espacios al final
   printf "2\nfile1.txt\nfile2.txt\ntest_commands.txt" > test_input.txt
   ```

5. **Configuración de Prueba Recomendada**:
   - `file1.txt`: Archivo de texto simple con contenido variado
   - `file2.txt`: Otro archivo de texto con contenido diferente
   - `test_commands.txt`: Archivo con comandos para probar funcionalidad
   - `test_input.txt`: Archivo de especificación de entrada

6. **Estrategia de Prueba Exhaustiva**:
   - Prueba comandos individualmente para verificar funcionalidad básica
   - Prueba combinaciones de comandos para asegurar que el estado se mantiene correctamente
   - Prueba casos extremos como archivos vacíos, líneas largas, etc.

### Desafíos Comunes y Soluciones

1. **Gestión de Memoria**: Asegura una asignación/liberación adecuada para prevenir fugas
2. **Aritmética de Punteros**: Practica reemplazar notación de corchetes con expresiones de punteros
3. **Manejo de Cadenas**: Ten cuidado con operaciones de cadenas, especialmente al modificar contenido
4. **Análisis de Comandos**: Implementa un análisis robusto para manejar correctamente los parámetros de los comandos

### Valor Educativo

Este ejercicio ofrece lecciones valiosas en:
- Manipulación avanzada de punteros en C
- Gestión dinámica de memoria
- Operaciones de entrada/salida de archivos
- Técnicas de procesamiento de cadenas

Aunque la restricción contra corchetes de arrays pueda parecer artificial, cultiva una comprensión más profunda de cómo funcionan los punteros internamente - conocimiento que te será útil en programación de sistemas y más allá. 