#ifndef ROLLING_FIELD_PLAYER_ENTITY
#define ROLLING_FIELD_PLAYER_ENTITY

#include "TimeStar.h"
#include "Billboard.h"
#include "Texture.h"
#include "SDLTTF.h"


class RFPlayer
{
public:

	RFPlayer();
	bool Update(); //returns true if time is 0;
	void Draw();
	void collect(const TimeStar& star);

private:

	float time;
	float score;
	Billboard timeHUD;
	Billboard scoreHUD;
	Texture timeTEX;
	Texture scoreTEX;
	SDLTTF* font;


};




#endif //ROLLING_FIELD_PLAYER_ENTITY