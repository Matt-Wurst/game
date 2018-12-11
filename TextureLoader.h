#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>

#include "Texture.h"


/* 
* Many textures will be needed multiple times. This stores them in a hashmap using their file path as key, so each file only needs to be loaded once.
* Using this, every texture will exist exactly once.
*/
class TextureLoader
{
public:
	TextureLoader(SDL_Renderer * r);
	~TextureLoader();

	Texture * load(std::string file);
	void flush();

private:
	SDL_Renderer * myRenderer;
	std::unordered_map<std::string, Texture *> myTextureMap;
};

