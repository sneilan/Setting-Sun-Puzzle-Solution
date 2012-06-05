#include "includes.h"

bool Piece::pointInside(int x, int y) {
    if (x >= this->x and x < this->x+this->w and y >= this->y and y < this->y+this->h)
        return true;
    return false;
}

bool Piece::intersects(Piece * piece) {
    if (this->x == piece->x and this->y == piece->y)
        return true;
    // check if any point on this piece intersects any point on the other piece
    for (int i = this->x; i < this->x+this->w; i++) {
        for (int j = this->y; j < this->y+this->h; j++) {
            if (piece->pointInside(i, j))
                return true;
        }
    }
    for (int i = piece->x; i < piece->x+piece->w; i++) {
        for (int j = piece->y; j < piece->y+piece->h; j++) {
            if (this->pointInside(i, j))
                return true;
        }
    }
    return false;
}

