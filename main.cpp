#include "Game.hpp"
#include "IO.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    try {
        Graphics graphics;
        Printer printer(graphics.getRenderer(), "bansheepilotcond.ttf");
        Game game(graphics, printer);

        game.mainLoop();
    } catch (std::exception&) {
        std::cerr << "SDL error, shutting down" << std::endl;
        return 1;
    }

    return 0;
}
