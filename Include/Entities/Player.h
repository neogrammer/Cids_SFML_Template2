#pragma once

#include <Entities/Entity.h>
#include <FiniteStateMachine/PlayerAnimStates.h>
#include <FiniteStateMachine/PlayerAnimFSM.h>

class Player : public Entity
{
	friend class Physics;
	friend class PlayState;
	FSM_Player fsm{};
	std::string frameStartAnimStr{ "IdleState" };

public:
	bool isGrounded{ false };
	bool justLanded{ false };
	bool justJumped{ false };

	bool currentlyShooting{ false };
	float shootingTimeElapsed{ 0.f };
	float shootingDelay{ 0.2f };
	float shootAnimTotalElapsed{ 0.f };
	float shootAnimDelay{ 0.3f };


	Player();
	~Player();
	Player(const Player&) = delete;
	Player(Player&&) = delete;
	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&) = delete;

	void changeAnim() override final;
	void processEvent(sf::RenderWindow& wnd_, float dt_, sf::Event& e) override final;
	void update(sf::RenderWindow& wnd_, float dt_) override final;
	void render(sf::RenderWindow& wnd_, float dt_) override final;
	void input(sf::RenderWindow& wnd_, float dt_, bool haltingMapX) override final;

	void setGrounded(bool cond_);
	bool isOnGround();



};