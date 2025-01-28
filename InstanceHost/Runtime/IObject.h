#pragma once

#include <string>
#include <vector>

namespace Spielbrett::Runtime {

class IObject {
public:
    virtual ~IObject() = default;

    virtual void setTemplate(const std::string &templateStr) = 0;
    virtual void performAction(int playerIndex, const std::string &action, const std::vector<std::string> &args) = 0;
    virtual std::string renderTemplate(int playerIndex) = 0;
};

}