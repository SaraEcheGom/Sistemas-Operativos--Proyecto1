#pragma once
#include <vector>
#include <unordered_map>
#include <list>
#include <iostream>

struct LRUStats {
    int frames = 0;
    int refs = 0;
    int faults = 0;
};

inline LRUStats simulate_lru(const std::vector<int>& trace, int nframes) {
    std::unordered_map<int, std::list<int>::iterator> page_map;
    std::list<int> lru_list; // más reciente al frente
    LRUStats st{nframes, (int)trace.size(), 0};

    for (int page : trace) {
        auto it = page_map.find(page);
        
        if (it != page_map.end()) {
            // HIT: mover al frente
            lru_list.erase(it->second);
            lru_list.push_front(page);
            page_map[page] = lru_list.begin();
        } else {
            // MISS
            st.faults++;
            
            if ((int)page_map.size() < nframes) {
                // Hay espacio
                lru_list.push_front(page);
                page_map[page] = lru_list.begin();
            } else {
                // Reemplazar el LRU (último de la lista)
                int evict = lru_list.back();
                lru_list.pop_back();
                page_map.erase(evict);
                
                lru_list.push_front(page);
                page_map[page] = lru_list.begin();
            }
        }
    }
    return st;
}

inline void print_lru(const LRUStats& s) {
    double rate = s.refs == 0 ? 0.0 : (100.0 * s.faults / s.refs);
    std::cout << "Policy: LRU\nFrames: " << s.frames
              << "\nPage faults: " << s.faults << " / " << s.refs
              << " (" << rate << "%)\n";
}
