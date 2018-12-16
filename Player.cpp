#include "Player.h"



Player::Player() :PhysicsObject(0, 0, 12, 1, 0)
{
	myTexture = NULL;
}

Player::Player(int x, int y, Texture * texture):PhysicsObject(x, y, 12, 1, 0)
{
	myTexture = texture;
}


Player::~Player()
{
}


void Player::setMovement(int x, int y)
{
	setVelX(x);
	setVelY(y);
	if (x < 0)
	{
		if (y < 0) { setAngle(315); }
		else if (y == 0) { setAngle(270); }
		else { setAngle(225); }
	}
	else if (x > 0)
	{
		if (y < 0) { setAngle(45); }
		else if (y == 0) { setAngle(90); }
		else {setAngle(135);}
	}
	else // x == 0
	{
		if (y < 0) { setAngle(0); }
		else if (y > 0) { setAngle(180); }
	}
}


void Player::render(int cameraOffsetX, int cameraOffsetY)
{
	if (myTexture == NULL) return;
	myTexture->render(getPosX() - cameraOffsetX, getPosY() - cameraOffsetY, getAngle());
}