#include <Framework/Game.h>
#include <type_traits>
#include <string>
#include <variant>
#include <functional>
#include <utility>

Game::Game()
{
}


Game::~Game()
{
}

void Game::run()
{


	sf::ContextSettings settings{};
	settings.antialiasingLevel = 8;
	sf::RenderWindow wnd{ { 1600U, 900U, 32U }, "Cid's SFML Game Temaplate", sf::Style::None, settings };

	GameStateMgr gameStateMgr;

	sf::Clock frameTimer{};

	while (wnd.isOpen())
	{
		sf::Event e;
		while (wnd.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) { wnd.close(); }
			if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Key::Escape) { wnd.close(); }
			gameStateMgr.processEvent(e);
		}
		if (!wnd.isOpen()) { break; }
		// update time
		float dt = frameTimer.restart().asSeconds();
		// handle input and script updates
		gameStateMgr.input(wnd, dt);
		// update game based on that time
		gameStateMgr.update(wnd, dt);
		wnd.clear(sf::Color::White);
		gameStateMgr.render(wnd, dt);
		wnd.display();
	}
}
