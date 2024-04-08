cmake_minimum_required(VERSION 3.28)
project(lab9)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab9 main.cpp
        lib/drop.h
        lib/filter.h
        lib/keys.h
        lib/take.h
        lib/values.h
        lib/reverse.h
        lib/transform.h
        tests/adapters_tests.cpp)
