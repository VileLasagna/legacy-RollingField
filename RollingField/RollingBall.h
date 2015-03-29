#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "GameObject.h"



class RollingBall: public GameObject
{

public:

	RollingBall();
	void Draw();
	void Update();
	const char* getType() const{return "RollingBall/0";}
	float getRadius() const {return radius;}
	void setSurfaceNormal(const Vec3f& N) {SurfaceNormal = N;}

private:

	Vec3f orient;
	float radius;
	Vec3f SurfaceNormal;


};



#endif //ROLLINGBALL_H
