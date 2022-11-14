#include "Instance.h"

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <filesystem>
#include <iostream>
#include <shared_mutex>
#include <sstream>
#include <stdexcept>

Instance::Instance(const std::string &instanceType, const std::vector<std::string> &userIds) :
    userIds(userIds)
{
    for (size_t i = 0; i < userIds.size(); i++) {
        playerIndices[userIds[i]] = i;
    }

    std::filesystem::path moduleDir(instanceType);
    auto jsonPath = moduleDir / std::filesystem::path("config.json");

    boost::property_tree::ptree config;
    try {
        boost::property_tree::read_json(jsonPath.string(), config);
    }
    catch (boost::property_tree::json_parser_error &) {
        std::stringstream ss;
        ss << "failed to parse " << jsonPath;
        throw std::runtime_error(ss.str());
    }

    std::string entryPoint, ui;
    try {
        entryPoint = config.get<std::string>("entrypoint");
        ui = config.get<std::string>("ui");
    }
    catch (boost::property_tree::ptree_error &e) {
        std::stringstream ss;
        ss << "invalid config format: " << e.what();
        throw std::runtime_error(ss.str());
    }

    std::vector<std::string> tokens;
    boost::split(tokens, entryPoint, boost::is_any_of(":"));
    if (tokens.size() != 2) {
        throw std::runtime_error("invalid entrypoint format in config");
    }

    auto moduleName = tokens[0];
    boost::python::object gameModule;
    try {
        gameModule = boost::python::import(moduleName.c_str());
    }
    catch (const boost::python::error_already_set &) {
        if (PyErr_ExceptionMatches(PyExc_ImportError)) {
            std::stringstream ss;
            ss << "failed to import module " << moduleName;
            throw std::invalid_argument(ss.str());
        }
        else {
            throw std::runtime_error("Python exception occured");
        }
    }

    auto className = tokens[1];
    boost::python::object gameClass;
    try {
        gameClass = gameModule.attr(className.c_str());
    }
    catch (const boost::python::error_already_set &) {
        std::stringstream ss;
        ss << "failed to load class " << className << "from" << moduleName;
        throw std::invalid_argument(ss.str());
    }

    try {
        instanceObject = gameClass();
    }
    catch (const boost::python::error_already_set &) {
        std::stringstream ss;
        ss << "failed to instantiate class " << className << "from" << moduleName;
        throw std::invalid_argument(ss.str());
    }
}

void Instance::performAction(
    const std::string &userId,
    const std::string &actionName,
    const boost::python::list &payload)
{
    std::unique_lock lock(sm);

    if (!playerIndices.contains(userId)) {
        std::stringstream ss;
        ss << "user " << userId << " is not participating in the game";
        throw std::invalid_argument(ss.str());
    }

    int playerIndex = playerIndices[userId];
    try {
        instanceObject.attr(actionName.c_str())(playerIndex, actionName.c_str(), *payload);
    }
    catch (const boost::python::error_already_set &) {
        // TODO: Return traceback info instead of printing to console
        PyErr_Print();

        throw std::runtime_error("failed to apply action");
    }
}