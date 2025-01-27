add_executable(
    InstanceHost
    main.cpp
    Runtime/Python/ExternalClass.cpp
    Runtime/Python/Object.cpp
    Runtime/Python/ObjectBindings.cpp
    Runtime/Python/Runtime.cpp
    Board.cpp
    GRPCServer.cpp
    Instance.cpp
    InstanceHost.cpp
    OpenSpielGame.cpp
    WebsocketServer.cpp
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
    InstanceHost PRIVATE
    spielbrett-api
    gRPC::grpc++_reflection
    nlohmann_json::nlohmann_json
    pugixml::pugixml
    pybind11::embed
    open_spiel
)
