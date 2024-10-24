#include <GameStates/PlayState.h>
#include <type_traits>
#include <string>
#include <iostream>
#include <Animation/Animation.h>
#include <Types/EntityTypes.h>
#include <Helper/Physics.h>
#include <Helper/IamCOLLIDABLE.h>

void PlayState::input(sf::RenderWindow& wnd, float dt)
{
	tilemap.haltMapX = false;
	if (wnd.getView().getCenter().x - (wnd.getSize().x / 2) < 0)
	{
		tilemap.haltMapX = true;
	}
	if (player)
		player->input(wnd, dt, tilemap.shouldHaltMapX());

}

void PlayState::update(sf::RenderWindow& wnd, float dt)
{
	for (auto& e : *entMgr->getEntities())
	{
		e->update(wnd, dt);
		if (std::get<cAnimMap>(e->components).owner != nullptr)
		{
			auto& aMap = *dynamic_cast<cAnimMap*>(e->getComponent(ComponentType::AnimMap));
			
			aMap.update(wnd, dt);
		}
		else if (std::get<cAnimation>(e->components).owner != nullptr)
		{
			auto& anim = *dynamic_cast<cAnimation*>(e->getComponent(ComponentType::Animation));
			anim.update(wnd, dt);
		}
		
	}
}

void PlayState::render(sf::RenderWindow& wnd, float dt)
{

	tilemap.render(wnd);
	auto& collMapTmp = tilemap.getTiles();
	std::vector<IamCOLLIDABLE*> collidables(collMapTmp.size(), nullptr );

	for (int i = 0; i < collMapTmp.size(); i++)
	{
		collidables[i] = collMapTmp[i].get();
	}
	Physics::HandleCollisions(*player, collidables, dt); 

	for (auto& ent : *entMgr->getEntities())
	{
		if (dynamic_cast<Player*>(ent.get()))
			player->getComponent(ComponentType::Render)->render(wnd, dt);
		else
			ent->getComponent(ComponentType::Render)->render(wnd, dt);
	}
	// only run this once at the end of the frame after drawing for next frames
	for (auto& e : *entMgr->getEntities())
	{
		if (dynamic_cast<Player*>(e.get()))
			dynamic_cast<Player*>(e.get())->changeAnim();
		else
			e->changeAnim();
	}
}

PlayState::PlayState(GameStateMgr* mgr_)
	: GameState{mgr_}
	, tilemap{"Assets/Data/Tilemaps/tilemap1.txt"}
	, entMgr{}
	, player{nullptr}
{}

void PlayState::processEvent(sf::RenderWindow& wnd, sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::P)
		{
			owner->changeState(GameStateType::Paused, false);
		}
	}
	for (auto& ent : *entMgr->getEntities())
	{
		if (dynamic_cast<Player*>(ent.get()))
			dynamic_cast<Player*>(ent.get())->processEvent(wnd, 0.0003f, e);
		else
			ent->processEvent(wnd, 0.0003f, e);
	}
}

void PlayState::init(sf::RenderWindow& wnd)
{
	entMgr = std::make_unique<EntityMgr>();
	tilemap.renderTexture(wnd);
	makePlayer();
	frameStartAnimStr = "InAirFallState";
	dynamic_cast<cAnimMap*>(player->getComponent(ComponentType::AnimMap))->currAnimStr = "InAirFallState";
	player->fsm.dispatch(EventStartedFalling{});
	player->frameStartAnimStr = frameStartAnimStr;
}

PlayState::~PlayState()
{}


void PlayState::makePlayer()
{
	if (player)
	{
		player = nullptr;
	}
	AnimationPackage pkg{ "Assets/Data/Animations/player.anim" };
	AnimMapInitData animMapData = std::move(pkg.getData());
	RenderInitData rData{ Cfg::Textures::PlayerAtlas };
	TransformInitData tData{ {0.f,0.f},{300.f,500.f}, {0.f,0.f } };
	std::vector<void**> dataVec = {
		reinterpret_cast<void**>(&animMapData),
		reinterpret_cast<void**>(&rData),
		reinterpret_cast<void**>(&tData)
	};
	std::vector<ComponentType> tmpVec = {
		ComponentType::AnimMap,
		ComponentType::Render,
		ComponentType::Transform
	};
	int entID = entMgr->makeEntity(tmpVec, dataVec, EntityType::Player);
	auto& ctrans = *dynamic_cast<cTransform*>(reinterpret_cast<Component*>(entMgr->getEntity(entID)->getComponent(ComponentType::Transform)));
	BBoxInitData bbData{ {32 , 45},  &ctrans,  {60.f , 78.f} };
	entMgr->getEntity(entID)->setComponent(ComponentType::BBox, reinterpret_cast<void**>(&bbData));
	player = dynamic_cast<Player*>(entMgr->getEntity(entID));

	auto& transform = std::get<cTransform>(player->components);
	auto& bbox = std::get<cBBox>(player->components);
	auto& aMap = std::get<cAnimMap>(player->components);

	//auto& transform = std::get<cTransform>(player->components);
	transform.acceleration = { 0.f, 1000.f };
	transform.velocity = { 0.f, 0.f };
	transform.position = { 200.f, 400.f };

	player->loadPointers(transform.position, bbox.boundingSize, transform.velocity, bbox.worldPosOffset);

	player->setGrounded(false);
	dispatch(playerAnimFSM, EventStartedFalling{});
	aMap.currAnimStr = playerAnimFSM.getStateName();
	frameStartAnimStr = "InAirFallState";
}
