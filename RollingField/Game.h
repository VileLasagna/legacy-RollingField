#ifndef GAME_H
#define GAME_H

#include <Vector>
#include <String>
#include <fstream>
#include <map>
#include <set>
#include <utility>
#include "Err.h"
#include "StringProc.h"
#include "DisplayManager.h"
#include "GameState.h"
#include "TTFManager.h"
#include "GameObject.h"
#include "Factory.h"
#include "ConfigLoader.h"


typedef enum GOIT{GOIT_ALL = 0, GOIT_ACTIVE = 1, GOIT_DRAWN = 2};

struct ObjStatus { bool draw; bool update; ObjStatus(bool DRAW = false, bool UPDATE = false):draw(DRAW),update(UPDATE){}};
class CollisionSystem; //CollisionSystem.h
typedef std::multimap<std::string,std::pair<GameObject*,ObjStatus>> ObjectMap; //maps a typename to pointers to gameobjects and wether they should be drawn and updated


class Game
{
private:	//This class is a singleton.
	Game();
	Game operator= (const Game&);
	Game (const Game&);

public:

	static Game* instance();
	void Run();
	void addState(GameState* g);
	static void Clear();
	void showFPS(bool fps = true) {FPS = fps;}

	bool setDrawnTypes(const std::set<std::string>& types); //sets all(and only the) ObjectTypes in "types" to be drawn. Returns false if no objects are active then.
	bool setActiveTypes(const std::set<std::string>& types);//sets all(and only the) ObjectTypes in "types" to be updated. Returns false if no objects are active then.
	void DrawObjects();
	void UpdateObjects();

	~Game();



	class iterator	//iterator class to the GameObjectCollection
	{
	public:
		iterator(std::string type = "", int flag = GOIT_ALL);
		bool Next();
		bool Prev();
		bool Find(std::string key);
		void Begin();
		void End();
		const std::string& Type() const {return current->first;}
		bool isEmpty();
		bool isActive();
		bool isDrawn();
		operator GameObject*() {return current->second.first;}
		GameObject* operator->() {return current->second.first;}

	private:

		friend class Game;
		ObjectMap::iterator begin, current, end;
		int mode;
		std::string type;

	};

	void removeObject(Game::iterator it);
	void removeObject(std::string type);
	void addObject(std::string type, GameObject* object);
	void resetState(int i);

	

private:

	
	friend class GameState;
	friend class ConfigLoader;
	int Update();
	void Draw();
	void Flip();
	

	CollisionSystem* CS;
	std::vector<GameState*> states; //Note: State 0 is ALWAYS the program starting point
	ObjectMap Objects;
	Factory<GameObject>* GOFactory;
	int currentState;
	bool FPS;
	void drawFPS();
	unsigned int frames;
	unsigned int updates;
	unsigned int minFPS;
	



};

#endif //GAME_H