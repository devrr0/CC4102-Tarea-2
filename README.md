# CC4102-Tarea-2

## Índice
- [Descripción](#descripción)
- [Ejecución](#ejecución)
- [Estructura del Proyecto](#estructura-del-proyecto)

## Descripción
Implementación de estructura de datos Trie con funcionalidades que permiten utilizarlo como motor de autocompletado de texto.

## Ejecución

Primero se debe clonar el repositorio con: 

```bash
git clone https://github.com/devrr0/CC4102-Tarea-2.git
```

## Estructura del proyecto
```bash
CC4102-TAREA-2/                             # Carpeta principal
├── .vscode/                                # Ambiente VS Code
├── Tarea_2/                                # Carpeta del proyecto
│   ├── datos/                              # Archivos del experimento
│   ├── resultados/                         # Resultados del experimento
│   ├── src/                                # Archivos principales
│   │    ├──estructuras/                    # Estructuras del proyecto
│   │    │  └── nodo.c                      # Estructura de nodo y trie
│   │    └──operaciones/                    # Operaciones del proyecto
│   │       ├── autocomplete.c              # Autocompletado en trie
│   │       ├── crear_trie.c                # Inicializacion trie
│   │       ├── descend.c                   # Descender en trie
│   │       ├── insertar.c                  # Insertar en trie
│   │       └── update_priority.c           # Actualizar prioridad
│   └── experimento.c                       # Experimento
├── .gitignore                              # Archivos ignorados por Git
└── README.md                               # Documentación del proyecto
```
