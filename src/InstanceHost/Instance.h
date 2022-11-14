#ifndef INSTANCE_H
#define INSTANCE_H

#include <boost/python.hpp>

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
};

#endif // INSTANCE_H
