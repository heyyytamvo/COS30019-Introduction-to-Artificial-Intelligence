#ifndef CLOCK_H
#define CLOCK_H
#include <iostream>
#include <thread>   
#include <chrono>

using namespace std;

class Clock{
    private:
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;

    public:
    /// Constructor
    Clock(){
        start = std::chrono::high_resolution_clock::now();
    }

    void endClock(){
        end = std::chrono::high_resolution_clock::now();
    }

    void ExecutingTime(){
        std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        cout << endl << "The Agent need " << duration.count() << "ns (NanoSeconds) to findout the solution\n";
    }

};
#endif