#pragma once

#include "Board.hpp"
#include "Level.hpp"
#include "SDLWrappers.hpp"
#include "Score.hpp"
#include "Tetromino.hpp"

const int TETROMINO_PIXELS = 20; // pixels
const int X_MARGIN = 40;
const int Y_MARGIN = 20;

// codes used in color indexing
enum Colors { RED,
    GREEN,
    BLUE,
    YELLOW,
    MAGENTA,
    CYAN,
    ORANGE,
    BLACK,
    WHITE };

// forward declaration for drawScene
class Printer;

/*
*	Class handling rendering
*/
class Graphics {
    static const Uint8 colorCodes[9][4];

    SDLInit mInit;
    SDLWindow mWindow;
    SDLRenderer mRenderer;

public:
    Graphics();

    SDLRenderer& getRenderer();

    void clearScreen();
    void updateScreen();

    int XPixelPosition(int xPos) const;
    int YPixelPosition(int yPos) const;

    void drawRectangle(int xPos, int yPos, int width, int height, int color);
    void drawTetromino(int tetromino[4], const Blocks& blocks);
    void drawBoard(const Board& board);
    void drawScene(const Blocks& blocks, const Board& board, int currentTetromino[4], int nextTetromino[4], const Printer& printer, const Score& score, const Level& level, bool paused, bool gameOver);
};

class Printer {
    static const SDL_Color textColor;

    TTFInit mTTFInit;
    TTFFont mFont;

    SDLRenderer& mRenderer;

public:
    Printer(SDLRenderer& renderer, const std::string& fontPath);

    void print(const std::string& text, int xPos, int yPos) const;

    void printMenu() const;
    void printUI() const;
    void printScore(int score, int lines, int level) const;
    void printGameOver() const;

    void printScene(const Score& score, const Level& level, bool paused, bool gameOver) const;
};