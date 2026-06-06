#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Entry.h"

struct Directory : Entry {
    std::vector<std::unique_ptr<Entry>> children;

    Directory(const std::string& n);
    ~Directory();

    void addEntry(std::unique_ptr<Entry> e);
    Entry* findEntry(const std::string& targetName, bool includeHidden = false);

    void displayName() override;
    std::vector<Entry*> getChildrenCopy();
    void listAll() override;
    void hide() override;
    void restore() override;
};
