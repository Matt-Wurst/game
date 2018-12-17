#include "PhysicsObject.h"



long long int floorSqrt(long long int x);


/*
* Oh dear lord
* I hope noone will ever want to reverse-engineer this mess
*/
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
	
	bool checkTopLeft     = topOverlap && leftOverlap;
	bool checkTopRight    = topOverlap && rightOverlap;
	bool checkBottomLeft  = bottomOverlap && leftOverlap;
	bool checkBottomRight = bottomOverlap && rightOverlap;

	if(topOverlap)
	{ 
		if (enviroment->navMapAtPoint(tilePosX, tilePosY - 1) == 0)
		{
			myPosY -= topmost;
			myVelY = -myVelY;
			checkTopLeft = false;
			checkTopRight = false;
		}
	}
	if (bottomOverlap)
	{
		if (enviroment->navMapAtPoint(tilePosX, tilePosY + 1) == 0)
		{
			myPosY -= bottommost;
			myPosY += tileHeight;
			myVelY = -myVelY;
			checkBottomLeft = false;
			checkBottomRight = false;
		}
	}
	if (leftOverlap)
	{
		if (enviroment->navMapAtPoint(tilePosX - 1, tilePosY) == 0)
		{
			myPosX -= leftmost;
			myVelX = -myVelX;
			checkTopLeft = false;
			checkBottomLeft = false;
		}
	}
	if (rightOverlap)
	{
		if (enviroment->navMapAtPoint(tilePosX + 1, tilePosY) == 0)
		{
			myPosX -= rightmost;
			myPosX += tileWidth;
			myVelX = -myVelX;
			checkTopRight = false;
			checkBottomRight = false;
		}
	}

	if (checkTopLeft)
	{
		if (enviroment->navMapAtPoint(tilePosX - 1, tilePosY - 1) == 0)
		{
			long long int cornerX = tilePosX * tileWidth - tileWidthHalf;
			long long int cornerY = tilePosY * tileHeight - tileHeightHalf;
			long long int dx = cornerX - myPosX;
			long long int dy = cornerY - myPosY;
			long long int ds = dx * dx + dy * dy;
			long long int rs = radiusExact * radiusExact;
			if (ds < rs)
			{
				//this line needs some wonky bitshifting to prevent nasty suprises by integer overflow
				//basically, we divide it by 65536 before taking the square root, then multiplying by sqrt(65536) = 256
				//i don't want to use doubles because integers are speedy bois
				long long int d = floorSqrt(ds >> 16) << 8;

				long long int factor = (radiusExact * 260) / d;
				myPosX = cornerX - ((dx * factor) >> 8);
				myPosY = cornerY - ((dy * factor) >> 8);
			}
		}
	}

	if (checkTopRight)
	{
		if (enviroment->navMapAtPoint(tilePosX + 1, tilePosY - 1) == 0)
		{
			long long int cornerX = tilePosX * tileWidth + tileWidthHalf;
			long long int cornerY = tilePosY * tileHeight - tileHeightHalf;
			long long int dx = cornerX - myPosX;
			long long int dy = cornerY - myPosY;
			long long int ds = dx * dx + dy * dy;
			long long int rs = radiusExact * radiusExact;
			if (ds < rs)
			{
				//this line needs some wonky bitshifting to prevent nasty suprises by integer overflow
				//basically, we divide it by 65536 before taking the square root, then multiplying by sqrt(65536) = 256
				//i don't want to use doubles because integers are speedy bois
				long long int d = floorSqrt(ds >> 16) << 8;

				long long int factor = (radiusExact * 260) / d;
				myPosX = cornerX - ((dx * factor) >> 8);
				myPosY = cornerY - ((dy * factor) >> 8);
			}
		}
	}

	if (checkBottomLeft)
	{
		if (enviroment->navMapAtPoint(tilePosX - 1, tilePosY + 1) == 0)
		{
			long long int cornerX = tilePosX * tileWidth - tileWidthHalf;
			long long int cornerY = tilePosY * tileHeight + tileHeightHalf;
			long long int dx = cornerX - myPosX;
			long long int dy = cornerY - myPosY;
			long long int ds = dx * dx + dy * dy;
			long long int rs = radiusExact * radiusExact;
			if (ds < rs)
			{
				//this line needs some wonky bitshifting to prevent nasty suprises by integer overflow
				//basically, we divide it by 65536 before taking the square root, then multiplying by sqrt(65536) = 256
				//i don't want to use doubles because integers are speedy bois
				long long int d = floorSqrt(ds >> 16) << 8;

				long long int factor = (radiusExact * 260) / d;
				myPosX = cornerX - ((dx * factor) >> 8);
				myPosY = cornerY - ((dy * factor) >> 8);
			}
		}
	}

	if (checkBottomRight)
	{
		if (enviroment->navMapAtPoint(tilePosX + 1, tilePosY + 1) == 0)
		{
			long long int cornerX = tilePosX * tileWidth + tileWidthHalf;
			long long int cornerY = tilePosY * tileHeight + tileHeightHalf;
			long long int dx = cornerX - myPosX;
			long long int dy = cornerY - myPosY;
			long long int ds = dx * dx + dy * dy;
			long long int rs = radiusExact * radiusExact;
			if (ds < rs)
			{
				//this line needs some wonky bitshifting to prevent nasty suprises by integer overflow
				//basically, we divide it by 65536 before taking the square root, then multiplying by sqrt(65536) = 256
				//i don't want to use doubles because integers are speedy bois
				long long int d = floorSqrt(ds >> 16) << 8;

				long long int factor = (radiusExact * 260) / d;
				myPosX = cornerX - ((dx * factor) >> 8);
				myPosY = cornerY - ((dy * factor) >> 8);
			}
		}
	}
}



void DrawablePhysicsObject::render(int cameraOffsetX, int cameraOffsetY)
{
	if (myTexture == NULL) return;
	myTexture->render(getPosX() - cameraOffsetX, getPosY() - cameraOffsetY, getAngle());
}


/*
* Integer square root from
* https://www.geeksforgeeks.org/square-root-of-an-integer/
*
* Returns floor of square root of x      
*/
long long int floorSqrt(long long int x)
{
	// Base cases 
	if (x == 0 || x == 1)
		return x;

	// Do Binary Search for floor(sqrt(x)) 
	long long int start = 1, end = x, ans;
	while (start <= end)
	{
		long long int mid = (start + end) / 2;

		// If x is a perfect square 
		if (mid*mid == x)
			return mid;

		// Since we need floor, we update answer when mid*mid is  
		// smaller than x, and move closer to sqrt(x) 
		if (mid*mid < x)
		{
			start = mid + 1;
			ans = mid;
		}
		else // If mid*mid is greater than x 
			end = mid - 1;
	}
	return ans;
}