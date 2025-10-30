#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <sstream>
#include "modules/io/buffer.h"
#include "modules/mem/paging.h"
#include "modules/mem/paging_lru.h"
#include "modules/mem/scheduler_rr.h"
#include "modules/cpu/scheduler_sjf.h"
#include "modules/io/sync.h"
#include "modules/mem/memory_visualizer.h"
#include "modules/cpu/process_manager.h"

SharedBuffer buffer(5);
ProcessManager procMgr;
std::atomic<int> item_counter{0};

void print_help() {
    std::cout << R"(

        OS SIMULATOR - Comandos Disponibles                 


GESTIÓN DE PROCESOS:
  new <burst> [priority]  - Crear nuevo proceso
  ps                      - Listar todos los procesos
  kill <pid>              - Terminar proceso

PLANIFICACIÓN:
  rrdemo [quantum]        - Demo Round Robin
  sjfdemo                 - Demo SJF (Shortest Job First)

MEMORIA:
  memdemo <frames>        - Demo FIFO paging
  lrudemo <frames>        - Demo LRU paging
  memvis <frames>         - Visualización detallada FIFO

SINCRONIZACIÓN:
  produce                 - Producir item
  consume                 - Consumir item
  stat                    - Estado del buffer

UTILIDADES:
  runscript <file>        - Ejecutar script
  help                    - Mostrar esta ayuda
  exit                    - Salir

)";
}

void cli() {
    std::string command;

    std::cout << "     SIMULADOR DE SISTEMA OPERATIVO       \n";
    std::cout << "\n\n";
    std::cout << "Escribe 'help' para ver comandos disponibles\n\n";

    while (true) {
        std::cout << "OS> ";
        std::cin >> command;

        if (command == "exit") {
            std::cout << "Saliendo del simulador...\n";
            break;
        }
        else if (command == "help") {
            print_help();
        }
        else if (command == "new") {
            int burst, priority = 0;
            std::cin >> burst;
            if (std::cin.peek() != '\n') {
                std::cin >> priority;
            }
            int pid = procMgr.create_process(burst, priority);
            std::cout << "✓ Proceso " << pid << " creado (burst=" << burst << ")\n";
        }
        else if (command == "ps") {
            procMgr.list_processes();
        }
        else if (command == "kill") {
            int pid;
            std::cin >> pid;
            if (procMgr.kill_process(pid)) {
                std::cout << "✓ Proceso " << pid << " terminado\n";
            } else {
                std::cout << "✗ Proceso " << pid << " no encontrado o ya terminado\n";
            }
        }
        else if (command == "produce") {
            int item = ++item_counter;
            std::thread([item]() { buffer.produce(item); }).detach();
        }
        else if (command == "consume") {
            std::thread([]() { buffer.consume(); }).detach();
        }
        else if (command == "stat") {
            buffer.status();
        }
        else if (command == "rrdemo") {
            int q = 3;
            if (std::cin.peek() != '\n') {
                std::cin >> q;
            }
            std::vector<Proc> procs = {
                {1, 0, 10}, {2, 1, 5}, {3, 2, 8}, {4, 3, 3}
            };
            std::cout << "\n=== Round Robin Demo (Quantum=" << q << ") ===\n";
            auto res = run_rr(procs, q);
            print_rr(res);
        }
        else if (command == "sjfdemo") {
            std::vector<ProcSJF> procs = {
                {1, 0, 10}, {2, 1, 5}, {3, 2, 8}, {4, 3, 3}
            };
            auto res = run_sjf(procs);
            print_sjf(res);
        }
        else if (command == "memdemo") {
            int frames = 3;
            if (std::cin.peek() != '\n') {
                std::cin >> frames;
            }
            std::vector<int> trace = {1,2,3,4,1,2,5,1,2,3,4,5};
            std::cout << "\n=== FIFO Paging Demo ===\n";
            std::cout << "Trace: ";
            for (int p : trace) std::cout << p << " ";
            std::cout << "\n";
            auto s = simulate_fifo(trace, frames);
            print_paging(s);
        }
        else if (command == "lrudemo") {
            int frames = 3;
            if (std::cin.peek() != '\n') {
                std::cin >> frames;
            }
            std::vector<int> trace = {1,2,3,4,1,2,5,1,2,3,4,5};
            std::cout << "\n=== LRU Paging Demo ===\n";
            std::cout << "Trace: ";
            for (int p : trace) std::cout << p << " ";
            std::cout << "\n";
            auto s = simulate_lru(trace, frames);
            print_lru(s);
        }
        else if (command == "memvis") {
            int frames = 4;
            if (std::cin.peek() != '\n') {
                std::cin >> frames;
            }
            std::vector<int> trace = {1,2,3,4,1,2,5,1,2,3,4,5};
            MemoryVisualizer vis(frames);
            vis.simulate_trace_fifo(trace);
        }
        else if (command == "runscript") {
            std::string path;
            std::cin >> path;
            std::ifstream f(path);
            if (!f) {
                std::cout << "✗ No se pudo abrir " << path << "\n";
            } else {
                std::string cmd;
                std::cout << ">> Ejecutando script: " << path << "\n";
                while (f >> cmd) {
                    std::cout << "> " << cmd << "\n";
                    // Procesar comandos del script...
                    if (cmd == "exit") break;
                }
            }
        }
        else {
            std::cout << "✗ Comando desconocido: " << command << "\n";
            std::cout << "  Escribe 'help' para ver comandos disponibles\n";
        }

        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

int main() {
    cli();
    return 0;
}
