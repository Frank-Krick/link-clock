#ifndef LINK_CLOCK_WINDOWS_SLEEPER_H
#define LINK_CLOCK_WINDOWS_SLEEPER_H

#include <chrono>
#include <windows.h>
#include <timeapi.h>

namespace link_clock {

class Sleeper {
public:
    Sleeper() {
        _waitableTimer = CreateWaitableTimer(nullptr, TRUE, nullptr);
        timeBeginPeriod(5);
    }

    ~Sleeper() {
        CloseHandle(_waitableTimer);
        timeEndPeriod(5);
    }

    void sleepUntil(std::chrono::microseconds time);

private:
    HANDLE _waitableTimer;
};

}
#endif //LINK_CLOCK_WINDOWS_SLEEPER_H
