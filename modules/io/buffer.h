#pragma once
#include <queue>
#include <iostream>
#include "sync.h"

class SharedBuffer {
private:
    std::queue<int> buffer;
    const unsigned int capacity;

    std::mutex mtx;
    Semaphore empty;
    Semaphore full;

public:
    SharedBuffer(unsigned int cap) : capacity(cap), empty(cap), full(0) {}

    void produce(int item) {
        empty.wait();              // espera espacio libre
        {
            std::unique_lock<std::mutex> lock(mtx);
            buffer.push(item);
            std::cout << "Producido: " << item << "\n";
        }
        full.signal();             // hay un ítem nuevo
    }

    void consume() {
        full.wait();               // espera que haya algo
        int item;
        {
            std::unique_lock<std::mutex> lock(mtx);
            item = buffer.front();
            buffer.pop();
            std::cout << "Consumido: " << item << "\n";
        }
        empty.signal();            // libera espacio
    }

    void status() {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "Estado del buffer: " << buffer.size()
                  << "/" << capacity << " elementos.\n";
    }
};
