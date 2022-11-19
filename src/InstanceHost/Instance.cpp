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

boost::python::object importClass(const std::string &moduleName, const std::string &className)
{
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

    boost::python::object gameClass;
    try {
        gameClass = gameModule.attr(className.c_str());
    }
    catch (const boost::python::error_already_set &) {
        std::stringstream ss;
        ss << "failed to load class " << className << " from " << moduleName;
        throw std::invalid_argument(ss.str());
    }

    return gameClass;
}

// TODO: Just use native Mustache implementation
std::optional<boost::python::object> chevron = std::nullopt;

boost::python::object getChevron()
{
    if (!chevron.has_value()) {
        chevron = boost::python::import("chevron");
    }
    return chevron.value();
}

boost::python::str readUITemplate(const std::string &moduleDir, const std::string &ui)
{
    std::filesystem::path moduleDirPath(moduleDir);
    auto uiPath = moduleDirPath / std::filesystem::path(ui);

    std::stringstream ss;
    std::ifstream uiFile(uiPath);
    ss << uiFile.rdbuf();

    return ss.str().c_str();
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
    catch (const boost::python::error_already_set &) {
        std::stringstream ss;
        ss << "failed to instantiate an instance object";
        throw std::invalid_argument(ss.str());
    }

    uiTemplate = readUITemplate(instanceType, config.ui);
}

void Instance::performAction(const std::string &userId, const std::string &action)
{
    std::unique_lock lock(sm);

    if (!playerIndices.contains(userId)) {
        std::stringstream ss;
        ss << "user " << userId << " is not participating in the game";
        throw std::invalid_argument(ss.str());
    }

    auto playerIndex = playerIndices.at(userId);
    try {
        instanceObject.attr("perform_action")(playerIndex, action);
    }
    catch (const boost::python::error_already_set &) {
        // TODO: Return traceback info instead of printing to console
        PyErr_Print();

        throw std::runtime_error("failed to perform action");
    }
}

std::unordered_map<std::string, std::string> Instance::renderMarkup() const
{
    std::unordered_map<std::string, std::string> markup;
    for (const auto &userId : userIds) {
        markup[userId] = renderMarkup(userId);
    }
    return markup;
}

std::string Instance::renderMarkup(const std::string &userId) const
{
    // TODO: Maybe shared_lock is enough?
    std::unique_lock lock(sm);

    if (!playerIndices.contains(userId)) {
        std::stringstream ss;
        ss << "user " << userId << " is not participating in the game";
        throw std::invalid_argument(ss.str());
    }

    auto playerIndex = playerIndices.at(userId);
    try {
        auto observation = instanceObject.attr("observe")(playerIndex);

        boost::python::dict observationDict = boost::python::extract<boost::python::dict>(observation);
        observationDict["player_index"] = playerIndex;

        auto result = getChevron().attr("render")(uiTemplate, observationDict);
        return boost::python::extract<std::string>(result);
    }
    catch (boost::python::error_already_set &) {
        PyErr_Print();

        throw std::runtime_error("failed to render template");
    }
}
