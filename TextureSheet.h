#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>


class TextureSheet
{
public:
	TextureSheet();
	~TextureSheet();
	bool loadFromFile(std::string file, SDL_Renderer * renderer, int textureWidth = 32, int textureHeight = 32);
	void render(int x, int y, int texture);
	void free();

	inline int getWidth() { return myWidth; }
	inline int getHeight() { return myHeight; }
	inline int getTextureWidth() { return myTextureWidth; }
	inline int getTextureHeight() { return myTextureHeight; }
	inline int getTextureCount() { return myTextureCount; }
	inline std::string getFile() { return mySourceFile; }

private:
	void initRectangles();

	SDL_Texture * myTexture;
	SDL_Renderer * myRenderer;
	std::vector<SDL_Rect> myRectangles;
	int myWidth;
	int myHeight;
	int myTextureWidth;
	int myTextureHeight;
	int myTextureCount;
	int myTextureCountH;
	int myTextureCountV;
	std::string mySourceFile;
};
