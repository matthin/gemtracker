cmake_minimum_required(VERSION 2.8)
project(GemTracker CXX)

add_subdirectory(Source)
add_subdirectory(Libraries/SQLiteCpp)
include_directories(Source)
include_directories(Libraries/SQLiteCpp/include)

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
    sqlite3
    SQLiteCpp
)

ADD_DEFINITIONS(-std=c++11)
