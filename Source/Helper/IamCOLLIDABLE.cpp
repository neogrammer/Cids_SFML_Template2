#include <Helper/IamCOLLIDABLE.h>

IamCOLLIDABLE::~IamCOLLIDABLE()
{}

sf::Vector2i& IamCOLLIDABLE::IgetSize()
{
	return *I_size;
}

sf::Vector2i& IamCOLLIDABLE::IgetOffset()
{
	return *I_offset;
}

float IamCOLLIDABLE::halfW()
{
	return (float)this->I_size->x / 2.f;
}

float IamCOLLIDABLE::halfH()
{
	return (float)this->I_size->y / 2.f;
}



sf::Vector2f& IamCOLLIDABLE::IgetPos()
{
	return *I_pos;
}

sf::Vector2f& IamCOLLIDABLE::IgetVelocity()
{
	return *I_velocity;
}

void IamCOLLIDABLE::loadPointers(sf::Vector2f& pos_, sf::Vector2i& size_,  sf::Vector2f& vel_, sf::Vector2i& off_)
{
	I_pos = &pos_;
	I_size = &size_;
	I_velocity = &vel_;
	I_offset = &off_;
}
