#pragma once

#include "LevelMap.h"
#include "Texture.h"

class PhysicsObject
{
public:
	PhysicsObject() { myRadius = 16; myMass = 1; };
	PhysicsObject(int x, int y, int radius, int mass, double angle = 0 ) 
	{
		myPosX = (long long int)x << 16; (long long int)myPosY = y << 16;
		myVelX = (long long int)0; myVelY = (long long int)0;
		myRadius = radius;
		myMass = mass;
		myAngle = angle;
		myAngularVelocity = 0;
	}
	~PhysicsObject() {}

	inline void applyForce(int x, int y) { myVelX += (long long int)x / myMass; myVelY += (long long int)y / myMass; }
	inline void tick() { myPosX += myVelX / 60; myPosY += myVelY / 60; myAngle += myAngularVelocity / 60; }

	virtual void tick(LevelMap * enviroment);

	inline int getPosX()   { return (int)(myPosX >> 16); }
	inline int getPosY()   { return (int)(myPosY >> 16); }
	inline int getVelX()   { return (int)(myVelX >> 16); }
	inline int getVelY()   { return (int)(myVelY >> 16); }
	inline int getMass()   { return myMass; }
	inline int getRadius() { return myRadius; }
	inline double getAngle() { return myAngle; }
	inline double getAnglularVelocity() { return myAngularVelocity; }

	inline void setPosX(int x)   { myPosX = (long long int)x << 16; }
	inline void setPosY(int y)   { myPosY = (long long int)y << 16; }
	inline void setVelX(int vx)  { myVelX = (long long int)vx << 16; }
	inline void setVelY(int vy)  { myVelY = (long long int)vy << 16; }
	inline void setMass(int m)   { myMass = m; }
	inline void setRadius(int r) { myRadius = r; }
	inline void setAngle(double a) { myAngle = a; }
	inline void setAnglularVelocity(double a) { myAngularVelocity = a; }

	inline int stop() { myVelX = 0; myVelY = 0; myAngularVelocity = 0; }

	inline bool isColliding(PhysicsObject * other)
	{
		long long int radiusSum = myRadius + other->getRadius();
		long long int xDiff = myPosX - other->getPosX();
		if ( xDiff < -radiusSum ) return false;
		if ( xDiff >  radiusSum ) return false;
		long long int yDiff = myPosY - other->getPosY();
		if ( yDiff < -radiusSum) return false;
		if ( yDiff >  radiusSum) return false;
		return ((xDiff * xDiff) + (yDiff*yDiff)) < (radiusSum * radiusSum);
	}

	static inline bool isColliding(PhysicsObject * a, PhysicsObject * b)
	{
		long long int radiusSum = a->getRadius() + b->getRadius();
		long long int xDiff = a->getPosX() - b->getPosX();
		if (xDiff < -radiusSum) return false;
		if (xDiff >  radiusSum) return false;
		long long int yDiff = a->getPosY() - b->getPosY();
		if (yDiff < -radiusSum) return false;
		if (yDiff >  radiusSum) return false;
		return ((xDiff * xDiff) + (yDiff*yDiff)) < (radiusSum * radiusSum);
	}

private:
	long long int myPosX;
	long long int myPosY;
	long long int myVelX;
	long long int myVelY;
	double myAngle;
	double myAngularVelocity;
	int myMass;
	int myRadius;
};



class DrawablePhysicsObject : public PhysicsObject
{
public:
	DrawablePhysicsObject() {};
	DrawablePhysicsObject(int x, int y, int r, int m, double a = 0, Texture * t = NULL):PhysicsObject(x, y, r, m, a) { myTexture = t; }
	DrawablePhysicsObject(int x, int y, int m, double a = 0, Texture * t = NULL):PhysicsObject(x, y, t->getWidth() / 2, m, a) { myTexture = t; };

	virtual void render(int cameraOffsetX = 0, int cameraOffsetY = 0);

	Texture * getTexture() { return myTexture; }

	void setTexture(Texture * texture) { myTexture = texture; }

private:
	Texture * myTexture;
};