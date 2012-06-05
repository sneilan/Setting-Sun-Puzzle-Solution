#ifndef __PIECE_H__
#define __PIECE_H__
class Piece {
public:
    int x;
    int y;
    int w;
    int h;
    int color;

    bool pointInside(int x, int y);
    bool intersects(Piece * piece);
};
#endif

