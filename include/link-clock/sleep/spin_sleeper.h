#ifndef LINK_CLOCK_SPIN_SLEEPER_H
#define LINK_CLOCK_SPIN_SLEEPER_H

#include <chrono>

namespace link_clock {

template<class Clock>
class SpinSleeper {
public:
    void sleepUntil(std::chrono::microseconds time) {
        while (_clock.micros() < time) {}
    };

private:
    Clock _clock;
};

} // namespace link_clock

#endif //LINK_CLOCK_SPIN_SLEEPER_H
