#ifndef GAME_H__
#define GAME_H__
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <Framework/GameStateMgr.h>
class Tilemap;

class Game
{
public:
	Game();
	~Game();
	void run();
};

#endif