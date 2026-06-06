#pragma once

#include <iostream>
#include <string>

struct Entry {
    std::string name;
    bool hidden = false;

    Entry(const std::string& n);
    virtual ~Entry();

    virtual void displayName();
    virtual void listAll();
    virtual void display();
    virtual bool isHidden() const;
    virtual void hide();
    virtual void restore();
    virtual void edit();
};
