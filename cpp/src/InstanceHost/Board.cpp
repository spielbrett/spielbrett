#include "Board.h"

#include "ObjectFactory.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

Board::Board(const std::string &xml)
{
    pugi::xml_document doc;
    doc.load_string(xml.c_str());

    const auto root = doc.document_element();

    const auto layoutNode = root.child("Layout");
    for (const auto node : layoutNode.children()) {
        layout.push_back(ObjectFactory::defaultFactory().construct(node));
    }
    const auto publicInformationNode = root.child("PublicInformation");
    for (const auto node : publicInformationNode.children()) {
        publicInformation.push_back(ObjectFactory::defaultFactory().construct(node));
    }
    const auto privateInformationNode = root.child("PrivateInformation");
    for (const auto node : privateInformationNode.children()) {
        privateInformation.push_back(ObjectFactory::defaultFactory().construct(node));
    }
}

std::string Board::render(PyGameClass &gameClass, int playerIndex) const
{
    pugi::xml_document doc;
    auto root = doc.append_child("Board");

    if (!layout.empty()) {
        auto layoutNode = root.append_child("Layout");
        for (const auto object : layout) {
            auto childNode = layoutNode.append_child();
            object.render(childNode);
        }
    }
    if (!publicInformation.empty()) {
        auto publicInformationNode = root.append_child("PublicInformation");
        for (const auto object : publicInformation) {
            auto childNode = publicInformationNode.append_child();
            object.render(childNode);
        }
    }
    if (!privateInformation.empty()) {
        auto privateInformationNode = root.append_child("PrivateInformation");
        for (const auto object : privateInformation) {
            auto childNode = privateInformationNode.append_child();
            object.render(childNode);
        }
    }

    std::stringstream ss;
    doc.save(ss);
    return ss.str();
}

std::unique_ptr<Board> Board::stripPresentation() const
{
    throw std::logic_error("not implemented");
}

std::unique_ptr<Board> Board::clone() const
{
    throw std::logic_error("not implemented");
}

bool Board::hasPrivateInformation() const
{
    return !privateInformation.empty();
}

int Board::numDistinctActions() const
{
    throw std::logic_error("not implemented");
}
