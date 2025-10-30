#pragma once
#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>

struct PagingStats {
    int frames = 0;
    int refs = 0;
    int faults = 0;
};

inline PagingStats simulate_fifo(const std::vector<int>& trace, int nframes) {
    std::unordered_set<int> in_mem;
    std::queue<int> fifo;
    PagingStats st{nframes, (int)trace.size(), 0};

    for (int page : trace) {
        if (in_mem.count(page)) {
            // hit: nada
        } else {
            st.faults++;
            if ((int)in_mem.size() < nframes) {
                in_mem.insert(page);
                fifo.push(page);
            } else if (!fifo.empty()) {
                int evict = fifo.front(); fifo.pop();
                in_mem.erase(evict);
                in_mem.insert(page);
                fifo.push(page);
            }
        }
    }
    return st;
}

inline void print_paging(const PagingStats& s) {
    double rate = s.refs == 0 ? 0.0 : (100.0 * s.faults / s.refs);
    std::cout << "Policy: FIFO\nFrames: " << s.frames
              << "\nPage faults: " << s.faults << " / " << s.refs
              << " (" << rate << "%)\n";
}
