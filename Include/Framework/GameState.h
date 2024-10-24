#ifndef GAMESTATE_H__
#define GAMESTATE_H__
#include <Framework/GameStateMgr.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
class GameState
{
protected:
	bool paused;
	GameStateMgr* owner;
public:
	GameState(GameStateMgr* owner_);
	virtual ~GameState();
	virtual void processEvent(sf::RenderWindow& wnd, sf::Event& e) { return; };
	virtual void input(sf::RenderWindow& wnd, float dt) = 0;
	virtual void update(sf::RenderWindow& wnd, float dt) = 0;
	virtual void render(sf::RenderWindow& wnd, float dt) = 0;
};

#endif