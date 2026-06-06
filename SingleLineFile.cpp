#include "SingleLineFile.h"

SingleLineFile::SingleLineFile(const std::string& n) : Entry(n), content("") {}

std::string SingleLineFile::getContent() const {
    return content;
}

void SingleLineFile::setContent(const std::string& c) {
    content = c;
}

void SingleLineFile::displayName() {
    std::cout << name;
}

void SingleLineFile::display() {
    std::cout << content << std::endl;
}

void SingleLineFile::edit() {
    std::cout << "Current content: " << content << std::endl;
    std::cout << "Enter new line: ";

    std::string newLine;
    std::getline(std::cin >> std::ws, newLine);

    content = newLine;
    std::cout << "File updated." << std::endl;
}
