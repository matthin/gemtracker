cmake_minimum_required(VERSION 2.8)
project(GemTracker CXX)

add_subdirectory(Source)
include_directories(Source)

add_library(
    GemTrackerLibrary
    STATIC
    ${SourceFiles}
)
add_executable(GemTracker Source/Main.cc)
target_link_libraries(
    GemTracker
    GemTrackerLibrary
    sfml-system
    sfml-network    
)

ADD_DEFINITIONS(-std=c++11)
