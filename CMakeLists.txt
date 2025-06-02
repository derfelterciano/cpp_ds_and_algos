cmake_minimum_required(VERSION 3.15)
project(MazeDataStructsAndAlgos LANGUAGES CXX)

# ——————————————————————————————————————————————————————————
# 1) C++ Standard
# ——————————————————————————————————————————————————————————
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# compiler specific options if(MSVC AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
# set(CMAKE_CXX_FLAGS_DEBUG "-Weverything -Wno-c++98-compat
# -Wno-c++98-compat-pedantic -g") elseif(MSVC) set(CMAKE_CXX_FLAGS_DEBUG "/W4
# /Zi") else() set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wpedantic -Weverything
# -Wno-c++98-compat -Wno-c++98-compat-pedantic -g" ) endif()

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

  if(MSVC)
    target_compile_options(${test_name} PRIVATE $<$<CONFIG:DEBUG>: /W4 /Zi>)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(
      ${test_name} PRIVATE $<$<CONFIG:DEBUG>: -Weverything -Wno-c++98-compat
                           -Wno-c++98-compat-pedantic -g>)
  else()
    target_compile_options(
      ${test_name}
      PRIVATE $<$<CONFIG:DEBUG>:
              -Wall
              -Wextra
              -Wpedantic
              -Weverything
              -Wno-c++98-compat
              -Wno-c++98-compat-pedantic
              -g>)
  endif()

  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# file(GLOB EX_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#
# foreach(ex_src IN LISTS EX_SRCS) get_filename_component(ex_name ${ex_src}
# NAME_WE) add_executable(${ex_name} ${ex_src}) target_link_libraries(${ex_name}
# PRIVATE ds SFML::Graphics) endforeach()

# MAIN EXECUTABLES
file(GLOB LIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/*.cpp")

# helper for adding warning flags during debug
macro(ADD_COMPILE_OPTIONS_PER_OS target)
  if(MSVC)
    target_compile_options(${target} PRIVATE $<$<CONFIG:DEBUG>: /W4 /Zi>)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(
      ${target} PRIVATE $<$<CONFIG:DEBUG>: -Weverything -Wno-c++98-compat
                        -Wno-c++98-compat-pedantic -g>)
  else()
    target_compile_options(
      ${target}
      PRIVATE $<$<CONFIG:DEBUG>:
              -Wall
              -Wextra
              -Wpedantic
              -Weverything
              -Wno-c++98-compat
              -Wno-c++98-compat-pedantic
              -g>)
  endif()
endmacro()

add_executable(test_sfml src/test_sfml.cpp ${LIB_SRC})
target_include_directories(test_sfml PRIVATE src/lib)
target_link_libraries(test_sfml PRIVATE ds SFML::Graphics)
add_compile_options_per_os(test_sfml)

add_executable(maze src/maze.cpp ${LIB_SRC})
target_include_directories(maze PRIVATE src/lib)
target_link_libraries(maze PRIVATE ds SFML::Graphics)
add_compile_options_per_os(maze)

add_executable(test_maze src/test_maze.cpp ${LIB_SRC})
target_include_directories(test_maze PRIVATE src/lib)
target_link_libraries(test_maze PRIVATE ds SFML::Graphics)
add_compile_options_per_os(test_maze)
