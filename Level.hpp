#pragma once

/*
 *	Class for calculating current level and game delay ticks
 */
class Level {
    int mLevel;
    int mDelay; //ms

public:
    Level()
        : Level(0, 1000){};

    Level(int level, int delay)
        : mLevel(level)
        , mDelay(delay){};

    int getLevel() const { return mLevel; };
    int getDelay() const { return mDelay; };
    void levelUp();
    void resetLevel();
};