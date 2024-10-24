#pragma once
#include <Entities/Entity.h>
#include <vector>
#include <memory>
#include <Types/EntityTypes.h>

class EntityMgr
{
	std::vector<std::unique_ptr<Entity> > entVec;
public:
	int getNumEntities();
	EntityMgr();
	int makeEntity(std::vector<ComponentType>& typeVec_, std::vector<void**>& initDataVec_, EntityType type_);
	Entity* getEntity(int id_);
	int getEntityID(Entity& ent_);
	void setComponent(Entity& ent_, ComponentType type_, void** data_);
	void setComponents(Entity& ent_, std::vector<ComponentType> typeVec_, std::vector<void**>& data_);
	void setComponent(int entID_, ComponentType type_, void** data_);
	void setComponents(int entID_, std::vector<ComponentType> typeVec_, std::vector<void**>& data_);
	std::vector<std::unique_ptr<Entity> >* getEntities();
};