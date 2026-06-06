#pragma once

#include <string>
#include "Entry.h"

struct SingleLineFile : Entry {
    std::string content;

    SingleLineFile(const std::string& n);
    std::string getContent() const;
    void setContent(const std::string& c);

    void displayName() override;
    void display() override;
    void edit() override;
};
