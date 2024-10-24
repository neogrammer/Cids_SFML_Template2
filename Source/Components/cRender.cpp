#include <Components/Components.h>
#include <Entities/Entity.h>
#include <variant>

void cRender::render(sf::RenderWindow& wnd_, float dt_)
{
	sf::Sprite sprite = spr();
	wnd_.draw(sprite);
}

sf::Sprite cRender::spr()
{

	sf::Sprite sprite;
	sprite.setTexture(Cfg::textures.get((int)texture));
	if (std::get<cTransform>(owner->components).owner != nullptr)
	{
		auto* trans = owner->getComponent(ComponentType::Transform);
		auto* t = dynamic_cast<cTransform*>(trans);
		if (t)
		{

			sprite.setPosition(t->position);
		}
		else
		{
			sprite.setPosition({ 0.f,0.f });

		}


		if (std::get<cAnimMap>(owner->components).owner != nullptr)
		{
			auto* aMap = owner->getComponent(ComponentType::AnimMap);
			auto* a = dynamic_cast<cAnimMap*>(aMap);
			if (a)
			{
				sprite.setTextureRect(dynamic_cast<cAnimMap*>(owner->getComponent(ComponentType::AnimMap))->getCurrFrame());
			}
		}
		else if (std::get<cAnimation>(owner->components).owner != nullptr)
		{
			auto* anim = owner->getComponent(ComponentType::Animation);
			auto* a = dynamic_cast<cAnimation*>(anim);
			if (a)
			{
				sprite.setTextureRect(dynamic_cast<cAnimation*>(owner->getComponent(ComponentType::Animation))->getCurrFrame());
			}
		}
	}
	return static_cast<sf::Sprite&&>(sprite);
}
