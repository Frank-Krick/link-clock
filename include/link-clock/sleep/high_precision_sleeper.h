#ifndef LINK_CLOCK_HIGH_PRECISION_SLEEPER_H
#define LINK_CLOCK_HIGH_PRECISION_SLEEPER_H

#include <ableton/Link.hpp>
#include <chrono>

#include "windows_sleeper.h"
#include "spin_sleeper.h"

namespace link_clock {

template<unsigned int _spin_sleep_microseconds, class Sleeper, class SpinSleeper>
class HighPrecisionSleeperImplementation {
public:
    HighPrecisionSleeperImplementation() = default;

    void sleepUntil(std::chrono::microseconds time) {
        auto sleepUntil = time - _spinSleepTime;
        _sleeper.sleepUntil(sleepUntil);
        _spinSleeper.sleepUntil(time);
    };

private:
    Sleeper _sleeper;
    SpinSleeper _spinSleeper;
    std::chrono::microseconds _spinSleepTime{_spin_sleep_microseconds};
};

typedef HighPrecisionSleeperImplementation<5000, Sleeper, SpinSleeper<ableton::link::platform::Clock>> HighPrecisionSleeper;
}

#endif //LINK_CLOCK_HIGH_PRECISION_SLEEPER_H
