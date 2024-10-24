#pragma once
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <string>

struct AnimMapInitSubData;
struct AnimMapInitData;

class AnimationPackage
{
	std::vector<sf::IntRect> frames{};
	std::vector<std::string> animNames{};
	std::vector<std::vector<sf::IntRect> > rectVecContainer{};
	std::vector<AnimMapInitSubData> animdataVec{};
	bool singleAnimation{ true };
	bool initialized{ false };
public:
	AnimationPackage() = default;
	~AnimationPackage() = default;
	AnimationPackage(int numFrames, int startX, int startY, int frameW, int frameH);
	AnimationPackage(std::vector<sf::IntRect> frames_, std::vector<std::string> animFrames_, std::vector<std::vector<sf::IntRect> > rectVecContainer_, std::vector<AnimMapInitSubData> animdataVec_);
	AnimationPackage(const AnimationPackage&) = delete;
	AnimationPackage& operator=(const AnimationPackage&) = delete;
	AnimationPackage(AnimationPackage&&) = delete;
	AnimationPackage& operator=(AnimationPackage&&) = default;
	AnimationPackage(const std::string& filename);

	std::vector<sf::IntRect> getFrames();

	AnimMapInitData getData();
};