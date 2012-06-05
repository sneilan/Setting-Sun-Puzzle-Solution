#ifndef __STATEMINER_H__
#define __STATEMINER_H__
typedef struct EmptySpace {
    int x;
    int y;
} EmptySpace;

class StateMiner {
private:
    StateDB * stateDB;
    bool addedInitialState;
public:
    StateMiner();
    int numStates();
    vector<State *> getNewStates(State * state);
};
#endif

