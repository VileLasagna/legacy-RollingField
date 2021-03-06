#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <Vector>
#include <String>
#include <fstream>

#include "EventHandler.h"
#include "StringProc.h"
#include "SoundFX.h"
#include "SoundManager.h"

class GameState: public EventHandler
{
public:
	GameState(){}
	virtual~ GameState(){}
	virtual int Update() = 0;	 //The return value is the Game State to be run on the following update
								// Return -1 to terminate the program
	virtual void Draw() = 0; //Blit everything.

	virtual void Reset() = 0; //resets the game state;

protected:
	virtual void onQuitEvent() {ret = -1;} //Sends quit signal to "Game" container, so as to prevent leakage and enable for cleanup in main
	virtual void onKeyboardEvent(const SDL_KeyboardEvent& e) { if (e.keysym.sym == SDLK_ESCAPE) {onQuitEvent();}}
	int self; //The index of this state.
	int ret; //This is the value the update function will return. 
			//Always control this externally through EventHandler functions
			//and such, but leave the returning to the update funtion.

};



#endif //GAMESTATE_H