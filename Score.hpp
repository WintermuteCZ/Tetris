#pragma once

/*
 *	Class for keeping score, mScore is points, mLines cleared rows
 */
class Score {
    int mScore = 0;
    int mLines = 0;

public:
    int getScore() const { return mScore; };
    int getLines() const { return mLines; };
    void calculateScore(int numRows, int level);
    void resetScore();
};