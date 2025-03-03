#include "RenderWindow.h"
#include <iostream>


void commonFunc::renderWindow(const char* p_title, int p_width, int p_height) {
	//Khởi tạo cửa sổ
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_width, p_height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window has failed to init: " << SDL_GetError << std::endl;
	}
	//Tạo renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		std::cout << "Renderer has failed to init: " << SDL_GetError() << std::endl;
	}
}

SDL_Texture* commonFunc::loadTexture(const char* p_filePath) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);
	if (texture == NULL) std::cout << "Texture has failed to load: " << IMG_GetError() << std::endl;
	return texture;
}

void commonFunc::renderTexture(SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h) {
	//mặc định là in toàn bộ texture ra
	SDL_Rect dst = { p_x, p_y, p_w, p_h };
	SDL_RenderCopy(renderer, p_tex, NULL, &dst);
}

void commonFunc::clearRenderer() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

void commonFunc::renderPresent() {
	SDL_RenderPresent(renderer);
}

void commonFunc::cleanUp() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}