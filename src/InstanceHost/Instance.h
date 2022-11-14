#ifndef INSTANCE_H
#define INSTANCE_H

#include <boost/python.hpp>

#include <shared_mutex>
#include <string>

class Instance
{
public:
    Instance(const std::string &instanceType);

    void performAction(
        const std::string &userId,
        const std::string &actionName,
        const std::string &payload);

private:
    boost::python::object instanceObject;

    mutable std::shared_mutex sm;
};

#endif // INSTANCE_H
