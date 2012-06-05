#include "includes.h"

bool knownStatesSort(sha1ToStateMap i, sha1ToStateMap j) {
    return i.hash < j.hash;
}

bool StateDB::isStateDiscovered(State * state) {
    // use a binary search to see if state
    //  is already in list of discovered states
    vector<sha1ToStateMap>::iterator it;
    sha1ToStateMap tempVal;
    tempVal.state = state;
    tempVal.hash = state->getHash();

    // binary search
    
    bool found = binary_search(knownStates.begin(), knownStates.end(), tempVal, knownStatesSort);

    vector<sha1ToStateMap>::iterator first = lower_bound(knownStates.begin(), knownStates.end(), tempVal, knownStatesSort);
    if (first != knownStates.end() && !knownStatesSort(tempVal, *first)) {
        lastFoundState = (*first).state;
        return true;
    }
    else
        return false;
}

State * StateDB::getLastFoundState() {
    return lastFoundState;
}

void StateDB::addState(State * state) {
    // add this state to our db of discovered states
    sha1ToStateMap map;
    map.hash = state->getHash();
    map.state = state;
    knownStates.push_back(map);
    sort(knownStates.begin(), knownStates.end(), knownStatesSort);
}

int StateDB::numStates() {
    return knownStates.size();
}

