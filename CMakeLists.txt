cmake_minimum_required(VERSION 3.14)

project(spielbrett-api)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(generated_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/gen/cpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${generated_source_dir}/*.cc")

add_library(${PROJECT_NAME} STATIC ${sources})
target_include_directories(${PROJECT_NAME} PRIVATE ${Protobuf_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC "${generated_source_dir}")
target_link_libraries(${PROJECT_NAME} gRPC::grpc++)
