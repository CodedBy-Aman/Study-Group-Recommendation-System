# CMakeLists.txt
# ye file batati hai CMake ko ki C++ code kaise compile karna hai
# hum ek standalone executable bana rahe hain jiska naam hoga matcher_engine
# Java backend isko subprocess ki tarah call karega
# student data JSON stdin se dega, result JSON stdout se lega

cmake_minimum_required(VERSION 3.15)
project(StudyGroupMatcher)

# C++17 use kar rahe hain — structured bindings ke liye zaroori hai
# jaise auto& [key, val] wala syntax
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# local headers include karo — matcher.hpp, bid_calculator.hpp
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# nlohmann json library include karo — JSON parse karne ke liye
# ye ek single header file hai, algorithm/lib/ mein rakho
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# ye sab cpp files milke ek executable banayenge
add_executable(matcher_engine
    main.cpp        # stdin se JSON padh, stdout mein result do
    matcher.cpp     # Gale-Shapley loop — Amanpreet
    bid_calculator.cpp  # scoring formula — Ayush
)

# compiled executable project root mein jayega
# taaki Java backend aasani se ./matcher_engine call kar sake
set_target_properties(matcher_engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/..
)