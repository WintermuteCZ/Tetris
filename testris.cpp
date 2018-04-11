#include "Game.hpp"
#include "IO.hpp"
#include "catch.hpp"

#include <iostream>

TEST_CASE("Blocks initial position")
{
    Blocks blocks;

    REQUIRE(blocks.getInitialXPos(4) == 3);
    REQUIRE(blocks.getInitialYPos(4) == -2);

    REQUIRE(blocks.getInitialXPos(6) == 2);
    REQUIRE(blocks.getInitialYPos(6) == -1);
}

TEST_CASE("Blocks filled")
{
    Blocks blocks;

    REQUIRE(!blocks.isFilled(0, 0, 0, 0));
    REQUIRE(blocks.isFilled(6, 0, 2, 2));
    REQUIRE(blocks.isFilled(6, 0, 2, 1));
    REQUIRE(!blocks.isFilled(6, 0, 1, 2));
    REQUIRE(blocks.isFilled(4, 3, 3, 2));
}

TEST_CASE("Level basic")
{
    Level level;

    REQUIRE(level.getDelay() == 1000);
    REQUIRE(level.getLevel() == 0);

    level.levelUp();
    REQUIRE(level.getDelay() == 900);
    REQUIRE(level.getLevel() == 1);

    level.resetLevel();
    REQUIRE(level.getDelay() == 1000);
    REQUIRE(level.getLevel() == 0);
}

TEST_CASE("Level high level")
{
    Level level(19, 100);

    REQUIRE(level.getDelay() == 100);
    REQUIRE(level.getLevel() == 19);

    level.levelUp();
    REQUIRE(level.getDelay() == 90);
    REQUIRE(level.getLevel() == 20);

    level.levelUp();
    REQUIRE(level.getDelay() == 90);
    REQUIRE(level.getLevel() == 21);
}

TEST_CASE("Score")
{
    Score score;

    REQUIRE(score.getScore() == 0);
    REQUIRE(score.getLines() == 0);

    score.calculateScore(1, 0);
    REQUIRE(score.getScore() == 40);
    REQUIRE(score.getLines() == 1);

    score.calculateScore(3, 9);
    REQUIRE(score.getScore() == 3040);
    REQUIRE(score.getLines() == 4);

    score.calculateScore(-1, -1);
    REQUIRE(score.getScore() == 3040);
    REQUIRE(score.getLines() == 3);

    score.resetScore();
    REQUIRE(score.getScore() == 0);
    REQUIRE(score.getLines() == 0);
}

TEST_CASE("Board store")
{
    Blocks blocks;
    Board board(blocks);

    REQUIRE(board.mBoardArray[0][0] == 0);
    REQUIRE(board.mBoardArray[19][9] == 0);

    board.storeTetromino(0, 0, 0, 0);
    REQUIRE(board.mBoardArray[0][0] == 0);
    REQUIRE(board.mBoardArray[1][2] == 1);
    REQUIRE(board.mBoardArray[2][2] == 1);

    board.storeTetromino(1, 2, 6, 16);
    REQUIRE(board.mBoardArray[18][9] == 1);
    REQUIRE(board.mBoardArray[19][9] == 1);
    REQUIRE(board.mBoardArray[19][8] == 1);
    REQUIRE(board.mBoardArray[19][7] == 0);
    REQUIRE(board.mBoardArray[17][9] == 0);
}

TEST_CASE("Board delete")
{
    Blocks blocks;
    Board board(blocks);

    for (int i = 0; i < BOARD_WIDTH; i++)
        board.mBoardArray[15][i] = 1;
    board.mBoardArray[13][2] = 1;
    board.mBoardArray[13][6] = 1;

    board.deleteRow(17);

    for (int i = 0; i < BOARD_WIDTH; i++)
        REQUIRE(board.mBoardArray[15][i] == 0);

    board.deleteRow(15);
    board.deleteRow(3);

    REQUIRE(board.mBoardArray[15][2] == 1);
    REQUIRE(board.mBoardArray[15][6] == 1);

    REQUIRE(board.mBoardArray[13][2] == 0);
    REQUIRE(board.mBoardArray[13][6] == 0);
}

TEST_CASE("Board filled")
{
    Blocks blocks;
    Board board(blocks);

    for (int i = 0; i < BOARD_WIDTH; i++) {
        board.mBoardArray[15][i] = 1;
        board.mBoardArray[16][i] = 1;
    }
    board.mBoardArray[16][5] = 0;

    REQUIRE(board.rowFilled(15));
    REQUIRE(!board.rowFilled(16));
    REQUIRE(!board.rowFilled(0));
}

TEST_CASE("Board clear")
{
    Blocks blocks;
    Board board(blocks);

    for (int i = 0; i < BOARD_WIDTH; i++) {
        board.mBoardArray[5][i] = 1;
        board.mBoardArray[15][i] = 1;
    }
    board.mBoardArray[0][0] = 1;

    REQUIRE(board.clearRows() == 2);
    REQUIRE(!board.rowFilled(5));
    REQUIRE(!board.rowFilled(15));
    REQUIRE(board.clearRows() == 0);
    REQUIRE(board.mBoardArray[2][0] == 1);
}

TEST_CASE("Board movement out")
{
    Blocks blocks;
    Board board(blocks);

    REQUIRE(board.movementPossible(2, 0, 4, 5));
    REQUIRE(board.movementPossible(2, 0, -1, -2));
    REQUIRE(!board.movementPossible(2, 0, -2, -2));
    REQUIRE(!board.movementPossible(2, 0, -1, -3));
    REQUIRE(!board.movementPossible(2, 0, -5, -5));
    REQUIRE(board.movementPossible(2, 3, 6, 16));
    REQUIRE(!board.movementPossible(2, 3, 7, 16));
    REQUIRE(!board.movementPossible(2, 3, 6, 17));
    REQUIRE(!board.movementPossible(2, 3, 20, 30));
}

TEST_CASE("Board block collision")
{
    Blocks blocks;
    Board board(blocks);

    for (int i = 0; i < BOARD_WIDTH; i++) {
        board.mBoardArray[0][i] = 1;
        board.mBoardArray[3][i] = 1;
    }

    REQUIRE(board.movementPossible(6, 3, 0, 4));
    REQUIRE(board.movementPossible(6, 3, 0, 6));
    REQUIRE(!board.movementPossible(6, 3, 0, -1));
    REQUIRE(!board.movementPossible(6, 3, 0, 1));
    REQUIRE(!board.movementPossible(6, 3, 0, 2));
}