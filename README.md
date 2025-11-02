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
## Guía de instalación y ejecución del simulador
Para ejecutar nuestro proyecto en tu dispositivo, primero debes asegurarte de contar con las herramientas necesarias para compilar programas en C++. Este Simulador  incluye módulos de planificación, memoria y sincronización, por lo que necesitarás un entorno de desarrollo adecuado antes de ejecutarlo. A continuación, se mostraran los pasos que debes seguir para instalar, compilar y correr correctamente el programa:

*1)* Asegúrate de tener instalado un compilador C++ moderno (como g++ o clang) que soporte C++20 y la librería de threads; instálalo de esta manera
- Linux o macOS: 
  sudo apt install g++ clang
- En Windows:
  pacman -S mingw-w64-x86_64-clang

*2)* Instala Visual Studio Code y agrega la extensión C/C++ de Microsoft para compilar y ejecutar el proyecto fácilmente

*3)* Obtén el código fuente del simulador de dos formas:
- Descargalo:
   Descargo el archivo como .zip y descomprímelo
- Clona el repositorio:
  git clone https://github.com/tu-usuario/tu-repo.git

*4)* Abre la carpeta del proyecto en VS Code en Archivo,Abrir carpeta. Deberías ver los archivos main.cpp, buffer.h, sync.h, scheduler_rr.h, paging.h y demo.script; con esto comprobaras que abriste la carpeta correctamente

*5)*Compila el programa
  clang++ -std=c++20 main.cpp -pthread -o simulator

*6)*Ejecuta el programa desde la terminal
  - En Windows:
    .\simulator.exe
  - En Linux o macOS:
    ./simulator ó ./a.out
    

  
