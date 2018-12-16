#include "PhysicsObject.h"



void PhysicsObject::tick(LevelMap * enviroment)
{
	tick();

	long long int tileWidth  = enviroment->getTileWidth()  << 16;
	long long int tileHeight = enviroment->getTileHeight() << 16;
	long long int tileWidthHalf  = tileWidth  / 2;
	long long int tileHeightHalf = tileHeight / 2;

	long long int inTilePosX = ( myPosX + tileWidthHalf  ) % tileWidth;
	long long int inTilePosY = ( myPosY + tileHeightHalf ) % tileHeight;

	int tilePosX = (int)((myPosX + tileWidthHalf) / tileWidth);
	int tilePosY = (int)((myPosY + tileHeightHalf) / tileHeight);

	long long int radiusExact = myRadius << 16;

	long long int bottommost = inTilePosY + radiusExact;
	long long int leftmost = inTilePosX - radiusExact;
	long long int rightmost = inTilePosX + radiusExact;

	if(enviroment->navMapAtPoint(tilePosX, tilePosY - 1) == 0)
	{ 
		long long int topmost = inTilePosY - radiusExact;
		if (topmost < 0)
		{
			myPosY -= topmost;
		}
	}
	if (enviroment->navMapAtPoint(tilePosX, tilePosY + 1) == 0)
	{
		long long int botmost = inTilePosY + radiusExact;
		if (botmost > tileHeight)
		{
			myPosY -= botmost;
			myPosY += tileHeight;
		}
	}
	if (enviroment->navMapAtPoint(tilePosX -1, tilePosY) == 0)
	{
		long long int leftmost = inTilePosX - radiusExact;
		if (leftmost < 0)
		{
			myPosX -= leftmost;
		}
	}
	if (enviroment->navMapAtPoint(tilePosX + 1, tilePosY) == 0)
	{
		long long int rightmost = inTilePosX + radiusExact;
		if (rightmost > tileWidth)
		{
			myPosX -= rightmost;
			myPosX += tileWidth;
		}
	}
}