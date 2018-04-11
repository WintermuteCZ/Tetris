#pragma once

/*
 *	Stores 1 tetromino in its four rotations in a 5x5 matrix and it's initial position on the board
 */
struct Tetromino {
    char mRotations[4][5][5];
    int mInitialPosition[2];
};

const int TETROMINO_SIZE = 5; // size of matrix

/*
 * Class for basic tetromino interaction
 */
class Blocks {
    static const Tetromino tetrominoes[7];

public:
    bool isFilled(int tetromino, int rotation, int xPos, int yPos) const;
    int getInitialXPos(int tetromino) const;
    int getInitialYPos(int tetromino) const;
};