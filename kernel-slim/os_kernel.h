#pragma once

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "../modules/cpu/scheduler_sjf.h"
#include "../modules/mem/paging.h"
#include "../modules/io/buffer.h"

// Forward declarations
struct Proc;
struct PagingStats;

enum class SchedulerType {
    ROUND_ROBIN,
    SJF
};

enum class PagingAlgorithm {
    FIFO,
    LRU
};

class OSKernel {
private:
    // Configuración del sistema
    int quantum_rr;
    int memory_frames;
    int buffer_capacity;
    
    // Estado del sistema
    SchedulerType current_scheduler;
    PagingAlgorithm current_paging;
    int next_pid;
    
    // Buffer compartido para sincronización
    std::unique_ptr<SharedBuffer> shared_buffer;
    
public:
    OSKernel(int quantum = 4, int frames = 8, int buf_cap = 5)
        : quantum_rr(quantum),
          memory_frames(frames),
          buffer_capacity(buf_cap),
          current_scheduler(SchedulerType::ROUND_ROBIN),
          current_paging(PagingAlgorithm::FIFO),
          next_pid(1) {
        
        shared_buffer = std::make_unique<SharedBuffer>(buffer_capacity);
    }
    
    void set_quantum(int q) { 
        quantum_rr = q; 
        std::cout << "✓ Quantum actualizado a " << q << "\n";
    }
    
    void set_memory_frames(int f) { 
        memory_frames = f; 
        std::cout << "✓ Frames de memoria actualizados a " << f << "\n";
    }
    
    void set_scheduler(SchedulerType type) {
        current_scheduler = type;
        std::string name = (type == SchedulerType::ROUND_ROBIN) ? "Round Robin" : "SJF";
        std::cout << "✓ Planificador cambiado a " << name << "\n";
    }
    
    void set_paging_algorithm(PagingAlgorithm algo) {
        current_paging = algo;
        std::string name = (algo == PagingAlgorithm::FIFO) ? "FIFO" : "LRU";
        std::cout << "✓ Algoritmo de paginación cambiado a " << name << "\n";
    }
    
    // Información del Sistema 
    
    void print_system_info() {
        std::cout << "\n";
        std::cout << "           INFORMACIÓN DEL SISTEMA                     \n";
        std::cout << " Planificador CPU:    ";
        if (current_scheduler == SchedulerType::ROUND_ROBIN) {
            std::cout << "Round Robin (Q=" << quantum_rr << ")";
        } else {
            std::cout << "SJF (Non-preemptive)";
        }
        std::cout << std::string(27 - (current_scheduler == SchedulerType::ROUND_ROBIN ? 19 + std::to_string(quantum_rr).length() : 22), ' ') << "║\n";
        
        std::cout << " Algoritmo Memoria:   ";
        std::cout << (current_paging == PagingAlgorithm::FIFO ? "FIFO" : "LRU ");
        std::cout << std::string(31, ' ') << "║\n";
        
        std::cout << " Frames Memoria:      " << memory_frames;
        std::cout << std::string(33 - std::to_string(memory_frames).length(), ' ') << "\n";
        
        std::cout << " Capacidad Buffer:    " << buffer_capacity;
        std::cout << std::string(33 - std::to_string(buffer_capacity).length(), ' ') << "\n";

    
    }
    
    // Acceso a componentes 
    
    SharedBuffer* get_buffer() { 
        return shared_buffer.get(); 
    }
    
    int get_quantum() const { return quantum_rr; }
    int get_memory_frames() const { return memory_frames; }
    SchedulerType get_scheduler_type() const { return current_scheduler; }
    PagingAlgorithm get_paging_algorithm() const { return current_paging; }
    
    //  Utilidades
    
    int allocate_pid() {
        return next_pid++;
    }
    
    void reset() {
        next_pid = 1;
        std::cout << "✓ Sistema reiniciado\n";
    }
};