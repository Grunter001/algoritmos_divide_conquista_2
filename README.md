# Problemas de Divide y Vencerás

Este repositorio contiene la implementación en C de soluciones algorítmicas clásicas basadas en el paradigma de **Divide y Vencerás** (Divide and Conquer). Cada problema ilustra una forma distinta de dividir el espacio de búsqueda o los datos para lograr una complejidad óptima.

## Estructura de los Problemas

### 1. Formas de Poner Paréntesis (`1_formas_parentesis.c`)
Dada una expresión matemática con sumas, restas y multiplicaciones, el algoritmo calcula todos los resultados posibles al agrupar los operadores de todas las formas válidas.
* **Enfoque:** Recorre la expresión y, por cada operador encontrado, divide la cadena en dos mitades. Resuelve recursivamente la izquierda y la derecha, y finalmente combina (producto cartesiano) los resultados de ambas mitades aplicando el operador actual.
* **Complejidad:** Ligada a los Números de Catalan (exponencial), óptima para este problema donde se requieren todas las combinaciones posibles.

### 2. Multiplicación de Enteros Grandes (`2_karatsuba.c`)
Multiplica dos enteros de hasta $10^4$ dígitos representados como cadenas de texto, sin utilizar bibliotecas de números grandes (*BigInt*).
* **Enfoque:** Implementa el **Algoritmo de Karatsuba**. Divide los números a la mitad y reduce recursivamente el problema de 4 a 3 multiplicaciones de menor tamaño. Para números menores o iguales a 32 dígitos, utiliza un caso base de multiplicación escalar tradicional (fuerza bruta).
* **Complejidad:** $O(n^{\log_2 3}) \approx O(n^{1.58})$, significativamente más rápido que el $O(n^2)$ de la multiplicación escolar para números gigantes.

### 3. Conteo de Intercambios (`3_conteo_intercambios.c`)
Calcula el número mínimo de intercambios adyacentes necesarios para ordenar un arreglo (equivalente a contar el número de *inversiones*).
* **Enfoque:** Utiliza una modificación del algoritmo **Merge Sort**. Durante el paso de combinación (*merge*), si un elemento de la mitad derecha es menor que uno de la izquierda, se suma al contador la cantidad de elementos restantes en la mitad izquierda.
* **Complejidad:** $O(n \log n)$ en tiempo, utilizando $O(n)$ en espacio auxiliar.

### 4. Par de Puntos más Cercano (`4_par_puntos_mas_cercano.c`)
Encuentra la distancia euclidiana mínima entre dos puntos dentro de un conjunto en un plano 2D.
* **Enfoque:** Ordena los puntos por su coordenada X y divide el plano en dos mitades. Busca recursivamente la distancia mínima en ambas mitades ($d$). Luego, revisa una franja central de ancho $2d$ alrededor de la línea divisoria, ordenando los puntos de esta franja por su coordenada Y para asegurar un chequeo en tiempo lineal.
* **Complejidad:** $O(n \log n)$.

### 5. k-ésimo Elemento más Grande (`5_k_esimo_elemento.c`)
Encuentra el k-ésimo mayor elemento en un arreglo desordenado sin aplicar un algoritmo de ordenamiento completo.
* **Enfoque:** Implementa **Quickselect** con un pivote elegido de manera aleatoria. Funciona como Quicksort, pero en lugar de llamar recursivamente a ambas mitades, descarta la mitad en la que matemáticamente no puede estar el k-ésimo elemento.
* **Complejidad:** Tiempo esperado de $O(n)$.

---

## Compilación y Ejecución

Se recomienda el uso del compilador GCC. Todos los códigos siguen el estándar C11.

**Comando general de compilación:**
```bash
gcc -O3 -Wall -Wextra -std=c11 archivo.c -o ejecutable
```

**Nota para el Problema 4:**
Como el problema 4 hace uso de funciones matemáticas (`sqrt` de `<math.h>`), es necesario enlazar la librería matemática agregando la bandera `-lm` al final del comando:
```bash
gcc -O3 -Wall -Wextra -std=c11 4_par_puntos_mas_cercano.c -o par_puntos -lm
```

Para ejecutar cualquier problema, envíe los datos de entrada a través de la consola o redirigiendo un archivo de texto:
```bash
./ejecutable < input.txt
```