cmake_minimum_required(VERSION 3.14)

project(spielbrett-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../api")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../api" build)
else()
    FetchContent_Declare(
        spielbrett-api
        GIT_REPOSITORY https://github.com/spielbrett/spielbrett-api
        GIT_TAG main
    )
    FetchContent_MakeAvailable(spielbrett-api)
endif()

find_package(Boost 1.75.0)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

FetchContent_Declare(
    open_spiel
    GIT_REPOSITORY https://github.com/deepmind/open_spiel
    GIT_TAG master
    SOURCE_SUBDIR open_spiel
)
FetchContent_MakeAvailable(open_spiel)
FetchContent_GetProperties(open_spiel)
include_directories("${open_spiel_SOURCE_DIR}")

add_executable(InstanceHost src/InstanceHost/main.cpp)
target_link_libraries(InstanceHost spielbrett-api)
