#include <GameStates/PlayState.h>
#include <type_traits>
#include <string>
#include <iostream>

void PlayState::input(sf::RenderWindow& wnd, float dt)
{
}

void PlayState::update(sf::RenderWindow& wnd, float dt)
{

}



void PlayState::render(sf::RenderWindow& wnd, float dt)
{

}

PlayState::PlayState(GameStateMgr* mgr_)
	: GameState{mgr_}
{
}

void PlayState::processEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::P)
		{
			owner->changeState(GameStateType::Paused, false);
		}
	}
}

PlayState::~PlayState()
{

}

