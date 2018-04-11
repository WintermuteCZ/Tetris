#include "Game.hpp"

#include <algorithm>
#include <random>

/*
*	Generates first and second tetromino
*/
void Game::init()
{
    mCurrentTetromino[0] = generateBlock();
    mCurrentTetromino[1] = DEFAULT_ROTATION;
    mCurrentTetromino[2] = mBlocks.getInitialXPos(mCurrentTetromino[0]);
    mCurrentTetromino[3] = mBlocks.getInitialYPos(mCurrentTetromino[0]);

    mNextTetromino[0] = generateBlock();
    mNextTetromino[1] = DEFAULT_ROTATION;
    mNextTetromino[2] = NEXT_X_POSITION;
    mNextTetromino[3] = NEXT_Y_POSITION;
}

/*
*	Checks if top row only contains free spaces
*/
bool Game::isGameOver() const
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        if (mBoard.mBoardArray[0][i] == FILLED)
            return true;

    return false;
}

/*
*	Checks if game is over, if not, clears rows, updates level and generates next tetromino
*	Called after storing current tetromino in board
*/
bool Game::clearAndCheck()
{
    if (isGameOver())
        return false;

    int clearedRows = mBoard.clearRows();
    if (clearedRows > 0) {
        mScore.calculateScore(clearedRows, mLevel.getLevel());
        checkLevelUp();
    }
    nextBlock();

    return true;
}

/*
*	Resets game
*/
void Game::reset()
{
    mBoard.initBoard();
    mScore.resetScore();
    mLevel.resetLevel();
    init();
}

/*
*	sets next tetromino as current and generates another one
*/
void Game::nextBlock()
{
    mCurrentTetromino[0] = mNextTetromino[0];
    mCurrentTetromino[1] = mNextTetromino[1];
    mCurrentTetromino[2] = mBlocks.getInitialXPos(mCurrentTetromino[0]);
    mCurrentTetromino[3] = mBlocks.getInitialYPos(mCurrentTetromino[0]);

    mNextTetromino[0] = generateBlock();
    mNextTetromino[1] = DEFAULT_ROTATION;
    mNextTetromino[2] = NEXT_X_POSITION;
    mNextTetromino[3] = NEXT_Y_POSITION;
}

/*
*	Generates an index for which tetromino to use next, uses vector permutation to ensure no long waiting times for specific tetromino
*	Written this way to work on initialization
*/
int Game::generateBlock()
{
    mVectorIndex++;
    mVectorIndex %= 7; // vector contains 0..6

    // if 1, either none (just initialized) or all 7 elements were used, reshuffles the vector
    if (mVectorIndex == 1) {
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(mRandomVector.begin(), mRandomVector.end(), g);
    }

    return mRandomVector.at(mVectorIndex);
}

void Game::mainLoop()
{
    SDL_Event event;
    unsigned long timer1 = SDL_GetTicks(); // timers for tetromino ticks
    unsigned long timer2 = 0;

    reset();
    // main game loop
    while (!quit) {
        mGraphics.drawScene(mBlocks, mBoard, mCurrentTetromino, mNextTetromino, mPrinter, mScore, mLevel, paused, isGameOver()); // draw everything

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                quit = true;
            else if (event.type == SDL_KEYDOWN) {
                //esc & space needs to be treated separately for pausing to work (tetromino movement has to be locked)
                if (event.key.keysym.sym == SDLK_SPACE) {
                    if (isGameOver()) // check if normal pause or game ended
                        reset();
                    paused = !paused;
                } else if (event.key.keysym.sym == SDLK_ESCAPE)
                    quit = true;
                else {
                    if (!paused)
                        processKeyboard(event);
                }
            }
        }

        if (!paused) {
            // get timestamp with every loop, if the difference is bigger than the delay, drop tetromino by 1 and reset the first timer
            timer2 = SDL_GetTicks();

            if (timer2 - timer1 > static_cast<unsigned>(mLevel.getDelay())) {
                if (mBoard.movementPossible(mCurrentTetromino[0], mCurrentTetromino[1], mCurrentTetromino[2], mCurrentTetromino[3] + 1))
                    mCurrentTetromino[3]++;
                else {
                    mBoard.storeTetromino(mCurrentTetromino[0], mCurrentTetromino[1], mCurrentTetromino[2], mCurrentTetromino[3]);

                    if (!clearAndCheck()) // update game state
                        paused = true;
                }
                timer1 = SDL_GetTicks();
            }
        }
    }
}

/*
*	Processes keyboard input for tetromino movement
*/
void Game::processKeyboard(const SDL_Event& event)
{
    switch (event.key.keysym.sym) {
    case SDLK_DOWN: // faster down
        if (mBoard.movementPossible(mCurrentTetromino[0], mCurrentTetromino[1], mCurrentTetromino[2], mCurrentTetromino[3] + 1))
            mCurrentTetromino[3]++;
        break;

    case SDLK_LEFT: // left
        if (mBoard.movementPossible(mCurrentTetromino[0], mCurrentTetromino[1], mCurrentTetromino[2] - 1, mCurrentTetromino[3]))
            mCurrentTetromino[2]--;
        break;

    case SDLK_RIGHT: // right
        if (mBoard.movementPossible(mCurrentTetromino[0], mCurrentTetromino[1], mCurrentTetromino[2] + 1, mCurrentTetromino[3]))
            mCurrentTetromino[2]++;
        break;

    case SDLK_a: // turn counter clockwise
        if (mBoard.movementPossible(mCurrentTetromino[0], (mCurrentTetromino[1] + 1) % 4, mCurrentTetromino[2], mCurrentTetromino[3]))
            mCurrentTetromino[1] = (mCurrentTetromino[1] + 3) % 4;

        break;

    case SDLK_d: // turn clockwise
        if (mBoard.movementPossible(mCurrentTetromino[0], (mCurrentTetromino[1] + 1) % 4, mCurrentTetromino[2], mCurrentTetromino[3]))
            mCurrentTetromino[1] = (mCurrentTetromino[1] + 1) % 4;

        break;

    case SDLK_LCTRL: // drop tetromino
        while (mBoard.movementPossible(mCurrentTetromino[0], mCurrentTetromino[1], mCurrentTetromino[2], mCurrentTetromino[3] + 1))
            mCurrentTetromino[3]++;
        mBoard.storeTetromino(mCurrentTetromino[0], mCurrentTetromino[1], mCurrentTetromino[2], mCurrentTetromino[3]);
        if (!clearAndCheck()) // do immediate check to bypass delay timers (no hanging tetrominos)
            paused = true;
        break;
    }
}

void Game::checkLevelUp()
{
    if (mScore.getLines() >= (mLevel.getLevel() + 1) * 10)
        mLevel.levelUp();
}
