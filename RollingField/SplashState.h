#ifndef RF_SPLASH_STATE_H
#define RF_SPLASH_STATE_H

#include "Billboard.h"
#include "Texture.h"
#include "GameState.h"

class SplashState: public GameState
{
public:

	SplashState(){}
	int Update(){return 1;}
	void Draw(){}
	void Reset(){}
	~SplashState(){delete TEX;}

private:

	Billboard HUD;
	Texture* TEX;
};



#endif RF_SPLASH_STATE_H