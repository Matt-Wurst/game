#include "Player.h"



Player::Player() :DrawablePhysicsObject(0, 0, 32, 1, 0)
{
}

Player::Player(int x, int y, Texture * texture): DrawablePhysicsObject(x, y, 32, 1, 0, texture)
{
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