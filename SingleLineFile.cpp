#pragma once
#include <iostream>
#include <string>
#include "Entry.cpp"

struct SingleLineFile : Entry {
    std::string content;

    SingleLineFile(std::string n) : Entry(n), content("") {}
    std::string getContent() { return content; }
    void setContent(std::string c) { content = c; }

    void displayName() override {
        std::cout << name;
    }

    void display() override {
        std::cout << content << std::endl;
    }

    void edit() override {
        std::cout << "Current content: " << content << std::endl;
        std::cout << "Enter new line: ";

        std::string newLine;
        std::getline(std::cin >> std::ws, newLine);

        content = newLine;
        std::cout << "File updated." << std::endl;
    }
};