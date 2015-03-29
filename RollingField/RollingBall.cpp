#include "RollingBall.h"
#include "Matrix44.h"
#include "DisplayManager.h"
#include <GL/glut.h>


RollingBall::RollingBall()
{
	vel = Vec3f(0,0,0);
	pos = Vec3f(0,0,0);
	accel = Vec3f(0,0,0);
	orient = Vec3f(0,0,0);
	radius = 0.5f;

}


void RollingBall::Update()
{
	static const float G = 3;
	float thetaZ = dotProd(Vec3f(0,SurfaceNormal.Y(),SurfaceNormal.Z()), Vec3f(0,0,1));
	float thetaX = dotProd(Vec3f(SurfaceNormal.X(),SurfaceNormal.Y(),0), Vec3f(1,0,0));
	accel = Vec3f(G*thetaX, 0, G*thetaZ);

	vel+=accel*(DisplayManager::instance()->getDtSecs());
	Vec3f inc = vel*(DisplayManager::instance()->getDtSecs());
	pos += inc;
	pos.setY(-((SurfaceNormal.X()*pos.X()) + (SurfaceNormal.Z()*pos.Z())/SurfaceNormal.Y())+radius);
	if(radius != 0)
	{
		orient += inc*(1.0f/radius);
	}
}

void RollingBall::Draw()
{
	Matrix44 rot;
	rot.setRotation(orient.X(),orient.Y(),orient.Z());
	glPushMatrix();

		glTranslatef(pos.X(),pos.Y(),pos.Z());
		rot.applyMatrix();

		GLfloat ambientM[] = {0.05,0.05,0.05, 1};
		GLfloat diffuseM[] = {0.1,0.8,0.3,1};
		GLfloat specM[] = {1,1,1,1};
		GLfloat specratio = 1024;

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambientM);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuseM);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specM);
		glMaterialf(GL_FRONT, GL_SHININESS, specratio);

		glutSolidSphere(radius, 4,4);
		//glutWireSphere(radius,5,5);

	glPopMatrix();
}


