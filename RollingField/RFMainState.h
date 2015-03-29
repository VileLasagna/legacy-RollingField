#ifndef ROLLING_FIELD_MAIN_STATE_H
#define ROLLING_FIELD_MAIN_STATE_H

#include "GameState.h"
#include "Car.h"
#include "Plane.h"
#include "Texture.h"
#include "Camera.h"
#include "TimeStar.h"
#include "RFPlayer.h"
#include <Vector>
#include <GL/glut.h>
//#include "GameField.h"  KILL IT! KILL IT WITH FIRE!!!! 


class RFMainState: public GameState
{

public:


	RFMainState();
	~RFMainState();

	int Update();
	void Draw();
	void Reset();

	void onMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void onMouseButtonEvent(const SDL_MouseButtonEvent& e);
	void onKeyboardEvent(const SDL_KeyboardEvent& e);


private:

	//GameField* GF;
	Car* RC;
	Plane Ground;
	Texture* BG;
	Camera ChaseCam;
	std::vector<TimeStar*> Stars;
	RFPlayer P1;
	float SpawnTimer;



};










#endif //ROLLING_FIELD_MAIN_STATE_H