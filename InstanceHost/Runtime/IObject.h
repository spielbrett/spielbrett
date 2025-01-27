#pragma once

#include <string>
#include <vector>

namespace Spielbrett::Runtime {

class IObject {
public:
    virtual ~IObject() = default;

    virtual void performAction(int playerIndex, const std::string &action, const std::vector<std::string> &args) = 0;
    virtual double getObservation(int playerIndex, const std::string &observation) = 0;
    virtual std::string render(int playerIndex) = 0;
};

}