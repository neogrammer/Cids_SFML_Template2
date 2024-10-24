#pragma once

#include <SFML/Graphics/Rect.hpp>

class IamCOLLIDABLE
{
protected:
	sf::Vector2f* I_pos{ };
	sf::Vector2i* I_size{ };
	sf::Vector2f* I_velocity{};
	sf::Vector2i* I_offset{};

public:
	IamCOLLIDABLE() = default;
	virtual ~IamCOLLIDABLE() = 0;
	sf::Vector2f& IgetPos();
	sf::Vector2i& IgetSize();
	sf::Vector2i& IgetOffset();
	float halfW();
	float halfH();
	sf::Vector2f& IgetVelocity();
	void loadPointers(sf::Vector2f& pos_,sf::Vector2i& size_, sf::Vector2f& vel_, sf::Vector2i& off_);
};
