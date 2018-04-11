#include "IO.hpp"

#include <iostream>
#include <string>

// rgba codes for colors in Colors
const Uint8 Graphics::colorCodes[9][4]{
    { 0xFF, 0x00, 0x00, 0xFF },
    { 0x00, 0xFF, 0x00, 0xFF },
    { 0x00, 0x00, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0x00, 0xFF },
    { 0xFF, 0x00, 0xFF, 0xFF },
    { 0x00, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0x9F, 0x00, 0xFF },
    { 0x00, 0x00, 0x00, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF }
};

Graphics::Graphics() try : mRenderer(mWindow) {
    std::cout << "Graphics initialization successful" << std::endl;
} catch (std::exception& ex) {
    std::cerr << "Graphics initialization failed (" << ex.what() << ")" << std::endl;
}

SDLRenderer& Graphics::getRenderer()
{
    return mRenderer;
}

/*
*	Reset screen (with black)
*/
void Graphics::clearScreen()
{
    SDL_SetRenderDrawColor(mRenderer.getRenderer(), colorCodes[BLACK][0], colorCodes[BLACK][1], colorCodes[BLACK][2], colorCodes[BLACK][3]);
    SDL_RenderClear(mRenderer.getRenderer());
}

/*
*	Flips buffers
*/
void Graphics::updateScreen()
{
    SDL_RenderPresent(mRenderer.getRenderer());
}

/*
 *	Returns position in pixels for xPos (in block size)
 */
int Graphics::XPixelPosition(int xPos) const
{
    return X_MARGIN + (xPos * TETROMINO_PIXELS);
}

/*
 *	Returns position in pixels for yPos (in block size)
 */
int Graphics::YPixelPosition(int yPos) const
{
    return Y_MARGIN + (yPos * TETROMINO_PIXELS);
}

/*
*	Draws one rectangle, color - rgba
*/
void Graphics::drawRectangle(int xPos, int yPos, int width, int height, int color)
{
    SDL_Rect fillRect{ xPos, yPos, width, height };
    SDL_SetRenderDrawColor(mRenderer.getRenderer(), colorCodes[color][0], colorCodes[color][1], colorCodes[color][2], colorCodes[color][3]);
    SDL_RenderFillRect(mRenderer.getRenderer(), &fillRect);
}

/*
*	Calls the drawing function for each filled space of tetromino
*	tetromino[0] - type & color (index), tetromino[1] - rotation, tetromino[2] - column, tetromino[3] - row
*/
void Graphics::drawTetromino(int tetromino[4], const Blocks& blocks)
{
    int mPixelsX = XPixelPosition(tetromino[2]);
    int mPixelsY = YPixelPosition(tetromino[3]);

    for (int j = 0; j < TETROMINO_SIZE; j++)
        for (int i = 0; i < TETROMINO_SIZE; i++)
            if (blocks.isFilled(tetromino[0], tetromino[1], i, j))
                drawRectangle(mPixelsX + (i * TETROMINO_PIXELS), mPixelsY + (j * TETROMINO_PIXELS), TETROMINO_PIXELS - 1, TETROMINO_PIXELS - 1, tetromino[0]);
}

/*
*	Calls for the drawing of the well and all filled spaces of board
*/
void Graphics::drawBoard(const Board& board)
{
    drawRectangle(X_MARGIN / 2, Y_MARGIN, TETROMINO_PIXELS - 1, TETROMINO_PIXELS * BOARD_HEIGHT, WHITE);
    drawRectangle(X_MARGIN + (TETROMINO_PIXELS * BOARD_WIDTH), Y_MARGIN, TETROMINO_PIXELS - 1, TETROMINO_PIXELS * BOARD_HEIGHT, WHITE);
    drawRectangle(X_MARGIN / 2, Y_MARGIN + (TETROMINO_PIXELS * BOARD_HEIGHT), (2 * TETROMINO_PIXELS) + (TETROMINO_PIXELS * BOARD_WIDTH) - 1, TETROMINO_PIXELS - 1, WHITE);

    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++)
            if (board.mBoardArray[i][j] == FILLED)
                drawRectangle(XPixelPosition(j), YPixelPosition(i), TETROMINO_PIXELS - 1, TETROMINO_PIXELS - 1, WHITE);
}

/*
*	Main drawing loop, resets, fills and presents render
*/
void Graphics::drawScene(const Blocks& blocks, const Board& board, int currentTetromino[4], int nextTetromino[4], const Printer& printer, const Score& score, const Level& level, bool paused, bool gameOver)
{
    clearScreen(); // reset render
    drawBoard(board);
    drawTetromino(currentTetromino, blocks);
    drawTetromino(nextTetromino, blocks);
    printer.printScene(score, level, paused, gameOver);
    updateScreen(); // present render
}

// white for text, can't use colorCodes because of the type
const SDL_Color Printer::textColor{ 0xF0, 0xE1, 0x30, 0xFF };

Printer::Printer(SDLRenderer& renderer, const std::string& fontPath) try : mFont(fontPath), mRenderer(renderer) {
    std::cout << "Font initialization successful" << std::endl;
} catch (std::exception& ex) {
    std::cerr << "Font initialization failed (" << ex.what() << ")" << std::endl;
}

/*
*	creates a surface from text, texture from surface, frees the surface, renders the texture and frees it
*/
void Printer::print(const std::string& text, int xPos, int yPos) const
{
    SDL_Surface* surface = TTF_RenderText_Solid(mFont.getFont(), text.c_str(), textColor);
    SDL_Rect rect{ xPos, yPos, 0, 0 }; // 0w & 0h works, means it stretches based on text size

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer.getRenderer(), surface);

    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    SDL_RenderCopy(mRenderer.getRenderer(), texture, nullptr, &rect);

    SDL_DestroyTexture(texture);
}

void Printer::printMenu() const
{
    print("SPACE TO PLAY", 50, 70);
}

void Printer::printUI() const
{
    print("NEXT BLOCK", 280, 50);

    print("SCORE", 310, 210);

    print("LINES", 310, 270);

    print("LEVEL", 310, 330);
}

void Printer::printScore(int score, int lines, int level) const
{
    print(std::to_string(score), 340, 240);

    print(std::to_string(lines), 340, 300);

    print(std::to_string(level), 340, 360);
}

void Printer::printGameOver() const
{
    print("GAME OVER", 70, 100);
}

void Printer::printScene(const Score& score, const Level& level, bool paused, bool gameOver) const
{
    printScore(score.getScore(), score.getLines(), level.getLevel());
    if (paused) {
        printMenu(); // draws "space to play" whenever the game is paused
        if (gameOver)
            printGameOver();
    }
    printUI(); // rest of text
}
