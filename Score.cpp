#include "Score.hpp"

/*
*	Calculates score based on number of lines cleared
*/
void Score::calculateScore(int numRows, int level)
{
    mLines += numRows;

    switch (numRows) {
    case 1:
        mScore += 40 * (level + 1);
        break;
    case 2:
        mScore += 100 * (level + 1);
        break;
    case 3:
        mScore += 300 * (level + 1);
        break;
    case 4:
        mScore += 1200 * (level + 1);
    default:
        break;
    }
}

void Score::resetScore()
{
    mScore = 0;
    mLines = 0;
}