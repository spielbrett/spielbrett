#include "Instance.h"

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>

Instance::Instance(const std::string &instanceType)
{
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
    const std::string &payload)
{
}