#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Entry.cpp"

struct MultiLineFile : Entry {
    std::vector<std::string> lines;

    MultiLineFile(std::string n) : Entry(n) {}

    void display() override {
        if (lines.empty()) {
            std::cout << "(File is empty)" << std::endl;
            return;
        }
        for (const auto& line : lines) {
            std::cout << line << std::endl;
        }
    }

    void displayName() override {
        std::cout << name << "*";
    }

    void edit() override {
        std::cout << "Editing " << name << " (type '-1' on a new line to save and exit)" << std::endl;
        std::cout << "Existing content" << std::endl;
        display();
        std::cout << "Start typing" << std::endl;

        std::string input;
        while (true) {
            std::getline(std::cin >> std::ws, input);
            if (input == "-1") break;
            lines.push_back(input);
        }
        std::cout << "Changes saved." << std::endl;
    }
};