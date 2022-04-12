add_library(link-clock-lib "")

target_sources(link-clock-lib
  PUBLIC
    ../include/link-clock/clock/master_clock.h
    ../include/link-clock/sleep/high_precision_sleeper.h
    ../include/link-clock/sleep/spin_sleeper.h
  PRIVATE
    sleep/high_precision_sleeper.cpp
    sleep/spin_sleeper.cpp
    clock/master_clock.cpp)

if(WIN32)
  target_sources(link-clock-lib
    PUBLIC
      ../include/link-clock/sleep/windows_sleeper.h
    PRIVATE
      sleep/windows_sleeper.cpp)
endif()

target_link_libraries(link-clock-lib PUBLIC Ableton::Link)

target_include_directories(link-clock-lib PUBLIC ../include)

add_executable(link-clock
  main.cpp)

find_library(winmm winmm)

target_link_libraries(link-clock
  PRIVATE winmm
  PRIVATE link-clock-lib)
