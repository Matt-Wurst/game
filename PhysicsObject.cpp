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

	long long int topmost    = inTilePosY - radiusExact;
	long long int bottommost = inTilePosY + radiusExact;
	long long int leftmost   = inTilePosX - radiusExact;
	long long int rightmost  = inTilePosX + radiusExact;


	bool topOverlap = topmost < 0;
	bool bottomOverlap = bottommost > tileHeight;
	bool leftOverlap = leftmost < 0;
	bool rightOverlap = rightmost > tileWidth;
	
	bool checkTopLeft     = true;
	bool checkTopRight    = true;
	bool checkBottomLeft  = true;
	bool checkBottomRight = true;

	if(topOverlap)
	{ 
		if (enviroment->navMapAtPoint(tilePosX, tilePosY - 1) == 0)
		{
			myPosY -= topmost;
		}
	}
	if (bottomOverlap)
	{
		if (enviroment->navMapAtPoint(tilePosX, tilePosY + 1) == 0)
		{
			myPosY -= bottommost;
			myPosY += tileHeight;
		}
	}
	if (leftOverlap)
	{
		if (enviroment->navMapAtPoint(tilePosX - 1, tilePosY) == 0)
		{
			myPosX -= leftmost;
		}
	}
	if (rightOverlap)
	{
		if (enviroment->navMapAtPoint(tilePosX + 1, tilePosY) == 0)
		{
			myPosX -= rightmost;
			myPosX += tileWidth;
		}
	}
}