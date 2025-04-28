# File Manager

## English

This program implements a file manager in C that can read and manipulate multiple text files.

### Compilation

To compile the program, just run this in your terminal:

```bash
gcc -o program program.c -Wall -Werror
```

### Running the Program

You can run the program in three ways:

1. **Interactive mode**: Run the program and type the inputs manually:
   ```bash
   ./program
   ```
   Then enter the number of files, file paths, and command file path as prompted.

2. **Input redirection**: Create a text file with the inputs and redirect it:
   ```bash
   ./program < test_input.txt
   ```

3. **Using a pipe**: This is the most reliable method:
   ```bash
   printf "2\n./hw4/file00.in\n./hw4/file01.in\n./hw4/command00.in" | ./program
   ```

**Important note about input files**: Be super careful with trailing spaces in your input files! If there's a space at the end of a line in your input file (especially the last line with the command file path), the program will try to find a file with that space included in the name. Always check and make sure you don't have trailing spaces.

To check for trailing spaces:
```bash
cat -e test_input.txt  # Shows $ at the end of each line, you'll see if there are spaces
```

To create a clean input file:
```bash
printf "2\n./hw4/file00.in\n./hw4/file01.in\n./hw4/command00.in" > test_input.txt
```

### Program Functionality

The program supports these commands:

1. **PRINT IDX**: Prints all lines from the file at index IDX.
   Example: `PRINT 0` prints all lines from the first file.

2. **PRINT_ALL**: Prints all lines from all files.
   Example: `PRINT_ALL`

3. **PRINT_LONGEST IDX**: Prints the longest line from the file at index IDX.
   Example: `PRINT_LONGEST 1` prints the longest line from the second file.

4. **PRINT_LONGEST_FILE**: Prints the name of the file with the most lines.
   Example: `PRINT_LONGEST_FILE`

5. **SEARCH S**: Searches for the string S in all files and prints matching lines.
   Example: `SEARCH Hello` prints all lines containing "Hello".

6. **SORT IDX**: Sorts the lines in the file at index IDX alphabetically.
   Example: `SORT 0` sorts the first file.

7. **REMOVE S**: Removes all occurrences of the string S from all files.
   Example: `REMOVE World` removes "World" from all lines in all files.

8. **APPEND SRC_IDX DEST_IDX**: Appends the content of the source file to the destination file.
   Example: `APPEND 0 1` appends the content of the first file to the second file.

### Input Format

The program expects the following input:
1. A number n indicating the number of files to process.
2. n lines, each containing the path to a file.
3. A line containing the path to a file with commands.

Example:
```
2
./hw4/file00.in
./hw4/file01.in
./hw4/command00.in
```

### Output Format

The output depends on the commands in the command file. Typically, it will display the contents of files or specific lines based on the commands.

## Español (Spanish)

# Administrador de Archivos

Este programa implementa un administrador de archivos en C que puede leer y manipular múltiples archivos de texto.

### Compilación

Para compilar el programa, simplemente ejecuta esto en tu terminal:

```bash
gcc -o program program.c -Wall -Werror
```

### Ejecutando el Programa

Puedes ejecutar el programa de tres maneras:

1. **Modo interactivo**: Ejecuta el programa y escribe las entradas manualmente:
   ```bash
   ./program
   ```
   Luego ingresa el número de archivos, las rutas de los archivos y la ruta del archivo de comandos según se te solicite.

2. **Redirección de entrada**: Crea un archivo de texto con las entradas y redirígelo:
   ```bash
   ./program < test_input.txt
   ```

3. **Usando una tubería**: Este es el método más confiable:
   ```bash
   printf "2\n./hw4/file00.in\n./hw4/file01.in\n./hw4/command00.in" | ./program
   ```

**Nota importante sobre archivos de entrada**: ¡Ten mucho cuidado con los espacios al final en tus archivos de entrada! Si hay un espacio al final de una línea en tu archivo de entrada (especialmente en la última línea con la ruta del archivo de comandos), el programa intentará encontrar un archivo con ese espacio incluido en el nombre. Siempre verifica y asegúrate de no tener espacios al final.

Para verificar si hay espacios al final:
```bash
cat -e test_input.txt  # Muestra $ al final de cada línea, verás si hay espacios
```

Para crear un archivo de entrada limpio:
```bash
printf "2\n./hw4/file00.in\n./hw4/file01.in\n./hw4/command00.in" > test_input.txt
```

### Funcionalidad del Programa

El programa admite estos comandos:

1. **PRINT IDX**: Imprime todas las líneas del archivo en el índice IDX.
   Ejemplo: `PRINT 0` imprime todas las líneas del primer archivo.

2. **PRINT_ALL**: Imprime todas las líneas de todos los archivos.
   Ejemplo: `PRINT_ALL`

3. **PRINT_LONGEST IDX**: Imprime la línea más larga del archivo en el índice IDX.
   Ejemplo: `PRINT_LONGEST 1` imprime la línea más larga del segundo archivo.

4. **PRINT_LONGEST_FILE**: Imprime el nombre del archivo con más líneas.
   Ejemplo: `PRINT_LONGEST_FILE`

5. **SEARCH S**: Busca la cadena S en todos los archivos e imprime las líneas coincidentes.
   Ejemplo: `SEARCH Hello` imprime todas las líneas que contienen "Hello".

6. **SORT IDX**: Ordena alfabéticamente las líneas del archivo en el índice IDX.
   Ejemplo: `SORT 0` ordena el primer archivo.

7. **REMOVE S**: Elimina todas las ocurrencias de la cadena S de todos los archivos.
   Ejemplo: `REMOVE World` elimina "World" de todas las líneas en todos los archivos.

8. **APPEND SRC_IDX DEST_IDX**: Añade el contenido del archivo de origen al archivo de destino.
   Ejemplo: `APPEND 0 1` añade el contenido del primer archivo al segundo archivo.

### Formato de Entrada

El programa espera la siguiente entrada:
1. Un número n que indica la cantidad de archivos a procesar.
2. n líneas, cada una con la ruta a un archivo.
3. Una línea con la ruta a un archivo con comandos.

Ejemplo:
```
2
./hw4/file00.in
./hw4/file01.in
./hw4/command00.in
```

### Formato de Salida

La salida depende de los comandos en el archivo de comandos. Típicamente, mostrará el contenido de los archivos o líneas específicas según los comandos. 