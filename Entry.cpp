#pragma once
#include <iostream>
#include <string>

struct Entry {
    std::string name;
    bool hidden = false;

    Entry(std::string n) : name(n) {}
    virtual ~Entry() {}

    virtual void displayName() {
        std::cout << name;
    }

    virtual void listAll() {
        if (!hidden) {
            displayName();
            std::cout << std::endl;
        }
    }

    virtual void display() {
        std::cout << "This entry has no content." << std::endl;
    }

    virtual bool isHidden() { return hidden; }
    virtual void hide() { hidden = true; }
    virtual void restore() { hidden = false; }


    virtual void edit() {
        std::cout << "Error: this object cannot edit" << std::endl;
    }
};