#ifndef GAMESTATEMGR_H__
#define GAMESTATEMGR_H__
#include <string>

#include <memory>
#include <utility>
#include <stack>
#include <unordered_map>
#include <Framework/Cfg.h>
#include <Types/GameStateTypes.h>
class Game;
class GameState;

class GameStateMgr
{
	GameStateType nextState{ GameStateType::NotSet };
	bool needsToSwitchState{ false };
	bool popOffCurrent{ true };

	std::unordered_map<GameStateType, std::unique_ptr<GameState> > stateMap{};
public:
	std::stack<GameState*> stateStack;
	GameStateMgr();
	~GameStateMgr();
	GameStateMgr& operator=(const GameStateMgr&) = delete;
	GameStateMgr(const GameStateMgr&) = delete;
	GameStateMgr& operator=(GameStateMgr&&) = delete;
	GameStateMgr(GameStateMgr&&) = delete;

	void renderUnder(sf::RenderWindow& wnd, float dt);
	bool hasUnder();
	void input(sf::RenderWindow& wnd, float dt);
	void update(sf::RenderWindow& wnd, float dt);
	void render(sf::RenderWindow& wnd, float dt);
	void safeStateSwitch();
	void processEvent(sf::Event& e_);
	void changeState(GameStateType type_, bool popCurrent_ = true);
	void popTop();
	void resetState(GameStateType type_);

};

#endif