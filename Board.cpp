#include "Board.hpp"

/*
*	Sets all spaces on board to empty
*/
void Board::initBoard()
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++)
            mBoardArray[i][j] = EMPTY;
}

/*
*	Stores filled spaces of tetromino (whole matrix) to board, xPos and yPos are the coordinates of left top corner of matrix
*/
void Board::storeTetromino(int tetromino, int rotation, int xPos, int yPos)
{
    for (int j = 0; j < TETROMINO_SIZE; j++)
        for (int i = 0; i < TETROMINO_SIZE; i++)
            if (mBlocks.isFilled(tetromino, rotation, i, j))
                mBoardArray[yPos + j][xPos + i] = FILLED;
}

/*
*	Deletes row by moving all higher rows one space lower (must be done bottom to top)
*/
void Board::deleteRow(int row)
{
    for (int i = row; i > 0; i--)
        for (int j = 0; j < BOARD_WIDTH; j++)
            mBoardArray[i][j] = mBoardArray[i - 1][j];
}

/*
*	Checks if row contains only filled spaces
*/
bool Board::rowFilled(int row) const
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        if (mBoardArray[row][i] == EMPTY)
            return false;

    return true;
}

/*
*	Deletes all filled rows and calculates score based on the number of rows (must be done top to bottom)
*/
int Board::clearRows()
{
    int numRows = 0;

    for (int i = 0; i < BOARD_HEIGHT; i++)
        if (rowFilled(i)) {
            deleteRow(i);
            numRows++;
        }

    return numRows;
}

/*
*	Checks if tetromino matrix can move to coordinates xPos & yPos	
*/
bool Board::movementPossible(int tetromino, int rotation, int xPos, int yPos) const
{
    for (int j = 0; j < TETROMINO_SIZE; j++)
        for (int i = 0; i < TETROMINO_SIZE; i++)
            // only checks collisions with tetromino spaces that are filled
            if (mBlocks.isFilled(tetromino, rotation, i, j))
                //	too far left || too far right || too low || too high (all collisions with board) || board space is filled (collision with another block)
                if (xPos + i < 0 || xPos + i > BOARD_WIDTH - 1 || yPos + j > BOARD_HEIGHT - 1 || yPos + j < 0 || mBoardArray[yPos + j][xPos + i] == FILLED)
                    return false;

    return true;
}