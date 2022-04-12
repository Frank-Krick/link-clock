add_executable(link_clock_tests
  sleep/high_precision_sleeper_tests.cpp
  sleep/spin_sleeper_tests.cpp
  clock/master_clock_tests.cpp)

target_link_libraries(link_clock_tests
  PRIVATE link-clock-lib
  PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
