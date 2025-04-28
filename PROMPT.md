# Contexto
Eres un estudiante de programación. 
Debes crear un programa en **lenguaje C** que cumpla exactamente con las instrucciones del archivo TASK.md proporcionado. 
Queremos un código **completo, funcional y correcto**, pero **no buscamos profesionalismo extremo** (por ejemplo, no es necesario hacer modularización avanzada, manejar errores sofisticados o documentar en exceso). 

Todo el **código** debe estar en **inglés** (nombres de variables, funciones, comentarios breves si los hay). 
Todo el **feedback** debe ser en **español**.

# Requerimientos obligatorios

1. **Entradas**:
    - Leer desde `stdin`:
      - Primer línea: un número entero `n`, que indica la cantidad de archivos (`n < 1 000 000 000`).
      - Siguientes `n` líneas: rutas de archivos `Fi`.
      - Última línea: ruta del archivo que contiene los **comandos**.

2. **Procesamiento**:
    - Cada archivo `Fi` contiene varias líneas (`máximo 100 líneas`, cada línea de `máximo 1000 caracteres`).
    - Guardar las líneas en **orden de aparición**.

3. **Comandos disponibles**:
    - `PRINT IDX` → Imprimir el contenido del archivo en el índice `IDX`, separando cada línea por comas.
    - `PRINT_ALL` → Imprimir todos los archivos, separados por saltos de línea; dentro de cada archivo, las líneas separadas por coma.
    - `PRINT_LONGEST IDX` → Imprimir la primera línea más larga del archivo `IDX`.
    - `PRINT_LONGEST_FILE` → Imprimir el path del archivo que tenga **más líneas**.
    - `SEARCH S` → Imprimir el primer archivo que contenga el string `S`. Si no se encuentra, no imprimir nada.
    - `SORT IDX` → Ordenar las líneas del archivo `IDX` (en orden ASCII ascendente).
    - `REMOVE S` → Eliminar todas las ocurrencias del string `S` de todos los archivos.
    - `APPEND IDX1 IDX2` → Concatenar el contenido de `IDX2` al final de `IDX1`.

4. **Restricciones**:
    - Solo se puede usar **punteros y operadores de punteros**.
    - **No usar `[]`** en ninguna parte del programa (ni para arrays, ni para strings).
    - Después de cada impresión, agregar un salto de línea `\n` (excepto cuando no haya nada que imprimir).

5. **Otras observaciones**:
    - No es necesario manejar errores como archivos inexistentes o inputs corruptos.
    - El código debe ser lo suficientemente ordenado para ser entendible como tarea de estudiante.
    - No implementar extras que no se piden.

# Ejemplo de estructura esperada (solo guía, no obligatorio)

- Estructuras para representar los archivos y sus líneas.
- Funciones separadas para:
  - Leer archivos y almacenar contenido.
  - Ejecutar cada tipo de comando.
- Función principal `main()` para organizar el flujo: lectura de input → lectura de archivos → lectura de comandos → ejecución.

# Formato de entrega

- Un solo archivo `.c`.
- Todo el código en **inglés**.
- No usar librerías no estándar.
- Compilable usando: `gcc archivo.c -o program`.

# Feedback

El feedback debe ser dado en **español** y debe indicar:
- Si el código cumple correctamente los requisitos.
- Sugerencias si detectas fallos graves.
- Breves recomendaciones (opcionales) para mejorar si fuera muy evidente, pero recordar que **no es necesario llevarlo a nivel profesional**.