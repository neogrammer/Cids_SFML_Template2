#include <Entities/Player.h>

Player::Player()
	: Entity{}
{
	
}


void Player::setGrounded(bool cond_)
{
	isGrounded = cond_;
}

bool Player::isOnGround()
{
	return isGrounded;
}


Player::~Player()
{
}



void Player::changeAnim()
{
	std::string endOfFrameAnim = fsm.getStateName();

	if (endOfFrameAnim != frameStartAnimStr)
	{
		std::string tmp = std::get<cAnimMap>(components).currAnimStr;

		//std::cout << "Before State:  " << tmp << "   ---  After State:  ";

		std::get<cAnimMap>(components).currAnimStr = fsm.getStateName();

		std::string tmp2 = std::get<cAnimMap>(components).currAnimStr;

		//std::cout << tmp2 << std::endl;


		if (std::get<cAnimMap>(components).currAnimStr != tmp)
		{
			if (((tmp == "InAirState" && tmp2 == "InAirShootingState") || (tmp == "InAirShootingState" && tmp2 == "InAirState")) ||
				((tmp == "InAirPeakState" && tmp2 == "InAirPeakShootingState") || (tmp == "InAirPeakShootingState" && tmp2 == "InAirPeakState")) ||
				((tmp == "InAirFallState" && tmp2 == "InAirFallShootingState") || (tmp == "InAirFallShootingState" && tmp2 == "InAirFallState")) ||
				((tmp == "RunningState" && tmp2 == "RunningAndShootingState") || (tmp == "RunningAndShootingState" && tmp2 == "RunningState"))
				)
			{
				// dont change the index, leave it where its at
			}
			else if (((tmp == "RunningAndShootingState" && tmp2 == "ShootingState")))
			{
				std::get<cAnimMap>(components).idx = 3;
			}
			else
			{
				// start the animation over, make sure the new frame vector can handle the set idx for the component, which is shared by the states
				std::get<cAnimMap>(components).idx = 0;
			}
		}
	}
}

void Player::processEvent(sf::RenderWindow& wnd_, float dt_, sf::Event& e)
{
}

void Player::update(sf::RenderWindow& wnd_, float dt_)
{
	if (justJumped)
	{
		setGrounded(false);
		justJumped = false;
		IgetVelocity().y = -600.f;
	}

	if (!isOnGround())
	{
		std::string name = fsm.getStateName();
		if (IgetVelocity().y < 0.f)
		{
			IgetVelocity() += {0.f, dynamic_cast<cTransform*>(getComponent(ComponentType::Transform))->acceleration.y* dt_};
			if (IgetVelocity().y > -0.5f)
			{
				dispatch(fsm, EventReachedJumpPeak{});
			}
		}
		else
		{
			IgetVelocity() += {0.f, dynamic_cast<cTransform*>(getComponent(ComponentType::Transform))->acceleration.y* dt_};
			if (IgetVelocity().y > 150.f)
			{
				if (name == "InAirPeakState" || name == "InAirPeakShootingState")
				{
					dispatch(fsm, EventStartedFalling{});
				}
			}
		}
		
	}
	else
	{
		IgetVelocity().y = 0.f;
	}
}

void Player::render(sf::RenderWindow& wnd_, float dt_)
{
}

void Player::input(sf::RenderWindow& wnd_, float dt_, bool haltingMapX)
{



	frameStartAnimStr = fsm.getStateName();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		auto view = wnd_.getView();
		if (!haltingMapX)
		{
			auto& pos = std::get<cTransform>(components).position.x;
			pos += 280.f * dt_;
			if (wnd_.getView().getCenter().x < pos - 70.f)
			{
				sf::View v = wnd_.getView();
				v.setCenter({ pos - 70.f, v.getCenter().y });
				wnd_.setView(v);
			}
		}
		else
		{
			auto& pos = std::get<cTransform>(components).position.x;
			pos += 250.f * dt_;
		}

		
		dispatch(fsm, EventStartedMoving{});

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		auto view = wnd_.getView();
		if (!haltingMapX)
		{
			auto& pos = std::get<cTransform>(components).position.x;
			pos -= 250.f * dt_;
			if (wnd_.getView().getCenter().x > pos + 300.f)
			{
				sf::View v = wnd_.getView();
				v.setCenter({ pos + 300.f, v.getCenter().y });
				wnd_.setView(v);
			}
		}
		else
		{
			auto& pos = std::get<cTransform>(components).position.x;
			pos -= 250.f * dt_;

		}

		dispatch(fsm, EventStartedMoving{});
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		dispatch(fsm, EventStoppedMoving{});
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		if (isOnGround())
		{
			justJumped = true;
			dispatch(fsm, EventJumped{});
		}
	}


	if (currentlyShooting)
	{
		shootAnimTotalElapsed += dt_;
		shootingTimeElapsed += dt_;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		if (!currentlyShooting)
		{
			currentlyShooting = true;
			shootAnimTotalElapsed = 0.f;
			shootingTimeElapsed = 0.f;
			dispatch(fsm, EventStartedShooting{});
			// FIRE A BULLET

		}

		if (currentlyShooting)
		{
			if (shootingTimeElapsed > shootingDelay)
			{
				shootingTimeElapsed = 0.f;
				shootAnimTotalElapsed = 0.f;
				// FIRE A BULLET
			}
		}
	}
	else
	{
		if (currentlyShooting && shootAnimTotalElapsed > shootAnimDelay)
		{
			currentlyShooting = false;
			shootingTimeElapsed = 0.f;
			shootAnimTotalElapsed = 0.f;
			dispatch(fsm, EventStoppedShooting{});
		}
	}
}
