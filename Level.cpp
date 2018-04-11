#include "Level.hpp"

/*
 *	Ups a level and speeds up the game
 *	After level 20 the game doesn't speed up
 */
void Level::levelUp()
{
    mLevel++;
    if (mLevel <= 20) {
        mDelay = static_cast<int>(mDelay * 0.9);
    }
}

void Level::resetLevel()
{
    mLevel = 0;
    mDelay = 1000;
}
