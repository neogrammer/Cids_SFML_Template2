#ifndef TITLESTATE_H__
#define TITLESTATE_H__
#include <Framework/GameStateMgr.h>
#include <Framework/GameState.h>
class TitleState : public GameState
{
public:
	TitleState(GameStateMgr* mgr_);
	~TitleState() override final;

	void input(sf::RenderWindow& wnd, float dt)  override final;
	void update(sf::RenderWindow& wnd, float dt)  override final;
	void render(sf::RenderWindow& wnd, float dt)  override final;
	void processEvent(sf::Event& e) override final;

};

#endif