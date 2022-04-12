#ifndef LINK_CLOCK_MASTER_CLOCK_H
#define LINK_CLOCK_MASTER_CLOCK_H

#include <chrono>

namespace link_clock {

template<size_t _resolution_ppqn>
std::chrono::microseconds calculate_tick_interval(double bpm) {
    auto beatInterval = std::chrono::minutes(1) / bpm;
    auto tickInterval = beatInterval / (double) _resolution_ppqn;
    return std::chrono::duration_cast<std::chrono::microseconds>(tickInterval);
}

template<size_t _resolution_ppqn>
class TickIntervalCalculator {
public:
   std::chrono::microseconds operator()(double tempoBpm) {
       return calculate_tick_interval<_resolution_ppqn>(tempoBpm);
   }
};

std::chrono::microseconds
calculate_next_tick_time(std::chrono::microseconds currentTime,
                         std::chrono::microseconds tickInterval,
                         std::chrono::microseconds beatTime);

class TickTimeCalculator {
public:
    std::chrono::microseconds operator()(std::chrono::microseconds currentTime,
                                         std::chrono::microseconds tickInterval,
                                         std::chrono::microseconds beatTime) {
        return calculate_next_tick_time(currentTime, tickInterval, beatTime);
    }
};

template<class TickIntervalCalculator, class NextTickCalculator>
class MasterClockImplementation {
public:
    explicit MasterClockImplementation(double tempoBpm):
        _tempoBpm(tempoBpm),
        _tickInterval(_tickIntervalCalculator(tempoBpm)) {}

    std::chrono::microseconds nextTick(
        std::chrono::microseconds currentTime,
        std::chrono::microseconds beatTime) {
        return _nextTickTimeCalculator(currentTime, _tickInterval, beatTime);
    }

    void setTempo(double tempoBpm) {
        if (tempoBpm == _tempoBpm) return;
        _tempoBpm = tempoBpm;
        _tickInterval = _tickIntervalCalculator(tempoBpm);
    }

private:
    double _tempoBpm;
    std::chrono::microseconds _tickInterval;
    TickIntervalCalculator _tickIntervalCalculator;
    NextTickCalculator _nextTickTimeCalculator;
};

typedef MasterClockImplementation<TickIntervalCalculator<24>, TickTimeCalculator> MasterClock;

} // namespace link_clock

#endif //LINK_CLOCK_MASTER_CLOCK_H
