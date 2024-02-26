
#include "timer.h"
using namespace std;

void Timer::Start() {
    gettimeofday(&_start, NULL);
}

void Timer::Stop(const string &msg) {
    float          time = 0;
    struct timeval t;
    gettimeofday(&t, NULL);
    time   = (1000000 * (t.tv_sec - _start.tv_sec) + t.tv_usec - _start.tv_usec) / (1000.0);   // ms
    _start = t;

    tc.push_back(make_pair(msg, time));
    total_ms += time;
}


void Timer::Clear() {
    total_ms = 0;
    tc.clear();
}


float Timer::Total() {
    return total_ms;
}