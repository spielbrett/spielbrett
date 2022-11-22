add_executable(
    InstanceHost
    main.cpp
    Board.cpp
    GRPCServer.cpp
    Instance.cpp
    InstanceHost.cpp
    OpenSpielGame.cpp
    PyGameClass.cpp
    WebsocketServer.cpp
)
target_include_directories(
    InstanceHost PRIVATE
    "$ENV{OPEN_SPIEL_ROOT_DIR}"
    "$ENV{OPEN_SPIEL_ROOT_DIR}/open_spiel/abseil-cpp"
)
target_link_directories(
    InstanceHost PRIVATE
    "$ENV{OPEN_SPIEL_ROOT_DIR}/build"
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
