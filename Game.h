#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Texture.h"


class Game
{
public:
	Game(int width, int height, std::string title);
	~Game();

	int run();
	void manageEvent(SDL_Event e);
	void render();

private:
	bool init(int width, int height, std::string title);
	bool loadMedia();
	SDL_Surface* loadSurface(std::string path);

	SDL_Window * myWindow = NULL;
	SDL_Renderer * myRenderer = NULL;
	SDL_Surface * myScreenSurface = NULL;

	//testing thingies
	Texture * myTexture = NULL;
};

