#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>



class Game
{
public:
	Game(int width, int height, std::string title);
	~Game();

	int run();

private:
	bool init(int width, int height, std::string title);
	bool loadMedia();
	SDL_Surface* loadSurface(std::string path);

	SDL_Window* gWindow = NULL;
	SDL_Surface* gScreenSurface = NULL;
	SDL_Surface* gPNGSurface = NULL;
};

