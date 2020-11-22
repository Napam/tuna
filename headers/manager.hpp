#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <map>
#include <queue>

class Manager
{
protected:
    std::map<std::string, std::string> statemap;
    std::deque<void*> history;
public:
    void add_state();
    void get_state();
    void reload_state();
};

#endif