#include <link-clock/clock/master_clock.h>

using namespace link_clock;
using namespace std::chrono;

microseconds link_clock::calculate_next_tick_time(microseconds currentTime, microseconds tickInterval, microseconds beatTime) {
    auto nextTick = beatTime;
    while (nextTick <= currentTime) {
        nextTick += tickInterval;
    }
    return nextTick;
}
