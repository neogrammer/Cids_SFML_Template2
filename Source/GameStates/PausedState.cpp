#include <GameStates/PausedState.h>
#include <iostream>

PausedState::PausedState(GameStateMgr* mgr_)
	: GameState{mgr_}
{
}

PausedState::~PausedState()
{
}

void PausedState::processEvent(sf::RenderWindow& wnd, sf::Event& e)
{

	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::P)
	{
		owner->popTop();
	}
}

void PausedState::input(sf::RenderWindow& wnd, float dt)
{
}

void PausedState::update(sf::RenderWindow& wnd, float dt)
{
}


void PausedState::render(sf::RenderWindow& wnd, float dt)
{
	/*gWnd.setView(gWnd.getDefaultView());
	std::cout << gWnd.getView().getCenter().x << std::endl;*/
	

	sf::RectangleShape screenOverlay{ {1600.f, 900.f} };

	sf::Text pausedText{};
	pausedText.setFont(Cfg::fonts.get((int)Cfg::Fonts::Title));
	pausedText.setString("Paused");
	pausedText.setCharacterSize(44U);
	pausedText.setPosition({ 750.f, 420.f });
	pausedText.setFillColor(sf::Color::Green);
	pausedText.setOutlineColor(sf::Color::Black);
	pausedText.setOutlineThickness(3);

	screenOverlay.setFillColor(sf::Color(0, 0, 0, 100));

	/*gWnd.draw(screenOverlay);
	gWnd.draw(pausedText);
	gWnd.setView(gameView);*/
	wnd.draw(screenOverlay);
	wnd.draw(pausedText);

}
