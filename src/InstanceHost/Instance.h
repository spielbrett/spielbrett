#ifndef INSTANCE_H
#define INSTANCE_H

#include <boost/python.hpp>

#include <string>

class Instance
{
public:
    Instance(const std::string &instanceType);

private:
    boost::python::object instanceModule;
};

#endif // INSTANCE_H
