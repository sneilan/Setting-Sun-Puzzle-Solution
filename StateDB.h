#ifndef __STATEDB_H__
#define __STATEDB_H__

typedef struct sha1ToStateMap {
    unsigned long hash;
    State * state;
} sha1ToStateMap;

bool knownStatesSort(sha1ToStateMap i, sha1ToStateMap j);

class StateDB {
private:
    vector<sha1ToStateMap> knownStates;
    State * lastFoundState;
public:
    bool isStateDiscovered(State * state);
    State * getLastFoundState();
    void addState(State * state);
    int numStates();
};
#endif

