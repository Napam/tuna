#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "../include/base_state.hpp"
#include <unordered_map>

class StateManager
{
protected:
    std::unordered_map<std::string, BaseState *> states = {{"exit", nullptr}};

public:
    StateManager();
    StateManager(std::unordered_map<std::string, BaseState *> &states);
    ~StateManager();
};

StateManager::StateManager()
{
    
}

StateManager::StateManager(std::unordered_map<std::string, BaseState *> &states)
{
    
}



StateManager::~StateManager()
{
}


#endif