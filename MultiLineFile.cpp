#include "MultiLineFile.h"

MultiLineFile::MultiLineFile(const std::string& n) : Entry(n) {}

void MultiLineFile::display() {
    if (lines.empty()) {
        std::cout << "(File is empty)" << std::endl;
        return;
    }
    for (const auto& line : lines) {
        std::cout << line << std::endl;
    }
}

void MultiLineFile::displayName() {
    std::cout << name << "*";
}

void MultiLineFile::edit() {
    std::cout << "Editing " << name << " (type '-1' on a new line to save and exit)" << std::endl;
    std::cout << "Existing content" << std::endl;
    display();
    std::cout << "Start typing" << std::endl;

    lines.clear();
    std::string input;
    while (true) {
        std::getline(std::cin >> std::ws, input);
        if (input == "-1") break;
        lines.push_back(input);
    }
    std::cout << "Changes saved." << std::endl;
}
