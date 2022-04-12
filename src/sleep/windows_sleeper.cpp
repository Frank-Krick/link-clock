#include <link-clock/sleep/windows_sleeper.h>

using namespace link_clock;
using namespace std::chrono;

void Sleeper::sleepUntil(microseconds time) {
    LARGE_INTEGER waitInterval;
    auto fileTime = duration_cast<nanoseconds>(time) / 100;
    waitInterval.QuadPart = fileTime.count();
    SetWaitableTimer(_waitableTimer, &waitInterval, 0, nullptr, nullptr, FALSE);
    WaitForSingleObject(_waitableTimer, INFINITE);
}
