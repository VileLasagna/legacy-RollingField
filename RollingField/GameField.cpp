#include "GameField.h"
#include "Vec4.h"
#include "Matrix44.h"
#include "Quaternion.h"
#include "Billboard.h"
#include "Texture.h"
#include "TTFManager.h"
#include <String>
#include <GL/glut.h>
#include "DisplayManager.h"


GameField::GameField()
{

	Vec3f Normal = Vec3f(0,1,0);
	Normal.normalise();
	field = Plane(Normal,0);
	field.setDrawn(8,8,2);
	field.setColour(0.7,0.7,1);
	pos = Vec3f(0,0,0);
	vel = Vec3f(0,0,0);
	accel = Vec3f(0,0,0);
	Down3 = Vec3f(0,-1,0);
	Down2 = Vec2f(0,-1);
	ballie = new RollingBall();
	//ballie->setPos(Vec3f(8/2,ballie->getRadius(),8/2)); //just drop it in the middle of the field for now.
	initialise();

}

void GameField::Lock(bool b, int x, int y)
{
	locked = b;
	lockX = x;
	lockY = y;
	LastNorm = field.getNormal();
}

void GameField::initialise()
{
	ballie->setPos(Vec3f(0,ballie->getRadius(),0));
	angleX = (float)90/(float)DisplayManager::instance()->getSize().first;
	angleY = (float)90/(float)DisplayManager::instance()->getSize().second;
	locked = false;
	LastNorm = Vec3f(0,1,0);
	field.DrawAsWireframe(false);
	field.DrawNormal();
}

void GameField::Update()
{
	ballie->setSurfaceNormal(field.getNormal());
	ballie->Update();




}

void GameField::rotate(int x, int z)
{
	if (!locked)
	{
		return;
	}


	//field.RotateAroundOrigin(Vec3f((x-lockX)/3,0,(z-lockY)/3));
	Matrix44 mat;
	mat.setRotation((lockY-z)/3,0,(x-lockX)/3);
	Vec3f N = Matrix44::Multiply(mat,LastNorm).toVec3();
	N.normalise();
	field.setNormal(N);

}
GameField::~GameField()
{
	delete ballie;
}


void GameField::Draw()
{
	ballie->Draw();
	field.Draw();	
	drawNormal();
	
}


void GameField::drawNormal()
{
	Vec3f N = field.getNormal();
	Vec3f O = field.getOrigin();
	std::string text = "Plane Normal: " + StringProc::floatToString(N.X()) + "; " + StringProc::floatToString(N.Y()) + "; " + StringProc::floatToString(N.Z());
	std::string text2 =  "Normal mod2 : " + StringProc::floatToString(N.sqMod());
	std::string text3 = "Plane Origin: " + StringProc::floatToString(O.X()) + "; " + StringProc::floatToString(O.Y()) + "; " + StringProc::floatToString(O.Z());
	glDisable(GL_LIGHTING);
	GLfloat white[] = {1,1,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,white);
	glRasterPos2f(0, 5);
    for (unsigned int k=0; k < text.size(); k++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[k]);
    }
	glRasterPos2f(0, 4.5);
	for (unsigned int k=0; k < text2.size(); k++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text2[k]);
    }
		glRasterPos2f(0, 4);
	for (unsigned int k=0; k < text3.size(); k++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text3[k]);
    }
	

	glEnable(GL_LIGHTING);

}