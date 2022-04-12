#include <iostream>
#include <thread>
#include <atomic>
#include <ableton/Link.hpp>
#include <link-clock/sleep/high_precision_sleeper.h>

using namespace link_clock;
using namespace ableton;
using namespace std;
using namespace std::chrono;

struct State {
    explicit State(): link(120) {}

    atomic<bool> enabled {true};
    Link link;
};

void clockFunction(State& state) {
    HighPrecisionSleeper sleeper;
    auto last = state.link.clock().micros();
    while (state.enabled) {
        sleeper.sleepUntil(last + microseconds(10000));
        auto current = state.link.clock().micros();
        auto diff = current - last;
        last = current;
        cout << (duration_cast<milliseconds>(diff)).count() << " ";
    }
}

int main(int argc, char *argv[]) {
    cout << "Starting link clock" << endl;
    State state;
    state.link.enable(true);
    state.link.enableStartStopSync(true);
    thread clockThread(clockFunction, ref(state));
    while (state.enabled) {
        auto stillEnabled = true;
        cin >> stillEnabled;
        state.enabled = false;
    }
    clockThread.join();
    return 0;
}
