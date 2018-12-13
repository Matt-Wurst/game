#include "TextureSheet.h"



TextureSheet::TextureSheet()
{
	myTexture = NULL;
	myWidth = 0;
	myHeight = 0;
	myTextureWidth = 0;
	myTextureHeight = 0;
	myTextureCount = 0;
}


TextureSheet::~TextureSheet()
{
	free();
}



bool TextureSheet::loadFromFile(std::string file, SDL_Renderer * renderer, int textureWidth, int textureHeight)
{
	free();
	SDL_Texture * newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(file.c_str());
	myRenderer = renderer;
	myTextureWidth = textureWidth;
	myTextureHeight = textureHeight;
	mySourceFile = file;

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", file.c_str(), IMG_GetError());
	}
	else
	{
		myWidth = loadedSurface->w;
		myHeight = loadedSurface->h;
		if( myWidth % myTextureWidth != 0)
		{
			printf("Unable to load image %s! Image width is not a multiple of texture width!", file.c_str());
		}
		else if (myHeight % myTextureHeight != 0)
		{
			printf("Unable to load image %s! Image height is not a multiple of texture height!", file.c_str());
		}
		else
		{
			myTextureCountH = myWidth / myTextureWidth;
			myTextureCountV = myHeight / myTextureHeight;
			myTextureCount = myTextureCountH * myTextureCountV;
			initRectangles();
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", file.c_str(), SDL_GetError());
			}
			else
			{
				myTexture = newTexture;
			}
		}
		SDL_FreeSurface(loadedSurface);
	}
	return myTexture != NULL;
}



void TextureSheet::initRectangles()
{
	myRectangles = std::vector<SDL_Rect>(myTextureCount);

	int i = 0;
	for (int y = 0; y < myTextureCountV; y++)
	{
		for (int x = 0; x < myTextureCountH; x++)
		{
			myRectangles[i].x = x*myTextureWidth;
			myRectangles[i].y = y*myTextureHeight;
			myRectangles[i].w = myTextureWidth;
			myRectangles[i].h = myTextureHeight;
			//printf("Index %3d: x=%4d, y=%4d, w=%3d, h=%3d\n", i, myRectangles[i].x, myRectangles[i].y, myRectangles[i].w, myRectangles[i].h);
			i++;
		}
	}
}



void TextureSheet::render(int x, int y, int texture)
{
	if (texture < -1 || texture >= myTextureCount)
	{
		printf("Texture out of bounds!\n");
		printf("Requested TEXTURE#%d from sheet %s\n", texture, mySourceFile.c_str());
	}
	else if (texture == -1)
	{
		//do nothing. -1 means we draw nothing.
	}
	else 
	{
		SDL_Rect renderQuad = { x - myTextureWidth / 2, y - myTextureHeight / 2, myTextureWidth, myTextureHeight };
		SDL_RenderCopyEx(myRenderer, myTexture, &myRectangles[texture], &renderQuad, 0, NULL, SDL_FLIP_NONE);
	}
}



void TextureSheet::free()
{
	if (myTexture != NULL)
	{
		SDL_DestroyTexture(myTexture);
		myTexture = NULL;
		myWidth = 0;
		myHeight = 0;
		myTextureWidth = 0;
		myTextureHeight = 0;
		myTextureCount = 0;
	}
}