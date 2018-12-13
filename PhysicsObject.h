#pragma once


class PhysicsObject
{
public:
	PhysicsObject(int x, int y, int radius, int mass, double angle = 0 ) 
	{
		myPosX = x << 16; myPosY = y << 16;
		myVelX = 0; myVelY = 0;
		myRadius = radius;
		myMass = mass;
		myAngle = angle;
		myAngularVelocity = 0;
	}
	~PhysicsObject() {}

	inline void applyForce(int x, int y) { myVelX += (long long int)x / myMass; myVelY += (long long int)y / myMass; }
	inline void tick() { myPosX += myVelX / 60; myPosY += myVelY / 60; myAngle += myAngularVelocity / 60; }

	inline int getPosX()   { return myPosX >> 16; }
	inline int getPosY()   { return myPosY >> 16; }
	inline int getVelX()   { return myVelX >> 16; }
	inline int getVelY()   { return myVelY >> 16; }
	inline int getMass()   { return myMass; }
	inline int getRadius() { return myRadius; }
	inline double getAngle() { return myAngle; }
	inline double getAnglularVelocity() { return myAngularVelocity; }

	inline void setPosX(int x)   { myPosX = x << 16; }
	inline void setPosY(int y)   { myPosY = y << 16; }
	inline void setVelX(int vx)  { myVelX = vx << 16; }
	inline void setVelY(int vy)  { myVelY = vy << 16; }
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
		long long int xDiff = a->getPosX(); - b->getPosX();
		if (xDiff < -radiusSum) return false;
		if (xDiff >  radiusSum) return false;
		long long int yDiff = a->getPosY(); -b->getPosY();
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

