#include "LevelMap.h"

#include <fstream>
#include <iostream>

LevelMap::LevelMap()
{
}


LevelMap::~LevelMap()
{
}


bool LevelMap::loadTestMap(SDL_Renderer * renderer)
{
	myRenderer = renderer;
	myTileWidth = 32;
	myTileHeight = 32;
	myTileCountX = 16;
	myTileCountY = 16;
	myTileCount = myTileCountX*myTileCountY;
	myLevelWidth = myTileCountX*myTileWidth;
	myLevelHeight = myTileCountY*myTileHeight;
	myFloorMap = std::vector<int>(myTileCount);
	for (int i = 0; i < myTileCount; i++)
	{
		myFloorMap[i] = i;
	}
	myCeilingMap = std::vector<int>(myTileCount);
	for (int i = 0; i < myTileCount; i++)
	{
		myCeilingMap[i] = -1;
	}
	myNavMap = std::vector<int>(myTileCount);
	for (int i = 0; i < myTileCount; i++)
	{
		myNavMap[i] = 1;
	}
	return myTextureSheet.loadFromFile("res/sprites/terrain/test.png", renderer, 32, 32);
}


bool LevelMap::validateObject(json obj)
{
	if (!obj["width"].is_number())
	{
		printf("terrain.width must be a number!\n");
		return false;
	}
	if (!obj["height"].is_number())
	{
		printf("terrain.height must be a number!\n");
		return false;
	}
	if (!obj["spritesheet"].is_string())
	{
		printf("terrain.spritesheet must be a string!\n");
		return false;
	}
	if (!obj["floorSprites"].is_array())
	{
		printf("terrain.floorSprites must be an array!\n");
		return false;
	}
	if (!obj["roofSprites"].is_array())
	{
		printf("terrain.roofSprites must be an array!\n");
		return false;
	}
	if (!obj["navigable"].is_array())
	{
		printf("terrain.navigable must be an array!\n");
		return false;
	}
	return true;
}


bool LevelMap::load(json levelData, SDL_Renderer * renderer)
{
	try
	{
		if (!validateObject(levelData)) return false;
		myRenderer = renderer;
		myTileWidth = 32;
		myTileHeight = 32;
		myTileCountX = levelData["width"];
		myTileCountY = levelData["height"];
		myTileCount = myTileCountX*myTileCountY;
		myLevelWidth = myTileCountX*myTileWidth;
		myLevelHeight = myTileCountY*myTileHeight;

		myFloorMap = levelData["floorSprites"];
		myCeilingMap = levelData["roofSprites"];
		myNavMap = levelData["navigable"];

		std::string spritesheet = levelData["spritesheet"];
		myTextureSheet.loadFromFile("res/sprites/terrain/" + spritesheet, renderer, 32, 32);
		return true;
	}
	catch(...)
	{
		printf("Error parsing json file");
		return false;
	}
}


bool LevelMap::loadFile(std::string levelFile, SDL_Renderer * renderer)
{
	try{
		std::ifstream jsonFile;
		jsonFile.open(levelFile);
		json levelData;
		jsonFile >> levelData;
		jsonFile.close();
		return load(levelData["terrain"], renderer);
	}
	catch (...)
	{
		printf("Error parsing json file");
		return false;
	}
}


void LevelMap::renderFloor(int cameraOffsetX, int cameraOffsetY)
{
	int i = 0;
	for (int y = 0; y < myTileCountY; y++)
	{
		for (int x = 0; x < myTileCountX; x++)
		{
			myTextureSheet.render(x*myTileWidth - cameraOffsetX, y*myTileHeight - cameraOffsetY, myFloorMap[i++]);
		}
	}
}


void LevelMap::renderCeiling(int cameraOffsetX, int cameraOffsetY)
{
	int i = 0;
	for (int y = 0; y < myTileCountY; y++)
	{
		for (int x = 0; x < myTileCountX; x++)
		{
			myTextureSheet.render(x*myTileWidth - cameraOffsetX, y*myTileHeight - cameraOffsetY, myCeilingMap[i++]);
		}
	}
}