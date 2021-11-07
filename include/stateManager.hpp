#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "tunapch.hpp"
#include "../include/baseState.hpp"

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