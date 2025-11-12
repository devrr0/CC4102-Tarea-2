# CC4102-Tarea-2

## Índice
- [Descripción](#descripción)
- [Ejecución](#ejecución)
- [Estructura del Proyecto](#estructura-del-proyecto)

## Descripción
El objetivo de este proyecto es analizar el desempeño de una estructura de datos Trie como motor de autocompletado de texto. Para ello se desarrollaron en el lenguaje C algoritmos de inserción y autocompletado que cumplen con una estructura de Trie con caminos unarios.

Para el desarrollo del experimento se utilizó el dataset *words.txt* que contiene $N=2^{18}$ palabras para construir un trie, midiendo el espacio y tiempo que toma la inserción de estas $N$ palabras. Además, se utilizaron los datasets *wikipedia.txt*, *random.txt* y *random_with_distribution.txt* para analizar la capacidad de autocompletado, simulando la escritura palabra por palabra, letra por letra sobre la estructura de trie generada por la inserción de *words.txt*. 

## Ejecución

Primero se debe clonar el repositorio con 

```bash
git clone https://github.com/devrr0/CC4102-Tarea-2.git
```

Luego es necesario subir a la carpeta */datos* los archivos *wikipedia.txt*, *random.txt* y *random_with_distribution.txt*. Una vez hecho esto se puede ejecutar el experimento con los siguientes comandos

```bash
cd Tarea_2
cd src
gcc -o experimento experimento.c
./experimento
```

## Estructura del proyecto
```bash
CC4102-TAREA-2/                             # Carpeta principal
├── .vscode/                                # Ambiente VS Code
├── Tarea_2/                                # Carpeta del proyecto
│   ├── datos/                              # Archivos del experimento
│   │    ├── words_sample.txt               # Dataset para test de insercion
│   │    └── words.txt                      # Dataset insercion
│   ├── resultados/                         # Resultados del experimento
│   │    ├── experimento_tiempo.txt         # Resultados tiempo insercion
│   │    ├── experimento.txt                # Resultados espacio insercion y autocompletado
│   │    └── test.txt                       # Resultados test de insercion
│   ├── src/                                # Archivos principales
│   │    ├──estructuras/                    # Estructuras del proyecto
│   │    │  └── nodo.c                      # Estructura de nodo y trie
│   │    └──operaciones/                    # Operaciones del proyecto
│   │       ├── autocomplete.c              # Autocompletado en trie
│   │       ├── crear_trie.c                # Inicializacion trie
│   │       ├── descend.c                   # Descender en trie
│   │       ├── insertar.c                  # Insertar en trie
│   │       └── update_priority.c           # Actualizar prioridad
│   ├── test.c                              # Test construccion de trie
│   ├── test.exe                            # Test construccion de trie (ejecutable)
│   ├── experimento.c                       # Experimento
│   └── experimento.exe                     # Experimento (ejecutable)
├── .gitignore                              # Archivos ignorados por Git
└── README.md                               # Documentación del proyecto
```
