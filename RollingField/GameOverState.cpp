#include "GameOverState.h"
#include "Game.h"


GameOverState::GameOverState()
{
	self = 2;
	ret = self;
	HUD = Billboard(3,Vec3f(0,0,0),true);
	GO = new Texture();
	GO->LoadTexture("gameover.jpg");

}

int GameOverState::Update()
{
	EventHandler::Update();
	if (ret == 1)
	{
		Game::instance()->resetState(1);
	}
	return ret;
}

void GameOverState::Draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GO->UseThisTexture();
	HUD.Draw();

}


void GameOverState::onKeyboardEvent(const SDL_KeyboardEvent &e)
{
	GameState::onKeyboardEvent(e);
	if(e.keysym.sym == SDLK_RETURN ||  e.keysym.sym == SDLK_KP_ENTER)
	{
		ret = 1;
	}
}