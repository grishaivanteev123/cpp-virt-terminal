#include "Directory.h"

Directory::Directory(const std::string& n) : Entry(n) {}
Directory::~Directory() = default;

void Directory::addEntry(std::unique_ptr<Entry> e) {
    children.push_back(std::move(e));
}

Entry* Directory::findEntry(const std::string& targetName, bool includeHidden) {
    for (auto& child : children) {
        if (child->name == targetName && (includeHidden || !child->isHidden())) {
            return child.get();
        }
    }
    return nullptr;
}

void Directory::displayName() {
    std::cout << "[" << name << "]";
}

std::vector<Entry*> Directory::getChildrenCopy() {
    std::vector<Entry*> result;
    result.reserve(children.size());
    for (auto& child : children) {
        result.push_back(child.get());
    }
    return result;
}

void Directory::listAll() {
    auto childcopy = getChildrenCopy();
    for (auto child : childcopy) {
        if (!child->isHidden()) {
            child->displayName();
            std::cout << "  ";
        }
    }
    std::cout << std::endl;
}

void Directory::hide() {
    hidden = true;
    for (auto& child : children) {
        child->hide();
    }
}

void Directory::restore() {
    hidden = false;
    for (auto& child : children) {
        child->restore();
    }
}
