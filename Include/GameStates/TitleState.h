#ifndef TITLESTATE_H__
#define TITLESTATE_H__
#include <Framework/GameStateMgr.h>
#include <Framework/GameState.h>
class TitleState : public GameState
{
	int choiceNum{ 0 };
	const unsigned int chosenSize{ 44U };
	const unsigned int unchosenSize{ 44U };
	const sf::Color unchosenColor{ sf::Color::White };
	const sf::Color chosenColor{ sf::Color(0,0,255,255) };
	const sf::Vector2f positions[3] = {
		{980.f,265.f},
		{980.f,365.f},
		{980.f,465.f}
	};
public:
	TitleState(GameStateMgr* mgr_);
	~TitleState() override final;
	void input(sf::RenderWindow& wnd, float dt)  override final;
	void update(sf::RenderWindow& wnd, float dt)  override final;
	void render(sf::RenderWindow& wnd, float dt)  override final;
	void processEvent(sf::RenderWindow& wnd, sf::Event& e) override final;
};

#endif