#include "includes.h"

StateMiner::StateMiner() {
    stateDB = new StateDB;
    addedInitialState = false;
}

int StateMiner::numStates() {
    return stateDB->numStates();
}

vector<State *> StateMiner::getNewStates(State * state) {
    // don't want to return the first state that was inputted into this function
    if (addedInitialState == false) {
        stateDB->addState(state);
        addedInitialState = true;
    }

    // for any state, should return a list of new states this state can achieve
    // should automagically ensure return states have pointers going to them from other states
    // should check db to ensure that no states that exist already can be returned
    // if a discovered state exists already, ensure that already existing state
    //   points somehow to the state we're operating on.
    // this is generating a big graph of all potential states.

    vector<State *> newStates;

    // get all empty spaces
    vector<EmptySpace> emptySpaces;
    for (int i = 0; i < GAME_WIDTH; i++)
        for (int j = 0; j < GAME_HEIGHT; j++) {
            if (state->isEmpty(i, j)) {
                EmptySpace emptySpace; // sooo.. empty inside..
                emptySpace.x = i;
                emptySpace.y = j;
                emptySpaces.push_back(emptySpace);
            }
        }
    
    // get all pieces in all 4 directions
    //   from these empty spaces
    for (int i = 0; i < emptySpaces.size(); i++) {
        int x = emptySpaces[i].x;
        int y = emptySpaces[i].y;
        int above = NONE;
        int below = NONE;
        int left = NONE;
        int right = NONE;

        // get piece directly above
        above = state->getPieceIDAtLocation(x, y-1);
        if (above == NONE)
            above = state->getPieceIDAtLocation(x, y-2);

        // get piece directly below
        below = state->getPieceIDAtLocation(x, y+1);
        if (below == NONE)
            below = state->getPieceIDAtLocation(x, y+2);

        // get piece directly to left
        left = state->getPieceIDAtLocation(x-1, y);
        if (left == NONE)
            left = state->getPieceIDAtLocation(x-2, y);

        // get piece directly to right
        right = state->getPieceIDAtLocation(x+1, y);
        if (right == NONE)
            right = state->getPieceIDAtLocation(x+2, y);
        
        // For all 4 of these pieces, we have to check if they can be moved down, up, right and left respectively
        // If a piece can be moved, a new state must be created if it doesn't already exist in the db
        
        State * tempState;

        if (above != NONE && state->canShiftPieceTo(above, 0, 2)) {
            // Move the above piece down two.
            // If piece can be moved down one, check if it's in the DB.
            // If the piece is not in the DB, duplicate the state and add it to the list of states to be mined.

            state->shiftPiece(above, 0, 2);
            if (!this->stateDB->isStateDiscovered(state)) {
                tempState = state->copy();
                this->stateDB->addState(tempState);
                state->addChildState(tempState);
                newStates.push_back(tempState);
            } else {
                stateDB->getLastFoundState()->addParent(state);
            }
            state->undo();
        }

        if (above != NONE && state->canShiftPieceTo(above, 0, 1)) {
            state->shiftPiece(above, 0, 1);
            if (!this->stateDB->isStateDiscovered(state)) {
                tempState = state->copy();
                this->stateDB->addState(tempState);
                state->addChildState(tempState);
                newStates.push_back(tempState);
            } else {
                stateDB->getLastFoundState()->addParent(state);
            }
            state->undo();
        }

        // Check if the piece below can be moved up at all.
        if (below != NONE && state->canShiftPieceTo(below, 0, -2)) {
            state->shiftPiece(below, 0, -2);
            if (!this->stateDB->isStateDiscovered(state)) {
                tempState = state->copy();
                this->stateDB->addState(tempState);
                state->addChildState(tempState);
                newStates.push_back(tempState);
            } else {
                stateDB->getLastFoundState()->addParent(state);
            }
            state->undo();
        }

        if (below != NONE && state->canShiftPieceTo(below, 0, -1)) {
            state->shiftPiece(below, 0, -1);
            if (!this->stateDB->isStateDiscovered(state)) {
                tempState = state->copy();
                this->stateDB->addState(tempState);
                state->addChildState(tempState);
                newStates.push_back(tempState);
            } else {
                stateDB->getLastFoundState()->addParent(state);
            }
            state->undo();
        }


        // Check if the piece of the left can be moved right
        if (left != NONE && state->canShiftPieceTo(left, 2, 0)) {
            state->shiftPiece(left, 2, 0);
            if (!this->stateDB->isStateDiscovered(state)) {
                tempState = state->copy();
                this->stateDB->addState(tempState);
                state->addChildState(tempState);
                newStates.push_back(tempState);
            } else {
                stateDB->getLastFoundState()->addParent(state);
            }
            state->undo();
        }

        if (left != NONE && state->canShiftPieceTo(left, 1, 0)) {
            state->shiftPiece(left, 1, 0);
            if (!this->stateDB->isStateDiscovered(state)) {
                tempState = state->copy();
                this->stateDB->addState(tempState);
                state->addChildState(tempState);
                newStates.push_back(tempState);
            } else {
                stateDB->getLastFoundState()->addParent(state);
            }
            state->undo();
        }


        // Check if the piece to the right can be moved left
        if (right != NONE && state->canShiftPieceTo(right, -2, 0)) {
            state->shiftPiece(right, -2, 0);
            if (!this->stateDB->isStateDiscovered(state)) {
                tempState = state->copy();
                this->stateDB->addState(tempState);
                state->addChildState(tempState);
                newStates.push_back(tempState);
            } else {
                stateDB->getLastFoundState()->addParent(state);
            }
            state->undo();
        }

        if (right != NONE && state->canShiftPieceTo(right, -1, 0)) {
            state->shiftPiece(right, -1, 0);
            if (!this->stateDB->isStateDiscovered(state)) {
                tempState = state->copy();
                this->stateDB->addState(tempState);
                state->addChildState(tempState);
                newStates.push_back(tempState);
            } else {
                stateDB->getLastFoundState()->addParent(state);
            }
            state->undo();
        }
    }

    return newStates;
}

