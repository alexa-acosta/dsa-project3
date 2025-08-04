#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>

// reads CSV file into a vector of strings
std::vector<std::string> read_csv(const std::string& filename);

// measures time
class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

public:
    void start();
    void stop();
    long long get_duration_microseconds();
};

#endif