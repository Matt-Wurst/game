#pragma once

#include "PhysicsObject.h"
#include "Texture.h"

class Player : public PhysicsObject
{
public:
	Player();
	Player(int x, int y, Texture * texture);
	~Player();

	void setMovement(int x, int y);

	void render(int cameraOffsetX, int cameraOffsetY);

private:
	Texture * myTexture;
};

