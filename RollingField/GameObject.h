
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "FileManager.h"
#include "ManagedFile.h"
#include "Vec3.h"
#include "DisplayManager.h"

class GameObject

{
public:

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ~GameObject(){};
	virtual bool Load(ManagedFile* F) {return true;}
	virtual const char* getType() const = 0;

	virtual void setVel(const Vec3f& v) { vel = v;}
	virtual void setPos(const Vec3f& p) { pos = p;}
	virtual void setAcc(const Vec3f& a) { accel = a;}

	virtual Vec3f getVel() const {return vel;}
	virtual Vec3f getPos() const {return pos;}
	virtual Vec3f getAcc() const {return accel;}


protected:

	Vec3f vel;
	Vec3f pos;
	Vec3f accel;

};

#endif //GAME_OBJECT_H