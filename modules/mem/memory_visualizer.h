#pragma once
#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <iomanip>

struct Frame {
    int id;
    int page = -1; // -1 = vacío
    int last_access = 0;
};

class MemoryVisualizer {
private:
    std::vector<Frame> frames;
    int access_count = 0;

public:
    MemoryVisualizer(int nframes) {
        frames.resize(nframes);
        for (int i = 0; i < nframes; i++) {
            frames[i].id = i;
        }
    }

    void simulate_trace_fifo(const std::vector<int>& trace) {
        std::unordered_set<int> in_mem;
        std::queue<int> fifo_order;
        access_count = 0;

        std::cout << "\n FIFO Memory Trace \n";
        std::cout << "Access | Page | Action\n";
    
        for (int page : trace) {
            access_count++;
            
            if (in_mem.count(page)) {
                std::cout << std::setw(6) << access_count << " | " 
                         << std::setw(4) << page << " | HIT\n";
            } else {
                std::cout << std::setw(6) << access_count << " | " 
                         << std::setw(4) << page << " | FAULT - ";
                
                if ((int)in_mem.size() < (int)frames.size()) {
                    // Cargar en frame libre
                    int free_idx = in_mem.size();
                    frames[free_idx].page = page;
                    frames[free_idx].last_access = access_count;
                    in_mem.insert(page);
                    fifo_order.push(free_idx);
                    std::cout << "Loaded to Frame " << free_idx << "\n";
                } else {
                    // Reemplazar FIFO
                    int victim_idx = fifo_order.front();
                    fifo_order.pop();
                    int old_page = frames[victim_idx].page;
                    
                    in_mem.erase(old_page);
                    frames[victim_idx].page = page;
                    frames[victim_idx].last_access = access_count;
                    in_mem.insert(page);
                    fifo_order.push(victim_idx);
                    
                    std::cout << "Replaced Page " << old_page 
                             << " in Frame " << victim_idx << "\n";
                }
            }
        }
        display_frames();
    }

    void display_frames() {
        std::cout << "\n┌─────────────────────────────┐\n";
        std::cout << "│   MEMORY FRAMES STATUS      │\n";
        std::cout << "├──────┬──────┬───────────────┤\n";
        std::cout << "│ Frame│ Page │ Last Access   │\n";
        std::cout << "├──────┼──────┼───────────────┤\n";
        
        for (const auto& f : frames) {
            std::cout << "│ " << std::setw(4) << f.id << " │ ";
            if (f.page == -1) {
                std::cout << "---- │     ----      │\n";
            } else {
                std::cout << std::setw(4) << f.page << " │ "
                         << std::setw(13) << f.last_access << " │\n";
            }
        }
        std::cout << "└──────┴──────┴───────────────┘\n\n";
    }
};