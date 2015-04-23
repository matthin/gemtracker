cmake_minimum_required(VERSION 2.8)
project(GemTrackerAPI CXX)

# Not sure why, but needs to be up here.
add_subdirectory(Libraries/rokunet)
include_directories(Libraries/rokunet/Include)

add_subdirectory(Source)
add_subdirectory(Source/Http)
include_directories(Source)
include_directories(Source/Http)

add_subdirectory(Libraries/SQLiteCpp)
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
    sqlite3
    SQLiteCpp
    rokunet
)

ADD_DEFINITIONS(-std=c++11)

