#pragma once
#include <vector>
#include <memory>
#include <atomic>
#include <iostream>

using namespace std;

enum class ProcessState {
    NEW, READY, RUNNING, WAITING, TERMINATED
};

struct Process {
    int pid;
    ProcessState state;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int priority;

    Process(int id, int burst, int arrival = 0, int prio = 0)
        : pid(id), state(ProcessState::NEW), burst_time(burst),
          remaining_time(burst), arrival_time(arrival), priority(prio) {}
};

class ProcessManager {
private:
    std::vector<std::shared_ptr<Process>> processes;
    std::atomic<int> next_pid{1};

public:
    int create_process(int burst_time, int priority = 0) {
        int pid = next_pid++;
        auto proc = std::make_shared<Process>(pid, burst_time, 0, priority);
        proc->state = ProcessState::READY;
        processes.push_back(proc);
        return pid;
    }

    void list_processes() {
        std::cout << "\n┌───────────────────────────────────────────────────────┐\n";
        std::cout << "│              PROCESS LIST                             │\n";
        std::cout << "├─────┬──────────┬───────┬──────────┬──────────────────┤\n";
        std::cout << "│ PID │ State    │ Burst │ Remain   │ Priority         │\n";
        std::cout << "├─────┼──────────┼───────┼──────────┼──────────────────┤\n";

        for (const auto& p : processes) {
            std::cout << "│ " << std::setw(3) << p->pid << " │ ";
            
            std::string state_str;
            switch(p->state) {
                case ProcessState::NEW: state_str = "NEW"; break;
                case ProcessState::READY: state_str = "READY"; break;
                case ProcessState::RUNNING: state_str = "RUNNING"; break;
                case ProcessState::WAITING: state_str = "WAITING"; break;
                case ProcessState::TERMINATED: state_str = "TERM"; break;
            }
            
            std::cout << std::setw(8) << std::left << state_str << std::right << " │ "
                     << std::setw(5) << p->burst_time << " │ "
                     << std::setw(8) << p->remaining_time << " │ "
                     << std::setw(16) << p->priority << " │\n";
        }
        std::cout << "└─────┴──────────┴───────┴──────────┴──────────────────┘\n\n";
    }

    bool kill_process(int pid) {
        for (auto& p : processes) {
            if (p->pid == pid && p->state != ProcessState::TERMINATED) {
                p->state = ProcessState::TERMINATED;
                p->remaining_time = 0;
                return true;
            }
        }
        return false;
    }

    std::vector<std::shared_ptr<Process>> get_processes() {
        return processes;
    }
};