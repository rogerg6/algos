#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <sys/time.h>
#include <utility>
#include <vector>

class Timer {
private:
    struct timeval                             _start;
    std::vector<std::pair<std::string, float>> tc;
    float                                      total_ms = 0;

public:
    friend std::ostream &operator<<(std::ostream &os, const Timer &t) {
        auto tc = t.tc;
        for (size_t i = 0; i < tc.size(); i++) {
            os << tc[i].first << ": " << tc[i].second << " ms, ";
        }
        return os;
    }
    /** 定时器开始 */
    void Start();
    /** 定时器掐表，记录当前时间距离start or 上次stop时间 */
    void Stop(const std::string &msg);
    /** 定时器本轮计时总时间 */
    float Total();
    /** 清除本次start所有的时间记录 */
    void Clear();
};

#endif
