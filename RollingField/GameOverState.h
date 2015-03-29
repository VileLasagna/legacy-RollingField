#ifndef RF_GAME_OVER_STATE_H
#define RF_GAME_OVER_STATE_H

#include "Billboard.h"
#include "Texture.h"
#include "GameState.h"

class GameOverState: public GameState
{

public:

	GameOverState();
	int Update();
	void Draw();
	void Reset() {ret = self;}
	void onKeyboardEvent(const SDL_KeyboardEvent& e);

private:

	Billboard HUD;
	Texture* GO;

};




#endif //RF_GAME_OVER_STATE_H