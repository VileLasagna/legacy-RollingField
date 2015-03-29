#include "RFMainState.h"
#include "DisplayManager.h"
#include "Game.h"
#include <algorithm>
#include <math.h>
#include <time.h>

static float MyRand(float range)
{
	//from -range to range
    return ((float)rand() / (float)RAND_MAX * 2.0 * range - range);
}


RFMainState::RFMainState()
{

	srand(time(NULL));
	self = 1;
	ret = self;
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);


	GLfloat light_direction[] = {0, 10, 0, 1};
	GLfloat ambientL[] = {1,1,1,1};
	GLfloat diffuseL[] = {1,1,1,1};
	GLfloat specularL[] = {1,1,1,1};


	glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientL);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseL);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularL);
	//glColor3f(1,0,0);
	glViewport(0,0,DisplayManager::instance()->getSize().first,DisplayManager::instance()->getSize().second);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
	
   
    gluPerspective(60.0, (float)(DisplayManager::instance()->getSize().first)/(float)(DisplayManager::instance()->getSize().second), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.2, 0.2 ,0.2, 1);
	RC = new Car();
	Ground = Plane(Vec3f(0,1,0),-0.3);
	Ground.setColour(Vec3f(1,1,1));
	Ground.setDrawn(10,10,6);
	Ground.DrawAsWireframe(false);
	BG = new Texture();
	BG->LoadTexture("zzwolf1.tif");
	Ground.useTexture(BG,true);
	ChaseCam.setTarget(RC);
	ChaseCam.setRelativePos(Vec3f(0,10,15));
	SpawnTimer = 20;
	
}

void RFMainState::Reset()
{
	P1 = RFPlayer();
	for (int i = 0; i < Stars.size(); i++)
	{
		delete Stars[i];
	}
	Stars.clear();
	delete RC;
	RC = new Car();
	ChaseCam.setTarget(RC);
	ret = self;
	SpawnTimer = 20;

}

RFMainState::~RFMainState()
{
	delete RC;
	delete BG;
}

static bool StarExpired(TimeStar* S)
{
	return (!S->isActive());
}

int RFMainState::Update()
{
	float time = DisplayManager::instance()->getDtSecs();
	SpawnTimer +=time;
	if (SpawnTimer >= 5)
	{
		SpawnTimer = 0;
		Stars.push_back(new TimeStar(MyRand(30),MyRand(30)));
		//Stars.push_back(new TimeStar(-25,-30));
	}

	if(P1.Update())
	{
		Game::instance()->resetState(2);
		ret = 2;
	}
	
	EventHandler::Update();
	RC->Update();
	Vec3f P = RC->getPos();
	if (P.X() < -30)
	{
		P.setX(-30);
	}
	else
	{
		if (P.X() > 30)
		{
			P.setX(30);
		}
	}
	if (P.Z() < -30)
	{
		P.setZ(-30);
	}
	else
	{
		if (P.Z() > 30)
		{
			P.setZ(30);
		}
	}
	RC->setPos(P);

	ChaseCam.Update();
	for(unsigned int i = 0; i < Stars.size()&& Stars[i]; i++)
	{
		Stars[i]->Update();
		if(RC->Collides(*(Stars[i]->getCollision())))
		{
			P1.collect(*Stars[i]);
			Stars[i]->Expire();	
		}
	}
	Stars.erase(remove_if(Stars.begin(),Stars.end(),StarExpired), Stars.end());
	//GF->Update();
	return ret;
}



void RFMainState::onMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	/*GF->rotate(e.x,e.y);*/
}

void RFMainState::onMouseButtonEvent(const SDL_MouseButtonEvent& e)
{
	/*if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		GF->Lock(true, e.x, e.y);
	}
	else
	{
		GF->Lock(false, e.x, e.y);
	}*/
}

void RFMainState::onKeyboardEvent(const SDL_KeyboardEvent &e)
{
	GameState::onKeyboardEvent(e);
	switch(e.keysym.sym)
	{
	case SDLK_UP:
		{if (e.type == SDL_KEYDOWN){RC->Forward();} else{RC->Stop();} break;}
	case SDLK_DOWN:
		{if (e.type == SDL_KEYDOWN){RC->Reverse();} else{RC->Stop();} break;}
	case SDLK_LEFT:
		{if (e.type == SDL_KEYDOWN){RC->Turn(true);} else{RC->Straight();} break;}
	case SDLK_RIGHT:
		{if (e.type == SDL_KEYDOWN){RC->Turn(false);} else{RC->Straight();} break;}
	}

}

void RFMainState::Draw()
{

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	//TODO: Projection and viewports need to be managed externally
    gluPerspective(60.0, (float)(DisplayManager::instance()->getSize().first)/(float)(DisplayManager::instance()->getSize().second), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	ChaseCam.Use();
	for(unsigned int i = 0; i < Stars.size(); i++)
	{
		Stars[i]->Draw();
	}

	
	RC->Draw();


	glDisable(GL_LIGHTING);
	Ground.Draw();
	glEnable(GL_LIGHTING);
	P1.Draw();
	
	//GF->Draw();
	//Game::DrawObjects();
}