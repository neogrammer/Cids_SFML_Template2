#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <utility>
#include <tuple>
#include <Framework/Cfg.h>
#include <unordered_map>
#include <Types/ComponentTypes.h>
class Entity;
struct Component
{
	Entity* owner;
	Component(Entity* owner_ = nullptr);
	Component(const Component&) = delete;
	Component& operator=(const Component &)  = delete;
	Component(Component&&) = default;
	Component& operator=(Component&&) = default;
	virtual ~Component() = 0;
	virtual void init(Entity& owner_, void** data_) = 0;
	virtual void update(sf::RenderWindow& wnd_, float dt_);
	virtual void render(sf::RenderWindow& wnd_, float dt_);
	virtual void execute(sf::RenderWindow& wnd_, float dt_);
};

struct cTransform : public sf::Transformable, Component
{
	sf::Vector2f position{0.f,0.f};
	sf::Vector2f velocity{0.f,0.f};
	sf::Vector2f acceleration{0.f,0.f};
	using sf::Transformable::Transformable;
	using Component::Component;
	~cTransform() override final = default;
	void init(Entity& owner_, void** data_) override final;
	void update(sf::RenderWindow& wnd_, float dt_) override final;
};

struct cRender : public Component
{
	Cfg::Textures texture;
	using Component::Component;
	~cRender() override final = default;
	void init(Entity& owner_, void** data_) override final;
	void render(sf::RenderWindow& wnd_, float dt_) override final;
	sf::Sprite spr();
};


struct cBBox : public Component
{
	sf::Vector2i worldPosOffset{ 0,0 };
	sf::Vector2i boundingSize{ 0,0 };
	cTransform* transform{ nullptr };
	using Component::Component;
	~cBBox() override final = default;
	void init(Entity& owner_, void** data_) override final;
};


struct cAnimation : Component
{
	std::vector<sf::IntRect> frames;
	float animTimeElapsed{0.0f};
	float animFrameDelay{0.13f};
	int idx{0};
	bool isPlaying{ true };
	sf::IntRect currFrameRect{};
	float loopWaitElapsed{ 0.f };
	float animLoopDelay{ 1.0f };
	bool isLoopWaiting{ false };
	bool reverseBeforeLoopWait{ false };
	bool isReversing{ false };
	using Component::Component;
	const sf::IntRect& getCurrFrame();
	~cAnimation() override final = default;
	void init(Entity& owner_, void** data_) override final;
	void update(sf::RenderWindow& wnd_, float dt_) override final;
	void animate();
};

struct AnimMapSubData;
struct cAnimMap : public Component
{
	std::unordered_map<std::string, std::vector<sf::IntRect> > animMap;
	std::unordered_map<std::string, AnimMapSubData > animData;
	std::string currAnimStr{ "IdleState" };
	float animTimeElapsed{ 0.f };
	float loopWaitElapsed{ 0.f };
	bool isLoopWaiting{ false };
	bool loops{ true };
	bool isReversing{ false };
	int idx{ 0 };
	sf::IntRect currFrameRect{};
	using Component::Component;
	sf::IntRect getCurrFrame();
	~cAnimMap() override final = default;
	void init(Entity& owner_, void** data_) override final;
	void update(sf::RenderWindow& wnd_, float dt_) override final;
	void animate();
};

using EntityTuple = std::tuple<cTransform, cBBox, cRender, cAnimation, cAnimMap>;
