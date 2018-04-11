#pragma once

#include "Board.hpp"
#include "IO.hpp"
#include "Level.hpp"
#include "Score.hpp"
#include "Tetromino.hpp"

#include <vector>

const int DEFAULT_ROTATION = 0; // tetrominos always in this rotation
const int NEXT_X_POSITION = 13; // position of next space in block size (for rendering)
const int NEXT_Y_POSITION = 2;

/*
*	Class for handling game states
*/
class Game {
    Blocks mBlocks;
    Board mBoard;
    Score mScore;
    Level mLevel;

    Graphics& mGraphics;
    Printer& mPrinter;

    // paused game flag
    bool paused = true;
    // quit flag
    bool quit = false;

    int mCurrentTetromino[4]; // active tetromino
    int mNextTetromino[4]; // next tetromino

    // used for generating next piece
    int mVectorIndex = 0;
    std::vector<int> mRandomVector{ 0, 1, 2, 3, 4, 5, 6 };

public:
    Game(Graphics& graphics, Printer& printer)
        : mBoard(mBlocks)
        , mGraphics(graphics)
        , mPrinter(printer)
    {
        init();
    };

    void init();
    bool isGameOver() const;
    bool clearAndCheck();
    void reset();

    void nextBlock();
    int generateBlock();

    void mainLoop();

    void processKeyboard(const SDL_Event& event);
    void checkLevelUp();
};