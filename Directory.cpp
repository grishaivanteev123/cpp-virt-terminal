#pragma once
#include <vector>
#include "Entry.cpp"

struct Directory : Entry {
    std::vector<Entry*> children;

    Directory(std::string n) : Entry(n) {}
    
    ~Directory() {
        for (auto child : children) {
            delete child;
        }
    }

    void addEntry(Entry* e) {
        children.push_back(e);
    }

    
    Entry* findEntry(const std::string& targetName) {
        for (auto child : children) {
            if (child->name == targetName) {
                return child;
            }
        }
        return nullptr;
    }

    void displayName() override {
        std::cout << "[" << name << "]";
    }

    std::vector<Entry*> getChildrenCopy() {
        return children;
    }

    void listAll() override {
        auto childcopy = getChildrenCopy();
        for (auto child : childcopy) {
            if (!child->isHidden()) { 
                child->displayName();
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }

    void hide() override {
        hidden = true;
        for (auto child : children) {
            child->hide();
        }
    }

    void restore() override {
        hidden = false;
        for (auto child : children) {
            child->restore();
        }
    }

};