#ifndef PAUSEDSTATE_H__
#define PAUSEDSTATE_H__
#include <Framework/GameStateMgr.h>
#include <Framework/GameState.h>
class PausedState : public GameState
{
public:
	PausedState(GameStateMgr* mgr_);
	~PausedState() override final;
	void input(sf::RenderWindow& wnd, float dt)  override final;
	void update(sf::RenderWindow& wnd, float dt)  override final;
	void render(sf::RenderWindow& wnd, float dt)  override final;
	void processEvent(sf::Event& e) override final;
};

#endif