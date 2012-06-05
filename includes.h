#ifndef __INCLUDES_H__
#define __INCLUDES_H__
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <locale>
#include <algorithm>

using namespace std;

#include "State.h"
#include "Piece.h"
#include "StateDB.h"
#include "StateMiner.h"

#define RED 0
#define BLACK 1
#define YELLOW 2

#define NUM_PIECES 10
#define GAME_WIDTH 4
#define GAME_HEIGHT 5

enum PIECES { RED_SUN_PIECE, TALL_BLACK_PIECE_A, TALL_BLACK_PIECE_B, TALL_BLACK_PIECE_C, TALL_BLACK_PIECE_D, WIDE_BLACK_PIECE, YELLOW_PIECE_A, YELLOW_PIECE_B, YELLOW_PIECE_C, YELLOW_PIECE_D, NONE};

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define NO_SOLUTION 1

#endif

