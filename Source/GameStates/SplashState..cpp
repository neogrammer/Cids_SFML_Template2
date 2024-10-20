
#include <GameStates/SplashState.h>

#include <GameStates/PlayState.h>

SplashState::SplashState(GameStateMgr* mgr_)
	: GameState(mgr_)
{

}

SplashState::~SplashState()
{
}

void SplashState::processEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::Enter)
		{
			owner->changeState(GameStateType::Title);
		}
	}
}

void SplashState::input(sf::RenderWindow& wnd, float dt)
{
	
}

void SplashState::update(sf::RenderWindow& wnd, float dt)
{
}


void SplashState::render(sf::RenderWindow& wnd, float dt)
{
	sf::Sprite spr;
	spr.setTexture(Cfg::textures.get((int)Cfg::Textures::Logo));
	wnd.draw(spr);
}