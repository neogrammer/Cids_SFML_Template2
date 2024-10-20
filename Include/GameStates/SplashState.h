#ifndef SPLASHSTATE_H__
#define SPLASHSTATE_H__
#include <Framework/GameStateMgr.h>
#include <Framework/GameState.h>
class SplashState : public GameState
{
public:
	SplashState(GameStateMgr* mgr_);
	~SplashState() override final;
	void input(sf::RenderWindow& wnd, float dt)  override final;
	void update(sf::RenderWindow& wnd, float dt)  override final;
	void render(sf::RenderWindow& wnd, float dt)  override final;
	void processEvent(sf::Event& e) override final;

};

#endif