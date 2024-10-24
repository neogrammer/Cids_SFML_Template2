#pragma once
#include <Components/Components.h>
#include <Framework/Cfg.h>
#include <Types/ComponentTypes.h>

enum class ComponentType : int
{
	Transform,
	Render,
	Animation,
	BBox,
	AnimMap,
	Count,
	NotSet
};

struct cTransform;
struct BBoxInitData
{
	sf::Vector2i worldPosOffset_;
	cTransform* transform_;
	sf::Vector2f boundingSize_;
};


struct AnimMapSubData
{
	float animFrameDelay{ 0.13f };
	bool isPlaying{ true };
	float animLoopDelay{ 0.f };
	bool reverseBeforeLoopWait{ false };
	bool loops{ true };
};

struct AnimationInitData
{
	std::vector<sf::IntRect> frames;
	float animTimeElapsed{ 0.0f };
	float animFrameDelay{ 0.13f };
	int idx{ 0 };
	bool isPlaying{ true };
	float animLoopDelay{ 0.f };
	bool reverseBeforeLoopWait{ false };
};


struct RenderInitData
{
	Cfg::Textures texture;
};


struct TransformInitData
{
	sf::Vector2f position_;
	sf::Vector2f vel_;
	sf::Vector2f acceleration_;
};



struct AnimMapInitSubData
{
	float animFrameDelay{ 0.13f };
	bool isPlaying{ true };
	float animLoopDelay{ 0.f };
	bool reverseBeforeLoopWait{ false };
	bool loops{ true };
};

struct AnimMapInitData
{
	std::vector<std::string> animNames;
	std::vector<std::vector<sf::IntRect> > frames;
	std::vector<AnimMapInitSubData> animSubDataVec;
	/*float animTimeElapsed{ 0.0f };
	float animFrameDelay{ 0.13f };*/
	//int idx{ 0 };
	//bool isPlaying{ true };
	//float animLoopDelay{ 0.f };
	//bool reverseBeforeLoopWait{ false };
	std::string currAnimStr{ "IdleState" };
};

