// scheduler_sjf.h - Segundo algoritmo de planificación
#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

struct ProcSJF {
    int pid;
    int arrival;
    int burst;
    int start = -1;
    int finish = -1;
    int wait = 0;
};

struct SJFResult {
    std::vector<ProcSJF> procs;
    double avg_wait = 0.0;
    double avg_turnaround = 0.0;
};

inline SJFResult run_sjf(std::vector<ProcSJF> input) {
    std::sort(input.begin(), input.end(), [](const ProcSJF& a, const ProcSJF& b){
        return a.arrival < b.arrival;
    });

    std::vector<bool> completed(input.size(), false);
    int t = 0;
    int done = 0;
    int n = input.size();

    while (done < n) {
        // Buscar el proceso más corto que ya llegó y no está completo
        int shortest_idx = -1;
        int shortest_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && input[i].arrival <= t) {
                if (input[i].burst < shortest_burst) {
                    shortest_burst = input[i].burst;
                    shortest_idx = i;
                }
            }
        }

        if (shortest_idx == -1) {
            // No hay procesos listos, avanzar al siguiente arrival
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!completed[i] && input[i].arrival > t) {
                    next_arrival = std::min(next_arrival, input[i].arrival);
                }
            }
            t = next_arrival;
            continue;
        }

        // Ejecutar el proceso seleccionado
        auto& p = input[shortest_idx];
        p.start = t;
        t += p.burst;
        p.finish = t;
        completed[shortest_idx] = true;
        done++;
    }

    // Calcular métricas
    double sum_wait = 0.0, sum_ta = 0.0;
    for (auto& p : input) {
        int turnaround = p.finish - p.arrival;
        p.wait = turnaround - p.burst;
        sum_wait += p.wait;
        sum_ta += turnaround;
    }

    SJFResult res;
    res.procs = std::move(input);
    res.avg_wait = n == 0 ? 0.0 : sum_wait / n;
    res.avg_turnaround = n == 0 ? 0.0 : sum_ta / n;
    return res;
}

inline void print_sjf(const SJFResult& r) {
    std::cout << "\n=== SJF (Shortest Job First) Results ===\n";
    std::cout << "PID  Arr  Burst  Start  Finish  Wait  Turnaround\n";
    std::cout << "-----------------------------------------------\n";
    for (const auto& p : r.procs) {
        int ta = p.finish - p.arrival;
        std::cout << std::setw(3) << p.pid << "  "
                  << std::setw(4) << p.arrival << "  "
                  << std::setw(5) << p.burst << "  "
                  << std::setw(5) << p.start << "  "
                  << std::setw(6) << p.finish << "  "
                  << std::setw(4) << p.wait << "  "
                  << std::setw(9) << ta << "\n";
    }
    std::cout << "-----------------------------------------------\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Avg Wait: " << r.avg_wait 
              << "  Avg Turnaround: " << r.avg_turnaround << "\n\n";
}