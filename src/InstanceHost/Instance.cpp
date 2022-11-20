#include "Instance.h"

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <filesystem>
#include <iostream>
#include <optional>
#include <shared_mutex>
#include <sstream>
#include <stdexcept>

namespace
{
struct ModuleConfig {
    std::string entrypoint;
    std::string ui;

    ModuleConfig(const std::string &entrypoint, const std::string &ui) :
        entrypoint(entrypoint), ui(ui) {}
};

template<typename T>
inline void initializeReverseIndex(const std::vector<T> &v, std::unordered_map<T, int> &m)
{
    for (typename std::vector<T>::size_type i = 0; i < v.size(); i++) {
        m[v[i]] = i;
    }
}

std::filesystem::path getConfigPath(const std::string &moduleName)
{
    std::filesystem::path moduleDir(moduleName);
    return moduleDir / std::filesystem::path("config.json");
}

ModuleConfig parseConfig(const std::filesystem::path &configPath)
{
    boost::property_tree::ptree config;
    try {
        boost::property_tree::read_json(configPath, config);
    }
    catch (boost::property_tree::json_parser_error &) {
        std::stringstream ss;
        ss << "failed to parse " << configPath;
        throw std::runtime_error(ss.str());
    }

    std::string entrypoint, ui;
    try {
        entrypoint = config.get<std::string>("entrypoint");
        ui = config.get<std::string>("ui");
    }
    catch (boost::property_tree::ptree_error &e) {
        std::stringstream ss;
        ss << "invalid config format: " << e.what();
        throw std::runtime_error(ss.str());
    }

    return {entrypoint, ui};
}

std::pair<std::string, std::string> parseEntrypoint(const std::string &entrypoint)
{
    std::vector<std::string> tokens;
    boost::split(tokens, entrypoint, boost::is_any_of(":"));
    if (tokens.size() != 2) {
        throw std::runtime_error("invalid entrypoint format");
    }
    return {tokens[0], tokens[1]};
}

pybind11::object importClass(const std::string &moduleName, const std::string &className)
{
    pybind11::object gameModule;
    try {
        gameModule = pybind11::module_::import(moduleName.c_str());
    }
    catch (const pybind11::error_already_set &e) {
        if (e.matches(PyExc_ImportError)) {
            std::stringstream ss;
            ss << "failed to import module " << moduleName;
            throw std::invalid_argument(ss.str());
        }
        else {
            throw std::runtime_error("Python exception occured");
        }
    }

    pybind11::object gameClass;
    try {
        gameClass = gameModule.attr(pybind11::str(className));
    }
    catch (const pybind11::error_already_set &) {
        std::stringstream ss;
        ss << "failed to load class " << className << " from " << moduleName;
        throw std::invalid_argument(ss.str());
    }

    return gameClass;
}

std::string readUITemplate(const std::string &moduleDir, const std::string &ui)
{
    std::filesystem::path moduleDirPath(moduleDir);
    auto uiPath = moduleDirPath / std::filesystem::path(ui);

    std::stringstream ss;
    std::ifstream uiFile(uiPath);
    ss << uiFile.rdbuf();

    return ss.str();
}

} // namespace

Instance::Instance(const std::string &instanceType, const std::vector<std::string> &userIds) :
    userIds(userIds)
{
    initializeReverseIndex(userIds, playerIndices);

    auto configPath = getConfigPath(instanceType);
    auto config = parseConfig(configPath);
    auto [moduleName, className] = parseEntrypoint(config.entrypoint);

    auto gameClass = importClass(moduleName, className);
    try {
        instanceObject = gameClass();
    }
    catch (const pybind11::error_already_set &) {
        std::stringstream ss;
        ss << "failed to instantiate an instance object";
        throw std::invalid_argument(ss.str());
    }

    uiTemplate = readUITemplate(instanceType, config.ui);
}

void Instance::performAction(const std::string &userId, const std::string &action)
{
    throw std::logic_error("not implemented");
}

std::unordered_map<std::string, std::string> Instance::renderMarkup() const
{
    throw std::logic_error("not implemented");
}

std::string Instance::renderMarkup(const std::string &userId) const
{
    throw std::logic_error("not implemented");
}
