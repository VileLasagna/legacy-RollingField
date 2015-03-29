#include "TimeStar.h"
#include "DisplayManager.h"



TimeStar::TimeStar()
{
	init();
}

void TimeStar::init()
{

	ModelSize = 2;
	Rotation = Quaternion(0,0,1,0);
	Value = 5;
	Timer = 8;
	TurnSpeed = 365; //Degrees per Sec;
	Collision = Sphere(pos,ModelSize*0.7);
	static GLMesh* M = new GLMesh("Star.obj",true,true,true);
	static bool B = M->setSize(ModelSize);
	//Spoiler: Will leak a Mesh. I'm in too much of rush to get this done to get around this (It'll get cleaned up after main, anyway);
	heading = 0;
	Mesh = M;
	Active = true;

}

TimeStar::TimeStar(float x, float y)
{
	init();
	setPos(Vec3f(x,ModelSize*0.7,y));
}


void TimeStar::Update()
{
	float time = DisplayManager::instance()->getDtSecs();
	//Rotation *= Quaternion(TurnSpeed*time,0,1,0);
	heading += TurnSpeed*time;
	Timer -= time;
	if (Timer <= 0)
	{
		Expire();
	}
}

void TimeStar::Draw()
{
	glPushMatrix();
		glTranslatef(pos.X(),pos.Y(),pos.Z());
		/*float f[16];
		Rotation.ToMatrix(f);
		glMultMatrixf(f);*/
		glRotatef(heading,0,1,0);
		//Collision.Draw();
		Mesh->Draw();
	glPopMatrix();
}

void TimeStar::setPos(const Vec3f& p)
{
	pos = p;
	Collision.setPos(p);
}

void TimeStar::Expire()
{
	Active = false;
}


