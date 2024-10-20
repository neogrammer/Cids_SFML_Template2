#include <Framework/GameStateMgr.h>

#include <GameStates/PausedState.h>
#include <GameStates/PlayState.h>
#include <GameStates/SplashState.h>
#include <GameStates/TitleState.h>
#include <iostream>
GameStateMgr::GameStateMgr()
{
	

	stateMap.emplace( GameStateType::Splash, std::move(std::make_unique<SplashState>(this)) );
	stateMap.emplace( GameStateType::Title, std::move(std::make_unique<TitleState>(this)) );
	stateMap.emplace( GameStateType::Paused, std::move(std::make_unique<PausedState>(this)) );
	stateMap.emplace( GameStateType::Play, std::move(std::make_unique<PlayState>(this)) );
	stateStack.push(stateMap.at(GameStateType::Splash).get());
	
}

GameStateMgr::~GameStateMgr()
{
	while (!stateStack.empty())
	{
		stateStack.pop();
	}
	stateMap.clear();
}

void GameStateMgr::renderUnder(sf::RenderWindow& wnd, float dt)
{
	std::stack<GameState*> tmpStack = {};
	while (!stateStack.empty())
	{
		tmpStack.push(stateStack.top());
		stateStack.pop();

	}

	// statestack is empty, lets put the states back, and render each one  as we do so as to render the under ones first
	while (!tmpStack.empty())
	{
		stateStack.push(tmpStack.top());
		tmpStack.pop();
		stateStack.top()->render( wnd,  dt);
	}

	// tmpStack is now empty again and all states on the stack have been rendered in order
	
}

bool GameStateMgr::hasUnder()
{
	return (stateStack.size() > 1);
}

void GameStateMgr::input(sf::RenderWindow& wnd, float dt)
{
	if (!needsToSwitchState)
		stateStack.top()->input( wnd,  dt);
	return;
}

void GameStateMgr::update(sf::RenderWindow& wnd, float dt)
{
	if (needsToSwitchState)
		safeStateSwitch();
	if (!needsToSwitchState)
		stateStack.top()->update( wnd,  dt);
	return;
}


void GameStateMgr::popTop()
{
	stateStack.pop();
}

void GameStateMgr::resetState(GameStateType type_)
{
	if (stateMap.find(type_) != stateMap.end())
	{
		stateMap.erase(stateMap.find(type_));
		stateMap.insert_or_assign(type_, std::make_unique<PlayState>(this));
	}

}

void GameStateMgr::render(sf::RenderWindow& wnd, float dt)
{
	if (!needsToSwitchState)
	{
		if (hasUnder())
		{
			renderUnder(wnd, dt);
		}
		else
		{
			stateStack.top()->render( wnd,  dt);
		}
	}
	return;
}

void GameStateMgr::safeStateSwitch()
{
	if (needsToSwitchState)
	{
		needsToSwitchState = false;
		if (nextState == GameStateType::NotSet)
		{
			std::cout << "Trying to change states to GameStateType::None!" << std::endl;
			return;
		}
		else
		{
			
			//gWnd.setView(gWnd.getDefaultView());
			if (popOffCurrent)
				stateStack.pop();
			
			stateStack.push(stateMap.at(nextState).get());

			if (nextState == GameStateType::Play)
			{
				//gameView = wnd->getDefaultView();
				//dynamic_cast<PlayState*>(stateStack.top())->LoadLevel();
			}

		}
		nextState = GameStateType::NotSet;
		popOffCurrent = true;

		return;
	}
	return;
}

void GameStateMgr::processEvent(sf::Event& e_)
{
	stateStack.top()->processEvent(e_);
}

void GameStateMgr::changeState(GameStateType type_, bool popCurrent_)
{
	nextState = type_;
	popOffCurrent = popCurrent_;
	needsToSwitchState = true;
	return;
}
