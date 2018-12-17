#pragma once

#include "PhysicsObject.h"
#include "Texture.h"

class Player : public DrawablePhysicsObject
{
public:
	Player();
	Player(int x, int y, Texture * texture);
	~Player();

	void setMovement(int x, int y);

private:
};

