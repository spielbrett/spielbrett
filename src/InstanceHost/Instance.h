#ifndef INSTANCE_H
#define INSTANCE_H

#include <boost/python.hpp>

#include <shared_mutex>
#include <string>
#include <unordered_map>

class Instance
{
public:
    Instance(
        const std::string &instanceType,
        const std::vector<std::string> &userIds);

    void performAction(
        const std::string &userId,
        const std::string &actionName);

private:
    boost::python::object instanceObject;

    std::vector<std::string> userIds;
    std::unordered_map<std::string, int> playerIndices;

    mutable std::shared_mutex sm;

    void initializeInstanceObject(boost::python::object cls);
};

#endif // INSTANCE_H
