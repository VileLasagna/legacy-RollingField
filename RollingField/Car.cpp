#define _USE_MATH_DEFINES
#define PIOVERSIX 0.5235
#define ROOTOFTHREE 1.732
#include "car.h"






Car::Car()

{
	acc_factor = 0.005f;
	max_spd = 0.2;
	turn_rate = -1.5;
	vel = 0;
	steer = 0;
	heading = 0;
	trisize = 1;
	width = 1.3;
	float radius = 1.5;
	triheight = trisize*ROOTOFTHREE*0.5;
	accel = 0;
	Vec3f V[] = 
	{	
		//Panel 1 BEGIN
		//0
		Vec3f(-3*trisize/2,	triheight,	width/2),
		//1
		Vec3f(-3*trisize/2,	0,			width/2),
		//2
		Vec3f(-trisize,		triheight,	width/2),
		//3
		Vec3f(-trisize/2,	0,			width/2),
		//4
		Vec3f(0,			triheight,	width/2),
		//5
		Vec3f(trisize/2,	0,			width/2),
		//6
		Vec3f(trisize,		triheight,	width/2),
		//7
		Vec3f(3*trisize/2,	0,			width/2),
		//8
		Vec3f(2*trisize,	triheight,	width/2),
		//9
		Vec3f(2*trisize,	0,			width/2),
		//10
		Vec3f(-trisize/2,	2*triheight,width/2),
		//11
		Vec3f(trisize/2,	2*triheight,width/2),
		//Panel 1 END

		//Panel 2 BEGIN
		//12
		Vec3f(-3*trisize/2,	triheight,	-width/2),
		//13
		Vec3f(-3*trisize/2,	0,			-width/2),
		//14
		Vec3f(-trisize,		triheight,	-width/2),
		//15
		Vec3f(-trisize/2,	0,			-width/2),
		//16
		Vec3f(0,			triheight,	-width/2),
		//17
		Vec3f(trisize/2,	0,			-width/2),
		//18
		Vec3f(trisize,		triheight,	-width/2),
		//19
		Vec3f(3*trisize/2,	0,			-width/2),
		//20
		Vec3f(2*trisize,	triheight,	-width/2),
		//21
		Vec3f(2*trisize,	0,			-width/2),
		//22
		Vec3f(-trisize/2,	2*triheight,-width/2),
		//23
		Vec3f(trisize/2,	2*triheight,-width/2),
		//Panel 1 END
	};

	Vec3f N[] = 
	{
		//0
		Vec3f(-1,1,1),
		//1
		Vec3f(-1,0,1),
		//2
		Vec3f(-1,1,1),
		//3
		Vec3f(0,0,1),
		//4
		Vec3f(0,0,1),
		//5
		Vec3f(0,0,1),
		//6
		Vec3f(1,1,1),
		//7
		Vec3f(0,0,1),
		//8
		Vec3f(1,1,1),
		//9
		Vec3f(1,0,1),
		//10
		Vec3f(-1,1,1),
		//11
		Vec3f(1,1,1),

		//12
		Vec3f(-1,1,-1),
		//13
		Vec3f(-1,0,-1),
		//14
		Vec3f(-1,1,-1),
		//15
		Vec3f(0,0,-1),
		//16
		Vec3f(0,0,-1),
		//17
		Vec3f(0,0,-1),
		//18
		Vec3f(1,1,-1),
		//19
		Vec3f(0,0,-1),
		//20
		Vec3f(1,1,-1),
		//21
		Vec3f(1,0,-1),
		//22
		Vec3f(-1,1,-1),
		//23
		Vec3f(1,1,-1),

	};

	for (int i = 0; i<24; i++)
	{
		N[i].normalise();
		normals[i] = N[i];
		verts[i] = V[i];
		//NO, I can't believe I had to do it THIS way either T_T
	}
	Collision.first.setRadius(radius);
	//Collision.second.setRadius(radius);



}




void Car::Update()
{
	if(accel > 0 || (accel==0 && vel < 0))
	{
		vel+= acc_factor;
	}
	if(accel < 0 || (accel==0 && vel > 0) )
	{
		vel -= acc_factor;
	}
	
	if(accel==0 && vel < 0)
	{
		if (vel > -acc_factor)
		{
			vel = 0;
		}
		else
		{
			vel+= acc_factor;
		}
	}
	if(accel==0 && vel > 0)
	{
		if (vel < acc_factor)
		{
			vel = 0;
		}
		else
		{
			vel-= acc_factor;
		}
	}
	
	if (vel > max_spd)
	{
		vel = max_spd;
	}
	if (vel < (-max_spd) )
	{
		vel = -max_spd;
	}
	heading += steer*turn_rate;
	pos += Vec3f(vel*(cos(heading*0.017)), 0 ,-vel*(sin(heading*0.017)) );
	Collision.first.setPos(getPos().X(),getPos().Y()/*+Collision.first.getRadius()*/,getPos().Z());
	//Collision.second.setPos(getPos().X(),getPos().Y()/*+Collision.second.getRadius()*/,getPos().Z());
}

void Car::Forward()
{
	accel = 1;
}

void Car::Reverse()
{
	accel = -1;
}

void Car::Stop()
{
	accel = 0;
}

void Car::Turn(bool left)
{
	if (left)
	{
		steer = -1;
	}
	else
	{
		steer = 1;
	}
}

void Car::Straight()
{
	steer = 0;
}

bool Car::Collides(const Sphere& s)
{
	return(Collision.first.collides(s) || Collision.second.collides(s));

}

void Car::Draw()
{
	

	//glDisable(GL_COLOR);
	glPushMatrix();
		glColor3f(1,1,1);
		//set base position and heading
		glTranslatef(pos.X(),pos.Y(),pos.Z());
		glRotatef(heading, 0, 1, 0);
		//Collision.first.Draw();
		
		GLfloat ambientM[] = {0.05,0.05,0.05, 1};
		GLfloat diffuseM[] = {0.1,0.8,0.3,1};
		GLfloat specM[] = {0,0,0,1};
		GLfloat specratio = 100;
		

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambientM);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuseM);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specM);
		glMaterialf(GL_FRONT, GL_SHININESS, specratio);


		glBegin(GL_TRIANGLE_STRIP);
			for(int i = 0; i < 10; i++)
			{
				glNormal3f(normals[i].X(),normals[i].Y(),normals[i].Z());
				glVertex3f(verts[i].X(),verts[i].Y(),verts[i].Z());
			}
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
			for(int i = 12; i < 22; i++)
			{
				glNormal3f(normals[i].X(),normals[i].Y(),normals[i].Z());
				glVertex3f(verts[i].X(),verts[i].Y(),verts[i].Z());
			}
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
			
			glNormal3f(normals[6].X(),normals[6].Y(),normals[6].Z());
			glVertex3f(verts[6].X(),verts[6].Y(),verts[6].Z());
			glNormal3f(normals[11].X(),normals[11].Y(),normals[11].Z());
			glVertex3f(verts[11].X(),verts[11].Y(),verts[11].Z());
			glNormal3f(normals[4].X(),normals[4].Y(),normals[4].Z());
			glVertex3f(verts[4].X(),verts[4].Y(),verts[4].Z());
			glNormal3f(normals[10].X(),normals[10].Y(),normals[10].Z());
			glVertex3f(verts[10].X(),verts[10].Y(),verts[10].Z());
			glNormal3f(normals[2].X(),normals[2].Y(),normals[2].Z());
			glVertex3f(verts[2].X(),verts[2].Y(),verts[2].Z());

		glEnd();

		glBegin(GL_TRIANGLE_STRIP);

			glNormal3f(normals[18].X(),normals[18].Y(),normals[18].Z());
			glVertex3f(verts[18].X(),verts[18].Y(),verts[18].Z());
			glNormal3f(normals[23].X(),normals[23].Y(),normals[23].Z());
			glVertex3f(verts[23].X(),verts[23].Y(),verts[23].Z());
			glNormal3f(normals[16].X(),normals[16].Y(),normals[16].Z());
			glVertex3f(verts[16].X(),verts[16].Y(),verts[16].Z());
			glNormal3f(normals[22].X(),normals[22].Y(),normals[22].Z());
			glVertex3f(verts[22].X(),verts[22].Y(),verts[22].Z());
			glNormal3f(normals[14].X(),normals[14].Y(),normals[14].Z());
			glVertex3f(verts[14].X(),verts[14].Y(),verts[14].Z());

		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
			
			glNormal3f(normals[9].X(),normals[9].Y(),normals[9].Z());
			glVertex3f(verts[9].X(),verts[9].Y(),verts[9].Z());
			glNormal3f(normals[21].X(),normals[21].Y(),normals[21].Z());
			glVertex3f(verts[21].X(),verts[21].Y(),verts[21].Z());
			glNormal3f(normals[8].X(),normals[8].Y(),normals[8].Z());
			glVertex3f(verts[8].X(),verts[8].Y(),verts[8].Z());
			glNormal3f(normals[20].X(),normals[20].Y(),normals[20].Z());
			glVertex3f(verts[20].X(),verts[20].Y(),verts[20].Z());
			glNormal3f(normals[6].X(),normals[6].Y(),normals[6].Z());
			glVertex3f(verts[6].X(),verts[6].Y(),verts[6].Z());
			glNormal3f(normals[18].X(),normals[18].Y(),normals[18].Z());
			glVertex3f(verts[18].X(),verts[18].Y(),verts[18].Z());

		glEnd();

		GLfloat GLASS_A[] = {0.0,0.05,0.07, 1};
		GLfloat GLASS_D[] = {0.1,0.7,1,1};
		specratio = 50;

		glMaterialfv(GL_FRONT, GL_AMBIENT, GLASS_A);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, GLASS_D);
		glMaterialf(GL_FRONT, GL_SHININESS, specratio);

		glBegin(GL_TRIANGLE_STRIP);
	
			glNormal3f(normals[6].X(),normals[6].Y(),normals[6].Z());
			glVertex3f(verts[6].X(),verts[6].Y(),verts[6].Z());
			glNormal3f(normals[18].X(),normals[18].Y(),normals[18].Z());
			glVertex3f(verts[18].X(),verts[18].Y(),verts[18].Z());
			glNormal3f(normals[11].X(),normals[11].Y(),normals[11].Z());
			glVertex3f(verts[11].X(),verts[11].Y(),verts[11].Z());
			glNormal3f(normals[23].X(),normals[23].Y(),normals[23].Z());
			glVertex3f(verts[23].X(),verts[23].Y(),verts[23].Z());

		glEnd();

		specratio = 100;

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambientM);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuseM);
		glMaterialf(GL_FRONT, GL_SHININESS, specratio);

		glBegin(GL_TRIANGLE_STRIP);

			glNormal3f(normals[11].X(),normals[11].Y(),normals[11].Z());
			glVertex3f(verts[11].X(),verts[11].Y(),verts[11].Z());
			glNormal3f(normals[23].X(),normals[23].Y(),normals[23].Z());
			glVertex3f(verts[23].X(),verts[23].Y(),verts[23].Z());
			glNormal3f(normals[10].X(),normals[10].Y(),normals[10].Z());
			glVertex3f(verts[10].X(),verts[10].Y(),verts[10].Z());
			glNormal3f(normals[22].X(),normals[22].Y(),normals[22].Z());
			glVertex3f(verts[22].X(),verts[22].Y(),verts[22].Z());

		glEnd();

		specratio = 100;

		glMaterialfv(GL_FRONT, GL_AMBIENT, GLASS_A);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, GLASS_D);
		glMaterialf(GL_FRONT, GL_SHININESS, specratio);

		glBegin(GL_TRIANGLE_STRIP);

			glNormal3f(normals[10].X(),normals[10].Y(),normals[10].Z());
			glVertex3f(verts[10].X(),verts[10].Y(),verts[10].Z());
			glNormal3f(normals[22].X(),normals[22].Y(),normals[22].Z());
			glVertex3f(verts[22].X(),verts[22].Y(),verts[22].Z());
			glNormal3f(normals[2].X(),normals[2].Y(),normals[2].Z());
			glVertex3f(verts[2].X(),verts[2].Y(),verts[2].Z());
			glNormal3f(normals[14].X(),normals[14].Y(),normals[14].Z());
			glVertex3f(verts[14].X(),verts[14].Y(),verts[14].Z());

		glEnd();

		specratio = 100;

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambientM);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuseM);
		glMaterialf(GL_FRONT, GL_SHININESS, specratio);

		glBegin(GL_TRIANGLE_STRIP);
			
			glNormal3f(normals[2].X(),normals[2].Y(),normals[2].Z());
			glVertex3f(verts[2].X(),verts[2].Y(),verts[2].Z());
			glNormal3f(normals[14].X(),normals[14].Y(),normals[14].Z());
			glVertex3f(verts[14].X(),verts[14].Y(),verts[14].Z());
			glNormal3f(normals[0].X(),normals[0].Y(),normals[0].Z());
			glVertex3f(verts[0].X(),verts[0].Y(),verts[0].Z());
			glNormal3f(normals[12].X(),normals[12].Y(),normals[12].Z());
			glVertex3f(verts[12].X(),verts[12].Y(),verts[12].Z());
			glNormal3f(normals[1].X(),normals[1].Y(),normals[1].Z());
			glVertex3f(verts[1].X(),verts[1].Y(),verts[1].Z());
			glNormal3f(normals[13].X(),normals[13].Y(),normals[13].Z());
			glVertex3f(verts[13].X(),verts[13].Y(),verts[13].Z());
			glNormal3f(normals[3].X(),normals[3].Y(),normals[3].Z());
			glVertex3f(verts[3].X(),verts[3].Y(),verts[3].Z());
			glNormal3f(normals[15].X(),normals[15].Y(),normals[15].Z());
			glVertex3f(verts[15].X(),verts[15].Y(),verts[15].Z());
			glNormal3f(normals[5].X(),normals[5].Y(),normals[5].Z());
			glVertex3f(verts[5].X(),verts[5].Y(),verts[5].Z());
			glNormal3f(normals[17].X(),normals[17].Y(),normals[17].Z());
			glVertex3f(verts[17].X(),verts[17].Y(),verts[17].Z());
			glNormal3f(normals[7].X(),normals[7].Y(),normals[7].Z());
			glVertex3f(verts[7].X(),verts[7].Y(),verts[7].Z());
			glNormal3f(normals[19].X(),normals[19].Y(),normals[19].Z());
			glVertex3f(verts[19].X(),verts[19].Y(),verts[19].Z());
			glNormal3f(normals[9].X(),normals[9].Y(),normals[9].Z());
			glVertex3f(verts[9].X(),verts[9].Y(),verts[9].Z());
			glNormal3f(normals[21].X(),normals[21].Y(),normals[21].Z());
			glVertex3f(verts[21].X(),verts[21].Y(),verts[21].Z());

		glEnd();


		GLfloat TIRE_A[] = {0.01,0.01,0.01, 1};
		GLfloat TIRE_D[] = {0.3,0.3,0.3,1};

		specratio = 100;

		glMaterialfv(GL_FRONT, GL_AMBIENT, TIRE_A);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, TIRE_D);
		glMaterialf(GL_FRONT, GL_SHININESS, specratio);

		glColor3f(0.2,0.2,0.2);
		glPushMatrix();
			
			glTranslatef(-trisize,0,width/2);
			glutSolidTorus(trisize/6,trisize/4,10,10);

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(trisize*1.5,0,width/2);
			glutSolidTorus(trisize/6,trisize/4,10,10);

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(-trisize,0,-width/2);
			glutSolidTorus(trisize/6,trisize/4,10,10);

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(trisize*1.5,0,-width/2);
			glutSolidTorus(trisize/6,trisize/4,10,10);

		glPopMatrix();


	glPopMatrix();
		

	glColor3f(1,1,1);
			



}
