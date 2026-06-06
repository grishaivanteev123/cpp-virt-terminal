#include "Entry.h"

Entry::Entry(const std::string& n) : name(n) {}
Entry::~Entry() {}

void Entry::displayName() {
    std::cout << name;
}

void Entry::listAll() {
    if (!hidden) {
        displayName();
        std::cout << std::endl;
    }
}

void Entry::display() {
    std::cout << "This entry has no content." << std::endl;
}

bool Entry::isHidden() const {
    return hidden;
}

void Entry::hide() {
    hidden = true;
}

void Entry::restore() {
    hidden = false;
}

void Entry::edit() {
    std::cout << "Error: this object cannot edit" << std::endl;
}
