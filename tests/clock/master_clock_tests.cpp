#include <catch2/catch_test_macros.hpp>
#include <link-clock/clock/master_clock.h>

using namespace link_clock;
using namespace std::chrono;

TEST_CASE("Tick interval calculation") {
    SECTION("Tick intervals should add up to a beat interval") {
        auto bpm = 120.0;
        auto minute = minutes(1);
        auto intervalPerBeat = minute / bpm;
        auto tickInterval = calculate_tick_interval<4>(bpm);
        auto result = tickInterval * 4;
        REQUIRE(result == intervalPerBeat);
    }
}

TEST_CASE("Tick time calculation") {
    SECTION("Should return next tick if current time has a tick") {
        auto beatTime = microseconds(10);
        auto currentTime = microseconds(35);
        auto tickInterval = microseconds(25);
        auto result = calculate_next_tick_time(currentTime, tickInterval, beatTime);
        REQUIRE(result == microseconds(60));
    }

    SECTION("Should return the next tick if current time is before a tick") {
        auto beatTime = microseconds(10);
        auto currentTime = microseconds(65);
        auto tickInterval = microseconds(25);
        auto result = calculate_next_tick_time(currentTime, tickInterval, beatTime);
        REQUIRE(result == microseconds(85));
    }
}

double passedInTempo{0.0};

class TestIntervalCalculator {
public:
    TestIntervalCalculator() {
        passedInTempo = 0.0;
    }

    microseconds operator()(double bpm) {
        passedInTempo = bpm;
        return microseconds(10);
    }
};

microseconds passedInCurrentTime{0};
microseconds passedInTickInterval{0};
microseconds passedInBeatTime{0};

class TestNextTimeCalculator {
public:
    microseconds operator()(microseconds currentTime,
                      microseconds tickInterval,
                      microseconds beatTime) {
        passedInCurrentTime = currentTime;
        passedInBeatTime = beatTime;
        passedInTickInterval = tickInterval;
        return microseconds(33);
    }
};

TEST_CASE("Initialization") {
    SECTION("Should calculate the tick interval") {
        MasterClockImplementation<TestIntervalCalculator, TestNextTimeCalculator> masterClock(80);
        REQUIRE(passedInTempo == 80.0);
    }
}

TEST_CASE("Setting the tempo") {
    SECTION("Should recalculate the tick interval") {
        MasterClockImplementation<TestIntervalCalculator, TestNextTimeCalculator> masterClock(80);
        masterClock.setTempo(100.0);
        REQUIRE(passedInTempo == 100.0);
    }

    SECTION("Should not do anything if tempo didn't change") {
        MasterClockImplementation<TestIntervalCalculator, TestNextTimeCalculator> masterClock(80);
        masterClock.setTempo(80.0);
        REQUIRE(passedInTempo == 0.0);
    }
}

TEST_CASE("Calculate next time") {
    SECTION("Should calculate next time and pass in required input") {
        MasterClockImplementation<TestIntervalCalculator, TestNextTimeCalculator> masterClock(80);
        microseconds currentTime(3);
        microseconds beatTime(6);
        auto result = masterClock.nextTick(currentTime, beatTime);
        REQUIRE(result == microseconds(33));
        REQUIRE(currentTime == passedInCurrentTime);
        REQUIRE(beatTime == passedInBeatTime);
        REQUIRE(passedInTickInterval == microseconds(10));
    }
}