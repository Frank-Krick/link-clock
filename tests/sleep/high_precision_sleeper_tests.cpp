#include <catch2/catch_test_macros.hpp>
#include <link-clock/sleep/high_precision_sleeper.h>

using namespace link_clock;
using namespace std::chrono;

microseconds testClockAfterSleep{0};

class TestClock {
public:
    microseconds micros() {
        if (testClockAfterSleep != start) {
            start = testClockAfterSleep;
        }

        return start++;
    }

    microseconds start{0};
};

microseconds calledForTime{0};

class TestSleeper {
public:
    void sleepUntil(microseconds time) {
        calledForTime = time;
        testClockAfterSleep = time;
    }
};

microseconds spinClockCalledForTime{0};

class TestSpinSleeper {
public:
    void sleepUntil(microseconds time) {
        spinClockCalledForTime = time;
    }
};

TEST_CASE("The high precision sleeper") {
    SECTION("Should sleep for 5ms while spinning and using the sleeper for the rest") {
        microseconds sleepUntil(45);
        HighPrecisionSleeperImplementation<5, TestSleeper, TestSpinSleeper> sleeper;
        sleeper.sleepUntil(sleepUntil);
        REQUIRE(calledForTime == microseconds(40));
        REQUIRE(spinClockCalledForTime == microseconds(sleepUntil));
    }
}
