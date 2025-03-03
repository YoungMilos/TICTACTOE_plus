#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "RenderWindow.h"
#include "Settings.h"


using namespace std;

class Game
{
private:
	SDL_Texture* cell_x;
	SDL_Texture* cell_o;
	SDL_Texture* cell_empty;
	SDL_Texture* win_up;
	SDL_Texture* win_down;
	SDL_Texture* win_horizontal;
	SDL_Texture* win_vertical;

	char gameBoard[BOARD_WIDTH][BOARD_HEIGHT];
	bool gameRunning = true;
	char nextMove = O_CELL;

public:
	bool init();
	void createBoard();
	void renderBoard();
	void resetGame();
	void move(int x, int y);
	bool isWin(int col, int row);
	void handleGameInput(SDL_Event& event);
	bool isRunning() { return gameRunning; }
	void destroy()
	{
		SDL_DestroyTexture(cell_x);
		SDL_DestroyTexture(cell_o);
		SDL_DestroyTexture(cell_empty);
	}
};
