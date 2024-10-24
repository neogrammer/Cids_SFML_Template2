#ifndef PLAYSTATE_H__
#define PLAYSTATE_H__
#include <Framework/GameStateMgr.h>
#include <Framework/GameState.h>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <stack>
#include <memory>
#include <array>
#include <Scene/Tilemap.h>
#include <Framework/EntityMgr.h>
#include <FiniteStateMachine/PlayerAnimStates.h>
#include <FiniteStateMachine/PlayerAnimFSM.h>
#include <Entities/Player.h>

class PlayState : public GameState
{
	std::unique_ptr<EntityMgr> entMgr;
	//Entity* player;
	Player* player;
	Tilemap tilemap;
	FSM_Player playerAnimFSM{};
	std::string frameStartAnimStr{ "InAirFallState" };
public:
	PlayState() = default;
	PlayState(GameStateMgr* mgr_);
	~PlayState() override final;
	void input(sf::RenderWindow& wnd, float dt)  override final;
	void update(sf::RenderWindow& wnd, float dt)  override final;
	void render(sf::RenderWindow& wnd, float dt)  override final;
	void processEvent(sf::RenderWindow& wnd, sf::Event& e) override final;
	void init(sf::RenderWindow& wnd);
	void changeAnim(Entity& entity, FSM_Player& fsm);
	void makePlayer();
};

#endif

