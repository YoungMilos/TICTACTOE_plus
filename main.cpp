#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"

#include "RenderWindow.h"

int main(int argc, char* argv[])
{
    Game Tictactoe;

    if (!Tictactoe.init()) return 0;
    else {
        Tictactoe.createBoard();
        while (Tictactoe.isRunning())
        {
            SDL_Event event;
            while (SDL_PollEvent(&event)) Tictactoe.handleGameInput(event);
            Tictactoe.renderBoard();
            SDL_Delay(100);
        }
    }
    
    Tictactoe.destroy();
    SDL_Quit();
    return 0;
}