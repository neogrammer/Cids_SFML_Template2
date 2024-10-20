#ifndef PLAYSTATE_H__
#define PLAYSTATE_H__
#include <Framework/GameStateMgr.h>
#include <Framework/GameState.h>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <stack>
#include <memory>
#include <array>

class PlayState : public GameState
{


	

public:

	
	PlayState() = default;
	PlayState(GameStateMgr* mgr_);
	~PlayState() override final;
	void input(sf::RenderWindow& wnd, float dt)  override final;
	void update(sf::RenderWindow& wnd, float dt)  override final;
	void render(sf::RenderWindow& wnd, float dt)  override final;
	void processEvent(sf::Event& e) override final;
};

#endif