cmake_minimum_required(VERSION 3.15)
project(DataStructsAndAlgos LANGUAGES CXX)

# ——————————————————————————————————————————————————————————
# 1) C++ Standard
#——————————————————————————————————————————————————————————
set(CMAKE_CXX_STANDARD      17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS     OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wpedantic -g")

# ——————————————————————————————————————————————————————————
# 2) Header‑only library target
#——————————————————————————————————————————————————————————
add_library(ds INTERFACE)

# Tell users of ds where to find the headers
target_include_directories(ds INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# ——————————————————————————————————————————————————————————
# 3) Enable CTest
#——————————————————————————————————————————————————————————
enable_testing()

# ——————————————————————————————————————————————————————————
# 4) Auto‑discover and build all tests in tests/*.cpp
#——————————————————————————————————————————————————————————
file(GLOB TEST_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

foreach(test_src IN LISTS TEST_SRCS)
  get_filename_component(test_name ${test_src} NAME_WE)
  add_executable(${test_name} ${test_src})
  target_link_libraries(${test_name} PRIVATE ds)
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# ——————————————————————————————————————————————————————————
# 5) (Optional) Discover demos in examples/*.cpp
#——————————————————————————————————————————————————————————
file(GLOB EX_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

foreach(ex_src IN LISTS EX_SRCS)
  get_filename_component(ex_name ${ex_src} NAME_WE)
  add_executable(${ex_name} ${ex_src})
  target_link_libraries(${ex_name} PRIVATE ds)
endforeach()

