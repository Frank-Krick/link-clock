#include <catch2/catch_test_macros.hpp>
#include <link-clock/sleep/spin_sleeper.h>

using namespace link_clock;
using namespace std::chrono;

unsigned int callCount{0};

class TestClock {
public:
    microseconds micros() {
        ++callCount;
        return ++start;
    }

    microseconds start{0};
};

TEST_CASE("The spin sleeper") {
    SECTION("Should call the clock until the wait time is reached") {
        SpinSleeper<TestClock> spinSleeper;
        spinSleeper.sleepUntil(microseconds(400));
        REQUIRE(callCount == 400);
    }
}