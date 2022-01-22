#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "Game.h";

int main()
{
    srand(time(0));
    Game game;

    while (game.IsRuning()) {
        game.Update();
        game.Render();
    }

    return 0;
}