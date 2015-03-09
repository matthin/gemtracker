cmake_minimum_required(VERSION 2.8)
project(GemTrackerAPI CXX)

add_subdirectory(Source)
add_subdirectory(Source/Http)
add_subdirectory(Libraries/SQLiteCpp)
include_directories(Source)
include_directories(Source/Http)
include_directories(Libraries/SQLiteCpp/include)

add_library(
    GemTrackerAPILibrary
    STATIC
    ${SourceFiles}
)
add_executable(GemTrackerAPI Source/Main.cc)
target_link_libraries(
    GemTrackerAPI
    GemTrackerAPILibrary
    sfml-system
    sfml-network
    sqlite3
    SQLiteCpp
)

ADD_DEFINITIONS(-std=c++11)

