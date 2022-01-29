#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    srand((unsigned int)time(NULL));
    Game game;

    while (game.IsRuning()) {
        game.Update();
        game.Render();
    }

    return 0;
}