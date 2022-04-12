cmake_minimum_required(VERSION 3.23)

project(link-clock)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

include(external/link/AbletonLinkConfig.cmake)
add_subdirectory(external/fr-musp)
add_subdirectory(src)
add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 20)
