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

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(Boost 1.80.0 COMPONENTS python REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

FetchContent_Declare(
    open_spiel
    GIT_REPOSITORY https://github.com/deepmind/open_spiel
    GIT_TAG master
    SOURCE_SUBDIR open_spiel
)
FetchContent_MakeAvailable(open_spiel)
FetchContent_GetProperties(open_spiel)
include_directories("${open_spiel_SOURCE_DIR}")

add_executable(InstanceHost
    src/InstanceHost/main.cpp
    src/InstanceHost/GRPCServer.cpp
    src/InstanceHost/Instance.cpp
    src/InstanceHost/InstanceHost.cpp
    src/InstanceHost/WebsocketServer.cpp)
target_link_libraries(InstanceHost
    spielbrett-api
    gRPC::grpc++_reflection
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES})
