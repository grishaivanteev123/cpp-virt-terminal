#pragma once
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "Directory.h"
#include "MultiLineFile.h"
#include "SingleLineFile.h"

struct Terminal
{
    std::unique_ptr<Directory> root;
    std::vector<Directory *> path;

    Terminal()
    {
        root = std::make_unique<Directory>("rootd");
        path.push_back(root.get());
    }

    std::string getCurrentPath()
    {
        std::string fullPath = "";
        for (auto dir : path)
        {
            if (dir->name != "/")
                fullPath += "/";
            fullPath += dir->name;
        }
        return fullPath + "/";
    }

    std::string getPrompt()
    {
        return "cpp-terminal:" + getCurrentPath();
    }

    Directory *getCurrentDir()
    {
        return path.back();
    }

    ~Terminal() = default;

    void run()
    {
        std::string line;
        while (true)
        {
            std::cout << getPrompt();
            if (!std::getline(std::cin, line))
                break;

            std::stringstream ss(line);
            std::string cmd, arg;
            ss >> cmd >> arg;

            if (cmd == "exit")
                break;

            else if (cmd == "help")
            {
                std::cout << "Available commands: exit, ls, cd, pwd, cat, touch, mkdir, rm, restore, mv, edit" << std::endl;
                std::cout << "Use restore to unhide files or directories removed with rm." << std::endl;
            }
            else if (cmd == "ls")
            {
                getCurrentDir()->listAll();
            }
            else if (cmd == "pwd")
            {
                std::cout << getCurrentPath() << std::endl;
            }
            else if (cmd == "cd")
            {
                if (arg == "..")
                {
                    if (path.size() > 1)
                    {
                        path.pop_back();
                    }
                    else
                    {
                        std::cout << "You can't go higher than the root directory" << std::endl;
                    }
                }
                else if (arg.empty())
                {
                    std::cout << "Usage: cd <directory>" << std::endl;
                }
                else
                {
                    Entry *found = getCurrentDir()->findEntry(arg);
                    Directory *nextDir = dynamic_cast<Directory *>(found);
                    if (nextDir)
                    {
                        path.push_back(nextDir);
                    }
                    else
                    {
                        std::cout << "Directory not found or is a file" << std::endl;
                    }
                }
            }
            else if (cmd == "cat")
            {
                Entry *found = getCurrentDir()->findEntry(arg);
                if (found)
                {
                    Directory *dir = dynamic_cast<Directory *>(found);
                    if (dir)
                    {
                        std::cout << "Cannot cat a directory." << std::endl;
                    }
                    else
                    {
                        found->display();
                    }
                }
                else
                {
                    std::cout << "This file doesn't exist, please try again" << std::endl;
                }
            }
            else if (cmd == "touch")
            {
                if (arg.empty())
                {
                    std::cout << "Usage: touch <filename> [-m for multiline]" << std::endl;
                }
                else if (getCurrentDir()->findEntry(arg, true))
                {
                    std::cout << "A file or directory with that name already exists." << std::endl;
                }
                else
                {
                    std::string flag;
                    ss >> flag;

                    if (flag == "-m")
                    {
                        getCurrentDir()->addEntry(std::make_unique<MultiLineFile>(arg));
                        std::cout << "Created multiline file: " << arg << std::endl;
                    }
                    else
                    {
                        getCurrentDir()->addEntry(std::make_unique<SingleLineFile>(arg));
                        std::cout << "Created singleline file: " << arg << std::endl;
                    }
                }
            }
            else if (cmd == "mkdir")
            {
                if (arg.empty())
                {
                    std::cout << "Usage: mkdir <directory_name>" << std::endl;
                }
                else if (getCurrentDir()->findEntry(arg, true))
                {
                    std::cout << "A file or directory with that name already exists." << std::endl;
                }
                else
                {
                    getCurrentDir()->addEntry(std::make_unique<Directory>(arg));
                    std::cout << "Created directory: " << arg << std::endl;
                }
            }
            else if (cmd == "rm")
            {
                if (arg.empty())
                {
                    std::cout << "Usage: rm <name>" << std::endl;
                }
                else
                {
                    Entry *found = getCurrentDir()->findEntry(arg);
                    if (found)
                    {
                        found->hide();
                        std::cout << "Removed: " << arg << std::endl;
                    }
                    else
                    {
                        std::cout << "Object not found: " << arg << std::endl;
                    }
                }
            }
            else if (cmd == "restore")
            {
                if (arg.empty())
                {
                    std::cout << "Usage: restore <name>" << std::endl;
                }
                else
                {
                    Entry *found = getCurrentDir()->findEntry(arg, true);
                    if (found)
                    {
                        found->restore();
                        std::cout << "Restored: " << arg << std::endl;
                    }
                    else
                    {
                        std::cout << "Object not found: " << arg << std::endl;
                    }
                }
            }
            else if (cmd == "mv")
            {
                if (arg.empty())
                {
                    std::cout << "Usage: mv <name> <new_name>" << std::endl;
                }
                else
                {
                    Entry *found = getCurrentDir()->findEntry(arg);
                    std::string newN;
                    ss >> newN;
                    if (!found)
                    {
                        std::cout << "This object doesn't exist, please try again" << std::endl;
                    }
                    else if (newN.empty())
                    {
                        std::cout << "Usage: mv <name> <new_name>" << std::endl;
                    }
                    else if (getCurrentDir()->findEntry(newN, true))
                    {
                        std::cout << "A file or directory with the new name already exists." << std::endl;
                    }
                    else
                    {
                        found->name = newN;
                        std::cout << "Renamed to: " << newN << std::endl;
                    }
                }
            }
            else if (cmd == "edit")
            {
                Entry *found = getCurrentDir()->findEntry(arg);
                if (found)
                {
                    found->edit();
                }
                else
                {
                    std::cout << "File not found" << std::endl;
                }
            }
            else
            {
                std::cout << "Incorrect command entered, please read help" << std::endl;
            }
        }
    }
};

int main()
{
    Terminal term;
    term.run();
    return 0;
}