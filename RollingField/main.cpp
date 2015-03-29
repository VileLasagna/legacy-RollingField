//#include "Game.h"
//
//
//int main(int numargs, char** args)
//{
//
//
//
//	return 0;
//}


#include "DisplayManager.h"
#include "Game.h"
#include "RFMainState.h"
#include "GameOverState.h"
#include "SplashState.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{
	DisplayManager::instance()->Init(false,true);
	Game::instance()->addState(new SplashState());
	Game::instance()->addState(new RFMainState());
	Game::instance()->addState(new GameOverState());

	Game::instance()->Run();
	
   

        
    return 0;
}