#include "Tetromino.hpp"

/*
 * Matrix storing all (7) tetromios, 1 is filled block, 2 is pivot block
 */
const Tetromino Blocks::tetrominoes[7]{
    { { { { 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 2, 0, 0 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 1, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 1, 1, 2, 1, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 1, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 2, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 1, 2, 1, 1 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 } } },
        { 2, -1 } },

    { {
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 2, 1, 0 },
              { 0, 0, 1, 1, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 2, 1, 0 },
              { 0, 0, 1, 1, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 2, 1, 0 },
              { 0, 0, 1, 1, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 2, 1, 0 },
              { 0, 0, 1, 1, 0 },
              { 0, 0, 0, 0, 0 } },
      },
        { 2, -2 } },

    { {
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 1, 2, 1, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 1, 2, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 1, 2, 1, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 2, 1, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 0, 0, 0 } },
      },
        { 2, -2 } },

    { {
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 2, 1, 0 },
              { 0, 1, 1, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 1, 0, 0, 0 },
              { 0, 1, 2, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 1, 1, 0 },
              { 0, 1, 2, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 2, 1, 0 },
              { 0, 0, 0, 1, 0 },
              { 0, 0, 0, 0, 0 } },
      },
        { 2, -2 } },

    { {
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 1, 2, 0, 0 },
              { 0, 0, 1, 1, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 1, 2, 0, 0 },
              { 0, 1, 0, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 1, 1, 0, 0 },
              { 0, 0, 2, 1, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 1, 0 },
              { 0, 0, 2, 1, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 0, 0, 0 } },
      },
        { 3, -2 } },

    { {
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 2, 0, 0 },
              { 0, 1, 1, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 1, 0, 0, 0 },
              { 0, 1, 2, 1, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 1, 1, 0 },
              { 0, 0, 2, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 1, 2, 1, 0 },
              { 0, 0, 0, 1, 0 },
              { 0, 0, 0, 0, 0 } },
      },
        { 3, -1 } },

    { {
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 2, 0, 0 },
              { 0, 0, 1, 1, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 1, 2, 1, 0 },
              { 0, 1, 0, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 1, 1, 0, 0 },
              { 0, 0, 2, 0, 0 },
              { 0, 0, 1, 0, 0 },
              { 0, 0, 0, 0, 0 } },
          { { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 1, 0 },
              { 0, 1, 2, 1, 0 },
              { 0, 0, 0, 0, 0 },
              { 0, 0, 0, 0, 0 } },
      },
        { 2, -1 } }
};

/*
 *	Checks if tertomino (in current rotation) has 1, or 2 in it's matrix at xPos (column) and yPos (row)
 */
bool Blocks::isFilled(int tetromino, int rotation, int xPos, int yPos) const
{
    return tetrominoes[tetromino].mRotations[rotation][yPos][xPos] != 0;
}

/*
 *	Gets initial xPosition (column on board) of tetromino
 */
int Blocks::getInitialXPos(int tetromino) const
{
    return tetrominoes[tetromino].mInitialPosition[0];
}

/*
*	Gets initial yPosition (row on board) of tetromino
*/
int Blocks::getInitialYPos(int tetromino) const
{
    return tetrominoes[tetromino].mInitialPosition[1];
}