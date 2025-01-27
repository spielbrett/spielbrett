cmake_minimum_required(VERSION 3.14)

project(spielbrett-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Boost 1.80.0 REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(pugixml 1.13 REQUIRED)
find_package(pybind11 REQUIRED)

set(OPEN_SPIEL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/open_spiel")

set(gen_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/gen/cpp")
file(GLOB_RECURSE gen_sources CONFIGURE_DEPENDS "${gen_source_dir}/*.cc")

add_definitions(-DBOOST_ASIO_NO_DEPRECATED)

add_library(spielbrett-api STATIC ${gen_sources})
target_include_directories(spielbrett-api PRIVATE ${Protobuf_INCLUDE_DIRS})
target_include_directories(spielbrett-api PUBLIC "${gen_source_dir}")
target_link_libraries(spielbrett-api gRPC::grpc++)

add_subdirectory(InstanceHost)
