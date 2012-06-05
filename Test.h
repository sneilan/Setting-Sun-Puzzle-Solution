// testing functions
bool testPiece();
bool test();

class TestState {
public:
    bool testIsEmpty() {
        State * state = createInitialState();

        // ensure that the side spaces in the initial state are empty
        if (!state->isEmpty(0, 2)) {
            delete state;
            return false;
        }

        if (!state->isEmpty(3, 2)) {
            delete state;
            return false;
        }

        delete state;
        return true;
    }

    bool testGetHash() {
        State * state = createInitialState();
        unsigned long hash1 = state->getHash();
        state->movePiece(WIDE_BLACK_PIECE, 2, 2);
        unsigned long hash2 = state->getHash();
        if (hash1 == hash2) {
            delete state;
            return false;
        }

        state->movePiece(WIDE_BLACK_PIECE, 1, 2);
        hash2 = state->getHash();
        if (hash1 != hash2) {
            delete state;
            return false;
        }

        // States that are geometrically the same but have pieces in different places should return the same hash code.
        // For instance, in the initial state, there are two black horizontal pieces at the top. Those pieces are both black and horizontal and are labeled piece A and piece B such that A is on the left and B is on the right. If A is on the left and B is on the right, the state should have the same hash code when B is on the left and A is on the right.

        // to test this, ensure the initial state hash is the same for when the pieces are in different places
        hash1 = state->getHash();
        state->movePiece(TALL_BLACK_PIECE_A, 3, 0); // swap A and B
        state->movePiece(TALL_BLACK_PIECE_B, 0, 0);
        hash2 = state->getHash();
        
        if (hash1 != hash2) {
            delete state;
            return false;
        }

        delete state;
        return true;
    }

    bool testCopy() {
        State * state1 = createInitialState();
        State * state2 = state1->copy();
        
        int hash1 = state1->getHash();
        int hash2 = state2->getHash();

        if (hash1 != hash2) {
            delete state1, state2;
            return false;
        }
        
        delete state1, state2;
        return true;
    }

    bool testMovePiece() {
        State * state = createInitialState();
        state->movePiece(TALL_BLACK_PIECE_A, 0, 1);

        if (!state->isEmpty(0,0)) {
            delete state;
            return false;
        }

        state->movePiece(TALL_BLACK_PIECE_A, 0, 0);
        state->movePiece(WIDE_BLACK_PIECE, 2, 2);

        if (!state->isEmpty(0,2) || !state->isEmpty(1,2)) {
            delete state;
            return false;
        }

        state->movePiece(WIDE_BLACK_PIECE, 0, 2);

        if (!state->isEmpty(2,2) || !state->isEmpty(3,2)) {
            delete state;
            return false;
        }

        state->movePiece(YELLOW_PIECE_B, 2, 2);

        if (!state->isEmpty(2,3) || !state->isEmpty(3, 2)) {
            delete state;
            return false;
        }

        state->movePiece(YELLOW_PIECE_B, 3, 2);
        state->movePiece(YELLOW_PIECE_D, 2, 2);
        state->movePiece(TALL_BLACK_PIECE_D, 2, 3);
        state->movePiece(YELLOW_PIECE_B, 3, 4);
        state->movePiece(TALL_BLACK_PIECE_B, 3, 2);
        state->movePiece(RED_SUN_PIECE, 2, 0);

        if (!state->isEmpty(1,0) || !state->isEmpty(1, 1)) {
            delete state;
            return false;
        }

        delete state;
        return true;
    }

    bool testShiftPIece() {
        // @TODO finish this
        return true;
    }

    bool testCanShiftPieceTo() {
        // @TODO finish this
        return true;
    }

    bool testUndo() {
        // @TODO finish this
        return true;
    }

    bool testCanMovePieceTo() {
        State * state = createInitialState();

        // make sure we can't move pieces outside the board
        if (state->canMovePieceTo(TALL_BLACK_PIECE_A, -1, -1)) {
            delete state;
            return false;
        }

        if (!state->canMovePieceTo(TALL_BLACK_PIECE_A, 0, 1)) {
            delete state;
            return false;
        }

        state->movePiece(TALL_BLACK_PIECE_A, 0, 1);

        if (!state->canMovePieceTo(TALL_BLACK_PIECE_A, 0, 0)) {
            delete state;
            return false;
        }

        state->movePiece(TALL_BLACK_PIECE_A, 0, 0);
        //cout << state->canMovePieceTo(WIDE_BLACK_PIECE

        if (!state->canMovePieceTo(WIDE_BLACK_PIECE, 0, 2)) {
            delete state;
            return false;
        }

        if (!state->canMovePieceTo(WIDE_BLACK_PIECE, 2, 2)) {
            delete state;
            return false;
        }

        if (!state->canMovePieceTo(WIDE_BLACK_PIECE, 0, 2) || 
                !state->canMovePieceTo(WIDE_BLACK_PIECE, 2, 2)) {
            delete state;
            return false;
        }

        state->movePiece(WIDE_BLACK_PIECE, 0, 2);

        if (!state->canMovePieceTo(WIDE_BLACK_PIECE, 1, 2) || 
                !state->canMovePieceTo(WIDE_BLACK_PIECE, 2, 2)) {
            delete state;
            return false;
        }

        state->movePiece(YELLOW_PIECE_B, 2, 2);

        if (!state->isEmpty(2, 3) || !state->isEmpty(3, 2)) {
            delete state;
            return false;
        }

        state->movePiece(YELLOW_PIECE_B, 2, 3);
        state->movePiece(YELLOW_PIECE_D, 2, 2);
        state->movePiece(TALL_BLACK_PIECE_D, 2, 3);
        state->movePiece(YELLOW_PIECE_B, 3, 4);
        state->movePiece(TALL_BLACK_PIECE_B, 3, 2);
        state->movePiece(RED_SUN_PIECE, 2, 0);

        if (!state->isEmpty(1,0) || !state->isEmpty(1, 1)) {
            delete state;
            return false;
        }
        
        delete state;
        return true;
    }

    bool testGetPieceIDAtLocation() {
        State * state = createInitialState();
        if (state->getPieceIDAtLocation(0,0) != TALL_BLACK_PIECE_A) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(0,1) != TALL_BLACK_PIECE_A) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(0,2) != NONE) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(0,3) != TALL_BLACK_PIECE_C) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(0,4) != TALL_BLACK_PIECE_C) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(1,0) != RED_SUN_PIECE) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(1,1) != RED_SUN_PIECE) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(1,2) != WIDE_BLACK_PIECE) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(1,3) != YELLOW_PIECE_A) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(1,4) != YELLOW_PIECE_C) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(2,0) != RED_SUN_PIECE) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(2,1) != RED_SUN_PIECE) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(2,2) != WIDE_BLACK_PIECE) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(2,3) != YELLOW_PIECE_B) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(2,4) != YELLOW_PIECE_D) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(3,0) != TALL_BLACK_PIECE_B) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(3,1) != TALL_BLACK_PIECE_B) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(3,2) != NONE) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(3,3) != TALL_BLACK_PIECE_D) {
            delete state;
            return false;
        }
        if (state->getPieceIDAtLocation(3,4) != TALL_BLACK_PIECE_D) {
            delete state;
            return false;
        }

        delete state;
        return true;
    }

    bool runTests() {
        TestState testState;

        if (!testState.testIsEmpty()) {
            cout << "testState.testIsEmpty() returned false\n";
            return false;
        } 

        if (!testState.testGetHash()) {
            cout << "testState.testGetHash() returned false\n";
            return false;
        }

        if (!testState.testCopy()) {
            cout << "testState.testCopy() returned false\n";
            return false;
        }

        if (!testState.testMovePiece()) {
            cout << "testState.testMovePiece() returned false\n";
            return false;
        }

        if (!testState.testCanMovePieceTo()) {
            cout << "testState.testCanMovePieceTo() returned false\n";
            return false;
        }

        if (!testState.testGetPieceIDAtLocation()) {
            cout << "testState.testGetPieceIDAtLocation() returned false\n";
            return false;
        }

        if (!testState.testShiftPIece()) {
            cout << "testState.testShiftPiece() returned false\n";
            return false;
        }

        if (!testState.testCanShiftPieceTo()) {
            cout << "testState.testCanShiftPieceTo() returned false\n";
            return false;
        }

        if (!testState.testUndo()) {
            cout << "testState.testUndo() returned false\n";
            return false;
        }

        return true;
    }
};


bool testPiece() {
    // create a gameboard, test points throughout it, then, take each type of piece and determine what 
    //   pieces it should intersect with at different points

    // no pieces should intersect in the initial state
    State * state = createInitialState();
    for (int i = 0; i < NUM_PIECES; i++) {
        for (int j = i+1; j < NUM_PIECES; j++) {
            if (state->pieces[i].intersects(&state->pieces[j])) {
                return false;
            }
        }
    }

    // these points should be inside piece 0 (the sun piece)
    if (state->pieces[RED_SUN_PIECE].pointInside(1,0) == false)
        return false;
    if (state->pieces[RED_SUN_PIECE].pointInside(1,1) == false)
        return false;
    if (state->pieces[RED_SUN_PIECE].pointInside(2,0) == false)
        return false;
    if (state->pieces[RED_SUN_PIECE].pointInside(2,1) == false)
        return false;

    // these points should all be inside the top left black piece
    //   on the initial gameboard
    // see initial gameboard diagram for details.
    if (state->pieces[TALL_BLACK_PIECE_A].pointInside(0,0) == false)
        return false;
    if (state->pieces[TALL_BLACK_PIECE_A].pointInside(0,1) == false)
        return false;

    // these points should all be in the horizontal piece on the initial gameboard
    if (state->pieces[WIDE_BLACK_PIECE].pointInside(1,2) == false)
        return false;
    if (state->pieces[WIDE_BLACK_PIECE].pointInside(2,2) == false)
        return false;

    // these points should all be inside the yellow pieces
    //   on the initial gameboard
    if (state->pieces[YELLOW_PIECE_A].pointInside(1,3) == false)
        return false;
    if (state->pieces[YELLOW_PIECE_B].pointInside(2,3) == false)
        return false;
    if (state->pieces[YELLOW_PIECE_C].pointInside(1,4) == false)
        return false;
    if (state->pieces[YELLOW_PIECE_D].pointInside(2,4) == false)
        return false;

    return true;
}


class TestStateDB {
public:
    bool runTests() {
        State * state = createInitialState();
        StateDB stateDB;
        if (stateDB.isStateDiscovered(state)) {
            delete state;
            return false;
        }
        stateDB.addState(state);
        if (!stateDB.isStateDiscovered(state)) {
            delete state;
            return false;
        }
        
        State * newState = state->copy();
        newState->movePiece(TALL_BLACK_PIECE_A, 0, 1);
        if (stateDB.isStateDiscovered(newState)) {
            delete newState;
            delete state;
            return false;
        }
        stateDB.addState(newState);
        if (!stateDB.isStateDiscovered(newState)) {
            delete newState;
            delete state;
            return false;
        }
        
        delete state;
        delete newState;
        return true;
    }
};


class TestStateMiner {
public:
    bool testGetNewStates() {
        // state miner should return 6 potential new states for the initial state
        StateMiner stateMiner;
        State * state = createInitialState();
        vector<State *> stateList = stateMiner.getNewStates(state);
        state->movePiece(TALL_BLACK_PIECE_A, 0, 1);
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(TALL_BLACK_PIECE_A, 0, 0);
        state->movePiece(TALL_BLACK_PIECE_B, 3, 1);
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(TALL_BLACK_PIECE_B, 3, 0);
        state->movePiece(TALL_BLACK_PIECE_C, 0, 2);
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(TALL_BLACK_PIECE_C, 0, 3);
        state->movePiece(TALL_BLACK_PIECE_D, 3, 2);
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(TALL_BLACK_PIECE_D, 3, 3);
        state->movePiece(WIDE_BLACK_PIECE, 0, 2);
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(WIDE_BLACK_PIECE, 2, 2);
        if (!stateInListOfStates(state, stateList))
            return false;
        if (stateList.size() != 6)
            return false;

        // If called again on initial state, state miner should return no states
        //   for the initial state.
        // This is because we don't want to repeat states we've already been to.
        state->movePiece(WIDE_BLACK_PIECE, 1, 2);
        stateList = stateMiner.getNewStates(state);
        if (stateList.size() != 0)
            return false;

        
        // now lets try shuffling some pieces around and see what happens
        state->movePiece(WIDE_BLACK_PIECE, 0, 2);
        stateList = stateMiner.getNewStates(state);
        if (stateList.size() != 3)   // there should be 3 new states with the wide
            return false;  // bar all the way to the left
        state->movePiece(TALL_BLACK_PIECE_B, 3, 1); // test state 1
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(TALL_BLACK_PIECE_B, 3, 0);
        // the state we just computed a bunch of new states
        //   for should not be in the list of states returned
        //   (The one with the wide black piece to the left)
        if (stateInListOfStates(state, stateList))
            return false;
        // initial state should not be in list of states either
        //   since we already mined that state.
        State * initialState = createInitialState();
        if (stateInListOfStates(initialState, stateList))
            return false;
        delete initialState;
        // continue checking other states returned
        state->movePiece(TALL_BLACK_PIECE_D, 3, 2);
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(TALL_BLACK_PIECE_D, 3, 3);
        state->movePiece(YELLOW_PIECE_B, 2, 2);
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(YELLOW_PIECE_B, 2, 3);

        // make some illegal moves and ensure they're not in the list of states returned
        state->movePiece(RED_SUN_PIECE, 2, 0);
        if (stateInListOfStates(state, stateList))
            return false;
        state->movePiece(RED_SUN_PIECE, 1, 0);
        state->movePiece(TALL_BLACK_PIECE_A, 0, 1);
        if (stateInListOfStates(state, stateList))
            return false;
        state->movePiece(TALL_BLACK_PIECE_A, 0, 0);

        // now ensure we don't get the same list of new states
        //   for this state
        stateList = stateMiner.getNewStates(state);
        if (stateList.size() != 0)
            return false;
        
        // move the yellow piece B up and work from there
        state->movePiece(YELLOW_PIECE_B, 2, 2);
        stateList = stateMiner.getNewStates(state);
        if (stateList.size() != 5)
            return false;
        state->movePiece(YELLOW_PIECE_B, 3, 2);
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(YELLOW_PIECE_B, 2, 2);
        state->movePiece(YELLOW_PIECE_D, 2, 3); // try out yellow piece D
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(YELLOW_PIECE_D, 2, 4);
        state->movePiece(TALL_BLACK_PIECE_B, 3, 1); // try out black piece B
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(TALL_BLACK_PIECE_B, 3, 0);
        state->movePiece(TALL_BLACK_PIECE_D, 3, 2); // try out black piece D
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(TALL_BLACK_PIECE_D, 3, 3);

        // move the yellow piece B right and work from there
        state->movePiece(YELLOW_PIECE_B, 3, 2);
        stateList = stateMiner.getNewStates(state);
        if (stateList.size() != 4) // ensure the number of states is correct
            return false;
        state->movePiece(YELLOW_PIECE_A, 2, 3); // try out yellow piece A
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(YELLOW_PIECE_A, 1, 3);
        state->movePiece(YELLOW_PIECE_D, 2, 3); // try out yellow piece D
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(YELLOW_PIECE_D, 2, 2);
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(YELLOW_PIECE_D, 2, 4);
        state->movePiece(WIDE_BLACK_PIECE, 1, 2); // try out the wide piece
        if (!stateInListOfStates(state, stateList))
            return false;
        state->movePiece(WIDE_BLACK_PIECE, 0, 2);

        // move the yellow piece D all the way up and work from there
        state->movePiece(YELLOW_PIECE_D, 2, 2);

        // nah.. and this is where I stop for the moment being

        delete state;
        return true;
    }

    bool runTests() {
        if (!testGetNewStates())
            return false;
        return true;
    }
};


bool test() {
    if (!testPiece()) { 
        cout << "testPiece() returned false\n";
        return false;
    }

    TestState testState;
    if (!testState.runTests()) {
        cout << "testState.runTests() returned false\n";
        return false;
    }

    TestStateDB testStateDB;
    if (!testStateDB.runTests()) { 
        cout << "testStateDB.runTests() returned false\n";
        return false;
    }

    TestStateMiner testStateMiner;
    if (!testStateMiner.runTests()) {
        cout << "testStateMiner.runTests() returned false\n";
        return false;
    }

    return true;
}

