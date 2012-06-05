#ifndef __STATE_H__
#define __STATE_H__
#include "Piece.h"

class State {
public:
    Piece * pieces;
    vector<State*> nextStates;
    vector<State*> parents;

    int lastMovedPieceID;
    int lastMovedPieceOldX;
    int lastMovedPieceOldY;

    State();

    int getPieceX(int pieceID);
    int getPieceY(int pieceID);
    bool isEmpty(int x, int y);
    unsigned long getHash();
    State * copy();
    void movePiece(int pieceID, int x, int y);
    void shiftPiece(int pieceID, int shiftX, int shiftY);
    bool canShiftPieceTo(int pieceID, int shiftX, int shiftY);
    bool canMovePieceTo(int pieceID, int x, int y);
    int getPieceIDAtLocation(int x, int y);
    void undo();
    void addParent(State* state);
    void addChildState(State * state);
};

bool stateInListOfStates(State * state, vector<State*> & stateList);
State * createInitialState();
bool solutionNotFound(vector<State *> & stateList);
#endif 

