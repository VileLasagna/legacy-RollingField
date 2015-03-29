#include "Billboard.h"
#include <GL/glut.h>


void Billboard::Draw() const
{
	glDisable(GL_LIGHTING);
	GLfloat m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX,m);
	Vec3f UP (0,1,0);
	if(!absUp)
	{
		UP = Vec3f(m[1],m[5],m[9]);
	}
	Vec3f RIGHT (m[0], m[4], m[8]);
	Vec3f RT = pos+RIGHT+UP;
	float halfsize = size/2;
	RT *= halfsize;
	Vec3f RB = pos+RIGHT-UP;
	RB *= halfsize;
	Vec3f LT = pos - RIGHT + UP;
	LT *= halfsize;
	Vec3f LB = pos - RIGHT - UP;
	LB *= halfsize;

	glBegin(GL_QUADS);

		//todo: TEXTURE COORDS
		glTexCoord2f(0,0);
		glVertex3f(LT.X(),LT.Y(),LT.Z());
		glTexCoord2f(0,1);
		glVertex3f(LB.X(),LB.Y(),LB.Z());
		glTexCoord2f(1,1);
		glVertex3f(RB.X(),RB.Y(),RB.Z());
		glTexCoord2f(1,0);
		glVertex3f(RT.X(),RT.Y(),RT.Z());

	glEnd();
	glEnable(GL_LIGHTING);
		


}