#ifndef TIME_STAR_H
#define TIME_STAR_H

#include "GameObject.h"
#include "Sphere.h"
#include "Quaternion.h"

#include "GLMesh.h"

class TimeStar: public GameObject
{
public:

	TimeStar();
	TimeStar(float x, float y);
	void Draw();
	void Update();
	const char* getType() const {return "TimeStar";}
	
	void Expire();
	bool isActive() const {return Active;}

	float getValue() const {return Value;}

	const Sphere* getCollision() const {return &Collision;}

	float getHeight() const {return ModelSize;}
	void setPos(const Vec3f& p);

private:

	void init();
	Sphere Collision;
	GLMesh* Mesh;
	float Value;
	float Timer;
	Quaternion Rotation;
	float TurnSpeed;
	bool Active;
	float ModelSize;
	float heading;



};

#endif