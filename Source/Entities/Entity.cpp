
#include <optional>
#include <Entities/Player.h>
int Entity::count = 0;
Entity::Entity()
	: IamCOLLIDABLE{}
	, id{ count++ }
{

}

Entity::~Entity()
{
}

void Entity::setComponent(ComponentType type_, void** data_)
{
	switch (type_)
	{
	case ComponentType::Transform:
	{
		std::get<cTransform>(components).init(*this, data_);
	}
	break;
	case ComponentType::BBox:
	{
		std::get<cBBox>(components).init(*this, data_);
	}
	break;
	case ComponentType::Render:
	{
		std::get<cRender>(components).init(*this, data_);
	}
	break;
	case ComponentType::Animation:
	{
		std::get<cAnimation>(components).init(*this, data_);
	}
		break;
	case ComponentType::AnimMap:
	{
		std::get<cAnimMap>(components).init(*this, data_);
	}
	break;
	default:
		
		break;
	}

}

bool Entity::hasComponent(ComponentType type_)
{
	return false;
}

Component* Entity::getComponent(ComponentType type_)
{
	switch (type_)
	{
	case ComponentType::Transform:
		return &std::get<cTransform>(components);
		break;
	case ComponentType::BBox:
		return &std::get<cBBox>(components);
		break;
	case ComponentType::Render:
		return &std::get<cRender>(components);
		break;
	case ComponentType::Animation:
		return &std::get<cAnimation>(components);
		break;
	case ComponentType::AnimMap:
		return &std::get<cAnimMap>(components);
		break;
	default:
		return nullptr;
		break;
	}
	return nullptr;
}

int Entity::getNumEntities()
{
	return count;
}

void Entity::processEvent(sf::RenderWindow& wnd_, float dt_, sf::Event& e)
{
}

void Entity::update(sf::RenderWindow& wnd_, float dt_)
{
}

void Entity::render(sf::RenderWindow& wnd_, float dt_)
{
}

void Entity::input(sf::RenderWindow& wnd_, float dt_, bool haltingMapX)
{
}


void Entity::changeAnim()
{
}

void Entity::tickPos(float dt_)
{
	auto* p = dynamic_cast<Player*>(this);
	if (p)
	{
		auto& pos = IgetPos();
		auto& vel = IgetVelocity();

		pos += {vel.x* dt_, vel.y* dt_ };
	}
}

