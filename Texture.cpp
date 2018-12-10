#include "Texture.h"



Texture::Texture()
{
	myTexture = NULL;
	myWidth = 0;
	myHeight = 0;
}


Texture::~Texture()
{
	free();
}


bool Texture::loadFromFile(std::string file, SDL_Renderer * renderer)
{
	free();
	SDL_Texture * newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(file.c_str()); 
	
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", file.c_str(), IMG_GetError());
		Texture::loadFromFile("res/error.png", renderer);
	}
	else
	{
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", file.c_str(), SDL_GetError());
		}
		else
		{
			myWidth = loadedSurface->w;
			myHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
		myTexture = newTexture;
	}
	return myTexture != NULL;
}


void Texture::render(int x, int y, SDL_Renderer * renderer, double angle, SDL_Point * center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, myWidth, myHeight };
	SDL_RenderCopyEx(renderer, myTexture, NULL, &renderQuad, angle, center, flip);
}


void Texture::free()
{
	if( myTexture != NULL )
	{
		SDL_DestroyTexture( myTexture );
		myTexture = NULL;
		myWidth = 0;
		myHeight = 0;
	}
}


int Texture::getWidth()
{
	return myWidth;
}


int Texture::getHeight()
{
	return myHeight;
}