
#include <GameStates/TitleState.h>

TitleState::TitleState(GameStateMgr* mgr_)
	: GameState(mgr_)
{
}

TitleState::~TitleState()
{
}

void TitleState::processEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::Enter)
		{
			owner->changeState(GameStateType::Play);
		}
	}
}

void TitleState::input(sf::RenderWindow& wnd, float dt)
{
}

void TitleState::update(sf::RenderWindow& wnd, float dt)
{
}



void TitleState::render(sf::RenderWindow& wnd, float dt)
{
	sf::Sprite spr;
	spr.setTexture(Cfg::textures.get((int)Cfg::Textures::Title));
	wnd.draw(spr);
}




