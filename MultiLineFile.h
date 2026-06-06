#pragma once

#include <string>
#include <vector>
#include "Entry.h"

struct MultiLineFile : Entry {
    std::vector<std::string> lines;

    MultiLineFile(const std::string& n);

    void display() override;
    void displayName() override;
    void edit() override;
};
