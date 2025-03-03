#pragma once
#include <SDL.h>
#include <SDL_image.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Surface* surface = NULL;

namespace commonFunc {
	//Window
	void renderWindow(const char* p_title, int p_width, int p_height);

	//Texture
	SDL_Texture* loadTexture(const char* p_filePath);
	void renderTexture(SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h);



	void clearRenderer();
	void renderPresent();
	void cleanUp();
}