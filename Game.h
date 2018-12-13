#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Texture.h"
#include "TextureLoader.h"
#include "TextureSheet.h"
#include "LevelMap.h"
#include "Player.h"

class Game
{
public:
	Game(int width, int height, std::string title);
	~Game();

	int run();
	void manageEvent(SDL_Event e);
	void render();
	void logic();

private:
	bool init(int width, int height, std::string title);
	bool loadMedia();
	SDL_Surface* loadSurface(std::string path);

	int myWidth;
	int myHeight;
	SDL_Window * myWindow = NULL;
	SDL_Renderer * myRenderer = NULL;
	SDL_Surface * myScreenSurface = NULL;
	TextureLoader * myTextureLoader;

	//testing thingies
	Texture * myTexture = NULL;
	LevelMap myLevelMap;
	Player myPlayer;
};

