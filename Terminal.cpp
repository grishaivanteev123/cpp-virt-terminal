#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Directory.cpp"
#include "MultiLineFile.cpp"
#include "SingleLineFile.cpp"

struct Terminal {
    Directory* root;
    std::vector<Directory*> path;

    Terminal() {
        root = new Directory("rootd");
        path.push_back(root);
    }

    std::string getPrompt() {
        std::string fullPath = "";
        for (auto dir : path) {
            if (dir->name != "/") fullPath += "/";
            fullPath += dir->name;
        }
        return "cpp-terminal:" + fullPath + "/";
    }

    Directory* getCurrentDir() {
        return path.back();
    }

    ~Terminal() {
        delete root;
    }

    void run() {
        std::string line;
        while (true) {
            std::cout << getPrompt();
            if (!std::getline(std::cin, line)) break;

            std::stringstream ss(line);
            std::string cmd, arg;
            ss >> cmd >> arg;

            if (cmd == "exit") break;


            else if (cmd == "help") {
                std::cout << "Available commands: exit, ls, cd, cat, touch, mkdir, rm, restore, mv, edit" << std::endl;
            }
            else if (cmd == "ls") {
                getCurrentDir()->listAll();
            }
            else if (cmd == "cd") {
                if (arg == "..") {
                    if (path.size() > 1) {
                        path.pop_back();
                    }
                    else {
                        std::cout << "You cant go higher than the root directory" << std::endl;
                    }
                    
                }
                else {
                    Entry* found = getCurrentDir()->findEntry(arg);
                    Directory* nextDir = dynamic_cast<Directory*>(found);
                    if (nextDir) {
                        path.push_back(nextDir);
                    }
                    else {
                        std::cout << "Directory not found or is a file" << std::endl;
                    }
                }
            }
            else if (cmd == "cat") {
                Entry* found = getCurrentDir()->findEntry(arg);
                if (found) {
                    found->display(); 
                }
                else {
                    std::cout << "This file doesnt exist, please try again" << std::endl;
                }
            }
            else if (cmd == "touch") {
                if (arg.empty()) {
                    std::cout << "Usage: touch <filename> [-m for multiline]" << std::endl;
                }
                else {
                    std::string flag;
                    ss >> flag;

                    if (flag == "-m") {
                        getCurrentDir()->addEntry(new MultiLineFile(arg));
                        std::cout << "Created multiline file: " << arg << std::endl;
                    }
                    else {
                        getCurrentDir()->addEntry(new SingleLineFile(arg));
                        std::cout << "Created singleline file: " << arg << std::endl;
                    }
                }
            }
            else if (cmd == "mkdir") {
                if (!arg.empty()) {
                    getCurrentDir()->addEntry(new Directory(arg));
                }
                else {
                    std::cout << "Directory should has name" << std::endl;
                }
            }
            else if (cmd == "rm") {
                Entry* found = getCurrentDir()->findEntry(arg);
                if (found) found->hide();
            }
            else if (cmd == "restore") {
                Entry* found = getCurrentDir()->findEntry(arg);
                if (found) found->restore();
            }
            else if (cmd == "mv") {
                Entry* found = getCurrentDir()->findEntry(arg);
                std::string newN;
                ss >> newN;
                if (found && !newN.empty()) {
                    found->name = newN; 
                }
                else if (newN.empty()) {
                    std::cout << "Incorrect new name, please try again" << std::endl;
                }
                else {
                    std::cout << "This object doesnt exist, please try again" << std::endl;
                }
            }
            else if (cmd == "edit") {
                Entry* found = getCurrentDir()->findEntry(arg);
                if (found) {
                    found->edit();
                }
                else {
                    std::cout << "File not found" << std::endl;
                }
            }
            else {
                std::cout << "Incorrect command entered, please read help" << std::endl;
            }
        }
    }
};

int main() {
    Terminal term;
    term.run();
    return 0;
}