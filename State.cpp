#include "includes.h"

State::State() {
    this->pieces = new Piece[10]; // @TODO use allocator instead
}

int State::getPieceX(int pieceID) {
    return pieces[pieceID].x;
}

int State::getPieceY(int pieceID) {
    return pieces[pieceID].y;
}

bool State::isEmpty(int x, int y) {
    for (int i = 0; i < NUM_PIECES; i++) {
        if (pieces[i].pointInside(x, y)) {
            return false;
        }
    }
    return true;
}

typedef struct POINT {
    int x;
    int y;
} POINT;

bool sortPoints(POINT a, POINT b) {
    if (a.x == b.x)
        return a.y < b.y;
    else
        return a.x < b.x;
}


unsigned long State::getHash() {
    // gets a unique value representing this state
    string hash = "00000000000000000000";
    char buffer[2];
    locale loc; // the "C" locale, whatever that means. used in hashing.
    const collate<char>& coll = use_facet<collate<char> >(loc);
    
    // TALL_BLACK_PIECE_A -> D
    // YELLOW_PIECE_A -> D
    // I need to get black and yellow points A-D in sorted order first.

    // compute and sort points of tall black pieces
    vector<POINT> blacks;
    for (int i = TALL_BLACK_PIECE_A; i <= TALL_BLACK_PIECE_D; i++) {
        POINT p;
        p.x = pieces[i].x;
        p.y = pieces[i].y;
        blacks.push_back(p);
    }
    sort(blacks.begin(), blacks.end(), sortPoints);

    // add the blacks to the hash
    for (int i = 0; i < 4; i++) {
        sprintf(buffer, "%d", blacks[i].x);
        hash[2*i] = buffer[0];

        sprintf(buffer, "%d", blacks[i].y);
        hash[2*i+1] = buffer[0];
    }

    // compute and sort points of yellow squares
    vector<POINT> yellows;
    for (int i = YELLOW_PIECE_A; i <= YELLOW_PIECE_D; i++) {
        POINT p;
        p.x = pieces[i].x;
        p.y = pieces[i].y;
        yellows.push_back(p);
    }
    sort(yellows.begin(), yellows.end(), sortPoints);

    // add the yellows to the hash
    for (int i = 0; i < 4; i++) {
        sprintf(buffer, "%d", yellows[i].x);
        hash[2*(i+4)] = buffer[0];

        sprintf(buffer, "%d", yellows[i].y);
        hash[2*(i+4)+1] = buffer[0];
    }
    
    // add the red sun piece & the wide black piece
    sprintf(buffer, "%d", pieces[RED_SUN_PIECE].x);
    hash[2*8] = buffer[0];
    sprintf(buffer, "%d", pieces[RED_SUN_PIECE].y);
    hash[2*8+1] = buffer[0];
    sprintf(buffer, "%d", pieces[WIDE_BLACK_PIECE].x);
    hash[2*9] = buffer[0];
    sprintf(buffer, "%d", pieces[WIDE_BLACK_PIECE].y);
    hash[2*9+1] = buffer[0];

    return coll.hash(hash.data(),hash.data()+hash.length());
}

State * State::copy() {
    State * newState = createInitialState();
    for (int p = 0; p < NUM_PIECES; p++) {
        newState->movePiece(p, pieces[p].x, pieces[p].y);
    }
    
    for (int i = 0; i < nextStates.size(); i++)
        newState->addChildState(nextStates[i]);

    return newState;
}

void State::movePiece(int pieceID, int x, int y) {
    this->lastMovedPieceID = pieceID;
    this->lastMovedPieceOldX = pieces[pieceID].x;
    this->lastMovedPieceOldY = pieces[pieceID].y;

    pieces[pieceID].x = x;
    pieces[pieceID].y = y;
}


void State::shiftPiece(int pieceID, int shiftX, int shiftY) {
    int oldX = pieces[pieceID].x;
    int oldY = pieces[pieceID].y;
    int newX = oldX+shiftX;
    int newY = oldY+shiftY;
    this->movePiece(pieceID, newX, newY);
}

bool State::canShiftPieceTo(int pieceID, int shiftX, int shiftY) {
    int oldX = pieces[pieceID].x;
    int oldY = pieces[pieceID].y;
    int newX = oldX+shiftX;
    int newY = oldY+shiftY;

    if (canMovePieceTo(pieceID, newX, newY)) return true;
    else return false;
}

bool State::canMovePieceTo(int pieceID, int x, int y) {
    int oldX = pieces[pieceID].x;
    int oldY = pieces[pieceID].y;

    int w = pieces[pieceID].w;
    int h = pieces[pieceID].h;

    if (x+w > GAME_WIDTH || y+h > GAME_HEIGHT)
        return false;
    if (x < 0 || y < 0)
        return false;

    movePiece(pieceID, x, y);

    for (int p = 0; p < NUM_PIECES; p++) {
        if (p == pieceID) // don't compare this piece to itself
            continue;
        if (pieces[p].intersects(&pieces[pieceID])) {
            movePiece(pieceID, oldX, oldY);
            return false;
        }
    }

    movePiece(pieceID, oldX, oldY);
    return true;
}

int State::getPieceIDAtLocation(int x, int y) {
    for (int i = 0; i < NUM_PIECES; i++) {
        if (pieces[i].pointInside(x, y)) {
            return i;
        }
    }
    return NONE;
}

void State::undo() {
    // undoes one level of movement
    movePiece(lastMovedPieceID, lastMovedPieceOldX, lastMovedPieceOldY);
}

void State::addParent(State* state) {
    if (!stateInListOfStates(state, parents)) {
        parents.push_back(state);
    }
}

void State::addChildState(State * state) {
    state->addParent(this);
    nextStates.push_back(state);
}


//
// utility functions, could be in better place
//
bool stateInListOfStates(State * state, vector<State*> & stateList) {
    int count = 0;
    unsigned long stateHash = state->getHash();
    for (int i = 0; i < stateList.size(); i++) {
        if (stateHash == stateList[i]->getHash())
            return true;
    }
    return false;
}


State * createInitialState() {
    State * state = new State();

    // sun piece
    state->pieces[RED_SUN_PIECE].x = 1;
    state->pieces[RED_SUN_PIECE].y = 0;
    state->pieces[RED_SUN_PIECE].w = 2;
    state->pieces[RED_SUN_PIECE].h = 2;
    state->pieces[RED_SUN_PIECE].color = RED;


    // black pieces
    state->pieces[TALL_BLACK_PIECE_A].x = 0;
    state->pieces[TALL_BLACK_PIECE_A].y = 0;
    state->pieces[TALL_BLACK_PIECE_A].w = 1;
    state->pieces[TALL_BLACK_PIECE_A].h = 2;
    state->pieces[TALL_BLACK_PIECE_A].color = BLACK;

    state->pieces[TALL_BLACK_PIECE_B].x = 3;
    state->pieces[TALL_BLACK_PIECE_B].y = 0;
    state->pieces[TALL_BLACK_PIECE_B].w = 1;
    state->pieces[TALL_BLACK_PIECE_B].h = 2;
    state->pieces[TALL_BLACK_PIECE_B].color = BLACK;

    state->pieces[TALL_BLACK_PIECE_C].x = 0;
    state->pieces[TALL_BLACK_PIECE_C].y = 3;
    state->pieces[TALL_BLACK_PIECE_C].w = 1;
    state->pieces[TALL_BLACK_PIECE_C].h = 2;
    state->pieces[TALL_BLACK_PIECE_C].color = BLACK;

    state->pieces[TALL_BLACK_PIECE_D].x = 3;
    state->pieces[TALL_BLACK_PIECE_D].y = 3;
    state->pieces[TALL_BLACK_PIECE_D].w = 1;
    state->pieces[TALL_BLACK_PIECE_D].h = 2;
    state->pieces[TALL_BLACK_PIECE_D].color = BLACK;


    //   the horizontal piece
    state->pieces[WIDE_BLACK_PIECE].x = 1;
    state->pieces[WIDE_BLACK_PIECE].y = 2;
    state->pieces[WIDE_BLACK_PIECE].w = 2;
    state->pieces[WIDE_BLACK_PIECE].h = 1;
    state->pieces[WIDE_BLACK_PIECE].color = BLACK;


    // yellow pieces
    state->pieces[YELLOW_PIECE_A].x = 1;
    state->pieces[YELLOW_PIECE_A].y = 3;
    state->pieces[YELLOW_PIECE_A].w = 1;
    state->pieces[YELLOW_PIECE_A].h = 1;
    state->pieces[YELLOW_PIECE_A].color = YELLOW;

    state->pieces[YELLOW_PIECE_B].x = 2;
    state->pieces[YELLOW_PIECE_B].y = 3;
    state->pieces[YELLOW_PIECE_B].w = 1;
    state->pieces[YELLOW_PIECE_B].h = 1;
    state->pieces[YELLOW_PIECE_B].color = YELLOW;

    state->pieces[YELLOW_PIECE_C].x = 1;
    state->pieces[YELLOW_PIECE_C].y = 4;
    state->pieces[YELLOW_PIECE_C].w = 1;
    state->pieces[YELLOW_PIECE_C].h = 1;
    state->pieces[YELLOW_PIECE_C].color = YELLOW;

    state->pieces[YELLOW_PIECE_D].x = 2;
    state->pieces[YELLOW_PIECE_D].y = 4;
    state->pieces[YELLOW_PIECE_D].w = 1;
    state->pieces[YELLOW_PIECE_D].h = 1;
    state->pieces[YELLOW_PIECE_D].color = YELLOW;

    return state;
};

bool solutionNotFound(vector<State *> & stateList) {
    for (int i = 0; i < stateList.size(); i++) {
        int x = stateList[i]->getPieceX(RED_SUN_PIECE);
        int y = stateList[i]->getPieceY(RED_SUN_PIECE);
        if (x == 1 && y == 3) {
            cout << "FOUND A SOLUTION\a";
            return false; // hooray!
        }
    }
    return true;
}

