#ifndef PHYSICS_H__
#define PHYSICS_H__

#include <vector>
#include <SFML/Graphics.hpp>

class IamCOLLIDABLE;
class Entity;

class Physics
{
public:
	Physics() = delete;
	~Physics() = default;
	Physics(const Physics&) = delete;
	Physics(Physics&&) = delete;
	Physics& operator=(const Physics&) = delete;
	Physics& operator=(Physics&&) = delete;

	static void HandleCollisions(Entity& offender_, std::vector<IamCOLLIDABLE*>& possibles_, float dt_);

	static bool PointVsAABB(sf::Vector2f& pt_, IamCOLLIDABLE& aabb_);
	static bool AABBvAABB(IamCOLLIDABLE& a_, IamCOLLIDABLE& b_);

	static bool RayVsAABB(sf::Vector2f origin_, sf::Vector2f direction_, IamCOLLIDABLE& target_, sf::Vector2f& contactPoint_, sf::Vector2i& contactNormal_, float& contactTime_);
	static bool DynamicAABBvAABB(Entity& offender_, IamCOLLIDABLE& target_, sf::Vector2f& contactPoint_, sf::Vector2i& contactNormal_, float& contactTime_, float dt_);

};

#endif