#pragma once

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;
    std::chrono::time_point<std::chrono::steady_clock> end_time;

public:
    void start() {
        start_time = std::chrono::steady_clock::now();
    }

    void stop() {
        end_time = std::chrono::steady_clock::now();
    }

    double elapsed_nanoseconds() const {
        return std::chrono::duration<double, std::nano>(end_time - start_time).count();
    }
};
