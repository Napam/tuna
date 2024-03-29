#ifndef MANAGER_H
#define MANAGER_H

#include "tunapch.hpp"
#include "baseState.hpp"

class Manager
{
protected:
    std::map<std::string, BaseState*> stateMap;
public:
    void addState(std::string label, BaseState *state);
    BaseState* getState(std::string label);
};

#endif