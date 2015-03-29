#ifndef CAR_H
#define CAR_H

#include "Vec3.h"
#include <math.h>
#include <utility>
#include "Sphere.h"
#include "GameObject.h"
#include "GL/glut.h"



class Car: public GameObject
{
public:
	Car();
	void Draw();
	void Update();
	void Forward();
	void Reverse();
	void Turn(bool left);
	void Straight();
	void Stop();
	bool Collides(const Sphere& s);
	float getHeading() const {return heading;}
	const char* getType() const {return "CAR";}

private:

	float vel;
	float heading;
	int accel;
	int steer;
	float acc_factor;
	float max_spd;
	float turn_rate;
	float trisize;
	float triheight;
	float width;
	Vec3f verts[24];
	Vec3f normals[24];
	std::pair<Sphere,Sphere> Collision;

};

#endif //CAR_H