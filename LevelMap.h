#pragma once

#include <SDL.h>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "TextureSheet.h"

class LevelMap
{
public:
	LevelMap();
	LevelMap(json levelData, SDL_Renderer * renderer) { load(levelData, renderer); }
	LevelMap(std::string levelFile, SDL_Renderer * renderer) { load(levelFile, renderer); };
	~LevelMap();

	bool loadTestMap(SDL_Renderer * renderer);
	bool load(json levelData, SDL_Renderer * renderer);
	bool load(json levelData, SDL_Renderer * renderer, int playerStartX, int PlayerStartY);
	bool loadFile(std::string levelFile, SDL_Renderer * renderer);

	void renderFloor(int cameraOffsetX, int cameraOffsetY);
	void renderCeiling(int cameraOffsetX, int cameraOffsetY);

	inline int getLevelWidth() { return myLevelWidth; };
	inline int getLevelHeight() { return myLevelHeight; }

	inline int getTileWidth() { return myTileWidth; };
	inline int getTileHeight() { return myTileHeight; };

	inline int getPlayerStartX() { return myPlayerStartX; };
	inline int getPlayerStartY() { return myPlayerStartY; };

	inline int navMapAtPoint(int x, int y) { 
		if (x < 0)return 0;
		if (x > myTileCountX)return 0;
		if (y < 0)return 0;
		if (y > myTileCountY)return 0;
		return myNavMap[y * myTileCountX + x]; 
	}

	bool validateObject(json obj);
private:
	std::vector<int> myFloorMap;
	std::vector<int> myCeilingMap;
	//Temporary, NavMap will someday get its own class with pathfinding functions.
	std::vector<int> myNavMap;
	TextureSheet myTextureSheet;
	SDL_Renderer * myRenderer;

	int myLevelWidth;
	int myLevelHeight;
	int myTileWidth;
	int myTileHeight;
	int myTileCount;
	int myTileCountX;
	int myTileCountY;
	int myPlayerStartX;
	int myPlayerStartY;
};

