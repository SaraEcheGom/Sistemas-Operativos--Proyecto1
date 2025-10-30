#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <algorithm>

struct Proc {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int start = -1;
    int finish = -1;
    int wait = 0;
};

struct RRResult {
    std::vector<Proc> procs;
    double avg_wait = 0.0;
    double avg_turnaround = 0.0;
    int last_time = 0;
};

inline RRResult run_rr(std::vector<Proc> input, int quantum) {
   
    std::sort(input.begin(), input.end(), [](const Proc& a, const Proc& b){
        return a.arrival < b.arrival || (a.arrival == b.arrival && a.pid < b.pid);
    });
    for (auto &p : input) p.remaining = p.burst;

    std::queue<int> ready; 
    int t = 0, i = 0;
    auto push_arrivals = [&](int until){
        while (i < (int)input.size() && input[i].arrival <= until) {
            ready.push(i++);
        }
    };
    push_arrivals(0);

  
    if (ready.empty() && !input.empty()) {
        t = input[0].arrival;
        push_arrivals(t);
    }

    while (!ready.empty()) {
        int idx = ready.front(); ready.pop();
        auto &p = input[idx];

        if (p.start == -1) p.start = t;

        int slice = std::min(quantum, p.remaining);
     
        int t_before = t;
        t += slice;
        p.remaining -= slice;

       
        push_arrivals(t);

        if (p.remaining > 0) {
           
            ready.push(idx);
        } else {
            p.finish = t;
        }

       
        if (ready.empty() && i < (int)input.size()) {
            t = std::max(t, input[i].arrival);
            push_arrivals(t);
        }
    }

   
    double sum_wait = 0.0, sum_ta = 0.0;
    for (auto &p : input) {
        int turnaround = p.finish - p.arrival;
        int wait = turnaround - p.burst;
        p.wait = wait;
        sum_wait += wait;
        sum_ta += turnaround;
    }
    RRResult res;
    res.procs = std::move(input);
    res.avg_wait = res.procs.empty()? 0.0 : sum_wait / res.procs.size();
    res.avg_turnaround = res.procs.empty()? 0.0 : sum_ta / res.procs.size();
    res.last_time = t;
    return res;
}

inline void print_rr(const RRResult& r) {
    std::cout << "PID  Arr  Burst  Start  Finish  Wait  Turnaround\n";
    std::cout << "-----------------------------------------------\n";
    for (const auto &p : r.procs) {
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
    std::cout << "Promedios -> Wait: " << r.avg_wait
              << "  Turnaround: " << r.avg_turnaround << "\n";
}
