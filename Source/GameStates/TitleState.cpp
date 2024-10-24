
#include <GameStates/TitleState.h>

TitleState::TitleState(GameStateMgr* mgr_)
	: GameState(mgr_)
{
}

TitleState::~TitleState()
{
}

void TitleState::processEvent(sf::RenderWindow& wnd, sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::Enter)
		{
			if (choiceNum == 0)
				owner->changeState(GameStateType::Play);
			else if (choiceNum == 2)
				wnd.close();
			else if (choiceNum == 1)
				int i = 0;
		}
		else if (e.key.code == sf::Keyboard::Up)
		{
			if (choiceNum > 0)
				--choiceNum;
		}
		else if (e.key.code == sf::Keyboard::Down)
		{
			if (choiceNum < 2)
				++choiceNum;
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

	sf::Sprite selectArrowSpr;
	selectArrowSpr.setTexture(Cfg::textures.get((int)Cfg::Textures::SelectArrow));
	selectArrowSpr.setPosition(positions[choiceNum]);

	wnd.draw(selectArrowSpr);

	sf::Text  titleText{};
	titleText.setFont(Cfg::fonts.get((int)Cfg::Fonts::Title));
	titleText.setString("The Adventures of Kenz : Cid's Awakening");
	titleText.setCharacterSize(64U);
	titleText.setPosition({ 275.f, 85.f });
	titleText.setFillColor(sf::Color::White);
	titleText.setOutlineColor(sf::Color::Black);
	titleText.setOutlineThickness(2);

	wnd.draw(titleText);

	sf::Text newGameText{};
	newGameText.setFont(Cfg::fonts.get((int)Cfg::Fonts::Title));
	newGameText.setString("New Game");
	
	if (choiceNum == 0)
	{
		newGameText.setCharacterSize(chosenSize);
		newGameText.setFillColor(chosenColor);
	}
	else
	{
		newGameText.setCharacterSize(unchosenSize);
		newGameText.setFillColor(unchosenColor);
	}
	newGameText.setPosition({ 1200.f, 285.f });
	newGameText.setOutlineColor(sf::Color::Black);
	newGameText.setOutlineThickness(2);

	wnd.draw(newGameText);

	sf::Text loadText{};
	loadText.setFont(Cfg::fonts.get((int)Cfg::Fonts::Title));
	loadText.setString("Load Game");
	if (choiceNum == 1)
	{
		loadText.setCharacterSize(chosenSize);
		loadText.setFillColor(chosenColor);
	}
	else
	{
		loadText.setCharacterSize(unchosenSize);
		loadText.setFillColor(unchosenColor);
	}
	loadText.setPosition({ 1200.f, 385.f });
	loadText.setOutlineColor(sf::Color::Black);
	loadText.setOutlineThickness(2);

	wnd.draw(loadText);

	sf::Text exitText{};
	exitText.setFont(Cfg::fonts.get((int)Cfg::Fonts::Title));
	exitText.setString("Exit Game");
	if (choiceNum == 2)
	{
		exitText.setCharacterSize(chosenSize);
		exitText.setFillColor(chosenColor);
	}
	else
	{
		exitText.setCharacterSize(unchosenSize);
		exitText.setFillColor(unchosenColor);
	}
	exitText.setPosition({ 1200.f, 485.f });
	exitText.setOutlineColor(sf::Color::Black);
	exitText.setOutlineThickness(2);

	wnd.draw(exitText);
}




