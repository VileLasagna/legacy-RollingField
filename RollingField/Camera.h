
#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "GameObject.h"
#include <GL/gl.h>

class Camera: public GameObject
{
public:

	Camera();
	void Update();
	void Draw();
	void Use();
	const char* getType() const {return "Camera";}

	void setTarget(const Vec3f& targetPos);
	void setTarget(const GameObject* targetObject);
	void setRelativePos(const Vec3f& Relative); //Relative Position to a targeted Object
	Vec3f getRelativePos() const {return relativePos;}

private:

	Vec3f up;
	const GameObject* targetObj;
	Vec3f target;
	Vec3f relativePos;


	




};

#endif //CAMERA_H