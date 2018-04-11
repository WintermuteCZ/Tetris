#pragma once

#include "Tetromino.hpp"

const int BOARD_WIDTH = 10; // in blocks
const int BOARD_HEIGHT = 20;

enum BoardSpace { EMPTY,
    FILLED };

/*
*	Class for keeping the board and basic ingame logic
*/
class Board {
public:
    int mBoardArray[BOARD_HEIGHT][BOARD_WIDTH];
    Blocks& mBlocks;

    Board(Blocks& blocks)
        : mBlocks(blocks)
    {
        initBoard();
    };

    void initBoard();
    void storeTetromino(int tetromino, int rotation, int xPos, int yPos);
    void deleteRow(int row);
    bool rowFilled(int row) const;
    int clearRows();

    bool movementPossible(int tetromino, int rotation, int xPos, int yPos) const;
};