# Proyecto Final: Sistemas Operativos

## Información de los Estudiantes
- **Nombres Completos:** Juan José Álvarez Ocampo, Sara Echeverri Gomez y Nathalia Valentina Cardoza Azuaje
- **Clase:** SI2004
- **Curso:** Sistemas operativos
- **Profesor:** Diego Ivan Cruz Ordiéres 
- **Tarea:** Proyecto final

## Ambiente
- **Sistema Operativo:** macOS Tahoe 26.0.1
- **Procesador:** Apple Silicon M4
- **Memoria:** 16 GB RAM, 512 GB
- **Versión de Visual Studio Code:** 1.105.1
- **Terminal:** zsh 5.9 (arm64-apple-darwin25.0)

## Prerrequisitos

- **Sistema Operativo:** Windows, linux o macOS
- **Compilador de C++:** Clang 14 o superior
- **CMake:** 3.20 o superior
- **Catch2:** v3
- **CLI11:** v2.4 o superior

## Estructura del proyecto

```
Sistemas-Operativos
│
├─ cli
│   ├─ cli_handler.h
│   └─ main.cpp
│
├─ docs
│   ├─ .DS_Store
│   └─ Informe Técnico .docx
│
├─ kernel-slim
│   └─ os_kernel.h
│
├─ modules
│   ├─ cpu
│   │   ├─ process.h
│   │   ├─ process_manager.h
│   │   ├─ scheduler.h
│   │   └─ scheduler_sjf.h
│   │
│   ├─ io
│   │   ├─ buffer.h
│   │   └─ sync.h
│   │
│   ├─ mem
│   │   ├─ memory_visualizer.h
│   │   ├─ paging.h
│   │   ├─ paging_lru.h
│   │   └─ scheduler_rr.h
│   │
│   └─ disk
│       └─ vacio.gitkeep
│
├─ test
│   └─ vacio.gitkeep
│
├─ .DS_Store
├─ .gitattributes
└─ README.md 
```

