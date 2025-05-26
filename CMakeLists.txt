cmake_minimum_required(VERSION 3.15)
project(DataStructsAndAlgos LANGUAGES CXX)

# ——————————————————————————————————————————————————————————
# 1) C++ Standard
# ——————————————————————————————————————————————————————————
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG
    "-Wall -Wextra -Wpedantic -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -g"
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ——————————————————————————————————————————————————————————
# 2) Header‑only library target
# ——————————————————————————————————————————————————————————
add_library(ds INTERFACE)

# Tell users of ds where to find the headers
target_include_directories(
  ds INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# ----- FETCH SFML -----

# FetchContent SFML
include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.1
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFML)

# ——————————————————————————————————————————————————————————
# 3) Enable CTest
# ——————————————————————————————————————————————————————————
enable_testing()

# ——————————————————————————————————————————————————————————
# 4) Auto‑discover and build all tests in tests/*.cpp
# ——————————————————————————————————————————————————————————
file(GLOB TEST_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

foreach(test_src IN LISTS TEST_SRCS)
  get_filename_component(test_name ${test_src} NAME_WE)
  add_executable(${test_name} ${test_src})
  target_link_libraries(${test_name} PRIVATE ds SFML::Graphics)
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# file(GLOB EX_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#
# foreach(ex_src IN LISTS EX_SRCS) get_filename_component(ex_name ${ex_src}
# NAME_WE) add_executable(${ex_name} ${ex_src}) target_link_libraries(${ex_name}
# PRIVATE ds SFML::Graphics) endforeach()

# MAIN EXECUTABLES
file(GLOB LIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/*.cpp")

add_executable(test_sfml src/test_sfml.cpp ${LIB_SRC})
target_include_directories(test_sfml PRIVATE src/lib)
target_link_libraries(test_sfml PRIVATE ds SFML::Graphics)
