#pragma once
#include <Types/ComponentTypes.h>
#include <Components/Components.h>
#include <tuple>
#include <memory>
#include <utility>
#include <Helper/IamCOLLIDABLE.h>
class Entity : public IamCOLLIDABLE
{
	friend class EntityMgr;
protected:
	int id{};
	static int count;
public:
	EntityTuple components{};
	Entity();
	virtual ~Entity();
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	Entity(Entity&&) = delete;
	Entity& operator=(Entity&&) = delete;
	void setComponent(ComponentType type_, void** data_);
	bool hasComponent(ComponentType type_);
	Component* getComponent(ComponentType type_);
	static int getNumEntities();
	virtual void processEvent(sf::RenderWindow& wnd_, float dt_, sf::Event& e);
	virtual void update(sf::RenderWindow& wnd_, float dt_);
	virtual void render(sf::RenderWindow& wnd_, float dt_);
	virtual void input(sf::RenderWindow& wnd_, float dt_, bool haltingMapX = false);

	virtual void changeAnim();
	void makePlayer();
	void tickPos(float dt_);
};