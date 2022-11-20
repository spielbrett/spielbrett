cmake_minimum_required(VERSION 3.14)

project(spielbrett-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

find_package(protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

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

find_package(Boost 1.80.0 REQUIRED)
find_package(pybind11 REQUIRED)

if(NOT DEFINED OPEN_SPIEL_ROOT_DIR)
    message(FATAL_ERROR "OPEN_SPIEL_ROOT_DIR not defined")
endif()

add_executable(
    InstanceHost
    src/InstanceHost/main.cpp
    src/InstanceHost/GRPCServer.cpp
    src/InstanceHost/Instance.cpp
    src/InstanceHost/InstanceHost.cpp
    src/InstanceHost/WebsocketServer.cpp
)
target_include_directories(
    InstanceHost PRIVATE
    "${OPEN_SPIEL_ROOT_DIR}"
    "${OPEN_SPIEL_ROOT_DIR}/open_spiel/abseil-cpp"
)
target_link_directories(
    InstanceHost PRIVATE
    "${OPEN_SPIEL_ROOT_DIR}/build"
)
target_link_libraries(
    InstanceHost
    spielbrett-api
    gRPC::grpc++_reflection
    pybind11::embed
    open_spiel
)
