cmake_minimum_required(VERSION 3.22)
project(tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set  ( core_files
        arguments.cpp
        headers/arguments.hpp
        window.cpp
        headers/window.hpp
        tetris.cpp
        headers/tetris.hpp
        headers/constants.hpp
        block.cpp
        headers/block.hpp
)

set  ( test_files
        arguments.cpp
        headers/arguments.hpp
        window.cpp
        headers/window.hpp
        tetris.cpp
        headers/tetris.hpp
        headers/constants.hpp
        block.cpp
        headers/block.hpp
        catch.cpp
        headers/catch.hpp
)

add_executable(
        tetris
        main.cpp
        ${core_files}
)

add_executable(
        tests
        tests.cpp
        ${test_files}
)

enable_testing()
add_test(NAME tests COMMAND tests)

#target_link_libraries(tetris PRIVATE Catch2::Catch2)
