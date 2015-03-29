#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "RollingBall.h"
#include "Plane.h"


class GameField: GameObject
{
public:

	GameField();

	~GameField();
	void Update();
	void Draw();
	void initialise();

	const char* getType() const { return "GameField";}

	void Lock(bool b, int x, int y);


	void rotate(int x, int z);

private:

	RollingBall* ballie;
	Plane field;
	Vec3f Down3;
	Vec3f LastNorm;
	Vec2f Down2;
	float angleX;
	float angleY;
	int lockX;
	int lockY;
	bool locked;
	void drawNormal();



};

#endif //GAME_FIELD_H