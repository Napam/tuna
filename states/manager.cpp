#include "include/manager.hpp"

void Manager::addState(std::string label, BaseState *state) {
    stateMap[label] = state;
}

BaseState* Manager::getState(std::string label) {
    return stateMap[label];
}