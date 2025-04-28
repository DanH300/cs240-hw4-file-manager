# File Manager - CS240 Homework 4

## English Instructions

### Compilation

To compile the program, just run this in your terminal:

```bash
gcc file_manager.c -o program
```

### Execution

The program takes input from stdin with this format:

1. First line: A number `n` of files to process
2. Next `n` lines: Paths to each file
3. Last line: Path to the command file

Here's a simple example:
```
2
./files/file1.txt
./files/file2.txt
./files/commands.txt
```

You can run the program in a few different ways:

1. Interactive mode (typing everything manually):
```bash
./program
```
Then just type each input line when prompted.

2. Using input redirection:
```bash
./program < test_input.txt
```

3. Using a pipe (this is what I usually do because it's easier):
```bash
printf "2\nfile1.txt\nfile2.txt\ntest_commands.txt\n" | ./program
```

#### Important Note on Input Files
Watch out for trailing spaces! I spent hours debugging before I realized my input file had spaces at the end of lines. These can mess up the program because it'll look for files with the wrong names.

You can check for sneaky trailing spaces with:
```bash
cat -e input_file.txt  # Shows $ at end of lines and will reveal any spaces
```

If you want to be 100% sure your input file is clean:
```bash
printf "2\nfile1.txt\nfile2.txt\ntest_commands.txt" > test_input.txt
```

### Available Commands

The program handles these commands:

- `PRINT IDX`: Shows the content of file at index IDX, with commas between lines
- `PRINT_ALL`: Dumps all file contents with newlines between files and commas within each file
- `PRINT_LONGEST IDX`: Shows the longest string in file IDX
- `PRINT_LONGEST_FILE`: Shows which file has the most lines
- `SEARCH S`: Finds the first file containing string S
- `SORT IDX`: Sorts the lines in file IDX alphabetically 
- `REMOVE S`: Removes all occurrences of string S from all files
- `APPEND IDX1 IDX2`: Adds all content from file IDX2 to the end of file IDX1

### Example

Input files:
```
# file1.txt
Hello
World
123!

# file2.txt
This
is
CS240
Class

# commands.txt
PRINT_LONGEST 1
PRINT_LONGEST_FILE
PRINT 0
APPEND 0 1
PRINT 0
PRINT_ALL
```

Expected output:
```
CS240
./files/file2.txt
Hello,World,123!
Hello,World,123!,This,is,CS240,Class
Hello,World,123!,This,is,CS240,Class
This,is,CS240,Class
```

### Test Results

I tested the program myself and it works correctly:

```bash
printf "2\nfile1.txt\nfile2.txt\ntest_commands.txt\n" | ./program
```

The output matched what was expected for each command, so everything seems to be working!

### Notes

- Remember that file indexes start from 0, not 1
- The program adds a newline after each print command
- No bracket notation (`[]`) is used anywhere as required by the assignment spec

---

## Instrucciones en Español

### Compilación

Para compilar el programa, simplemente ejecuta esto en tu terminal:

```bash
gcc file_manager.c -o program
```

### Ejecución

El programa toma entrada desde stdin con este formato:

1. Primera línea: Un número `n` de archivos a procesar
2. Siguientes `n` líneas: Rutas a cada archivo
3. Última línea: Ruta al archivo de comandos

Un ejemplo sencillo:
```
2
./archivos/archivo1.txt
./archivos/archivo2.txt
./archivos/comandos.txt
```

Puedes ejecutar el programa de varias formas:

1. Modo interactivo (escribiendo todo manualmente):
```bash
./program
```
Luego simplemente escribe cada línea cuando te lo pida.

2. Usando redirección de entrada:
```bash
./program < test_input.txt
```

3. Usando una tubería (esto es lo que suelo hacer porque es más fácil):
```bash
printf "2\narchivo1.txt\narchivo2.txt\ncomandos.txt\n" | ./program
```

#### Nota Importante sobre Archivos de Entrada
¡Cuidado con los espacios al final! Pasé horas depurando antes de darme cuenta que mi archivo de entrada tenía espacios al final de las líneas. Estos pueden estropear el funcionamiento del programa porque buscará archivos con nombres incorrectos.

Puedes detectar estos molestos espacios finales con:
```bash
cat -e archivo_entrada.txt  # Muestra $ al final de las líneas y revelará cualquier espacio
```

Si quieres estar 100% seguro de que tu archivo está limpio:
```bash
printf "2\nfile1.txt\nfile2.txt\ntest_commands.txt" > test_input.txt
```

### Comandos Disponibles

El programa maneja estos comandos:

- `PRINT IDX`: Muestra el contenido del archivo en índice IDX, con comas entre líneas
- `PRINT_ALL`: Muestra todos los archivos con saltos de línea entre ellos y comas dentro de cada uno
- `PRINT_LONGEST IDX`: Muestra la cadena más larga del archivo IDX
- `PRINT_LONGEST_FILE`: Muestra qué archivo tiene más líneas
- `SEARCH S`: Encuentra el primer archivo que contenga la cadena S
- `SORT IDX`: Ordena las líneas del archivo IDX alfabéticamente
- `REMOVE S`: Elimina todas las apariciones de la cadena S de todos los archivos
- `APPEND IDX1 IDX2`: Añade todo el contenido del archivo IDX2 al final del archivo IDX1

### Ejemplo

Archivos de entrada:
```
# archivo1.txt
Hola
Mundo
123!

# archivo2.txt
Esto
es
CS240
Clase

# comandos.txt
PRINT_LONGEST 1
PRINT_LONGEST_FILE
PRINT 0
APPEND 0 1
PRINT 0
PRINT_ALL
```

Salida esperada:
```
CS240
./archivos/archivo2.txt
Hola,Mundo,123!
Hola,Mundo,123!,Esto,es,CS240,Clase
Hola,Mundo,123!,Esto,es,CS240,Clase
Esto,es,CS240,Clase
```

### Resultados de Prueba

Probé el programa yo mismo y funciona correctamente:

```bash
printf "2\nfile1.txt\nfile2.txt\ntest_commands.txt\n" | ./program
```

La salida coincidió con lo esperado para cada comando, ¡así que todo parece estar funcionando!

### Notas

- Recuerda que los índices de archivos empiezan desde 0, no desde 1
- El programa añade un salto de línea después de cada comando de impresión
- No se usa notación de corchetes (`[]`) en ninguna parte, como requiere la especificación 