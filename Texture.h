#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>



class Texture
{
public:
	Texture();
	~Texture();
	bool loadFromFile(std::string file, SDL_Renderer * renderer);
	void render(int x, int y, SDL_Renderer * renderer, double angle = 0, SDL_Point * center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void free();

	int getWidth();
	int getHeight();

private:
	SDL_Texture * myTexture;

	int myWidth;
	int myHeight;
};

