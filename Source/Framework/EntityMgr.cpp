#include <Framework/EntityMgr.h>
#include <algorithm>
#include <assert.h>
#include <Entities/Player.h>
int EntityMgr::getNumEntities()
{    
    return Entity::getNumEntities();
}

EntityMgr::EntityMgr()
    : entVec{}
{
    entVec = std::vector<std::unique_ptr<Entity> >{};
    entVec.clear();
}

int EntityMgr::makeEntity(std::vector<ComponentType>& typeVec_, std::vector<void**>& initDataVec_, EntityType type_ )
{
    if (type_ == EntityType::Player)
        entVec.emplace_back(std::make_unique<Player>());
    else
        entVec.emplace_back(std::make_unique<Entity>());

    for (int i = 0; i < typeVec_.size(); ++i)
    {
        switch (typeVec_[i])
        {
        case ComponentType::Animation:
        {
            entVec.back()->setComponent(ComponentType::Animation, initDataVec_[i]);
        }
        break;
        case ComponentType::BBox:
        {
            entVec.back()->setComponent(ComponentType::BBox, initDataVec_[i]);
        }
        break;
        case ComponentType::Render:
        {
            entVec.back()->setComponent(ComponentType::Render, initDataVec_[i]);
        }
        break;
        case ComponentType::Transform:
        {
            entVec.back()->setComponent(ComponentType::Transform, initDataVec_[i]);
        }
        break;
        case ComponentType::AnimMap:
        {
            entVec.back()->setComponent(ComponentType::AnimMap, initDataVec_[i]);
        }
        break;
        default:
            break;
        }
    }
    return entVec.back()->id;
}

Entity* EntityMgr::getEntity(int id_)
{
    assert(id_ < Entity::getNumEntities() && "Trying to access an entity that has not been created!");
    // TODO: insert return statement here
    return entVec[id_].get();
}

int EntityMgr::getEntityID(Entity& ent_)
{
    return ent_.id;
}

void EntityMgr::setComponent(Entity& ent_, ComponentType type_, void** data_)
{
    ent_.setComponent(type_, data_);
}

void EntityMgr::setComponents(Entity& ent_, std::vector<ComponentType> typeVec_, std::vector<void**>& data_)
{
    for (int i = 0; i < typeVec_.size(); ++i)
    {
        ent_.setComponent(typeVec_[i], data_[i]);
    }
}

void EntityMgr::setComponent(int entID_, ComponentType type_, void** data_)
{
    getEntity(entID_)->setComponent(type_, data_);
}

void EntityMgr::setComponents(int entID_, std::vector<ComponentType> typeVec_, std::vector<void**>& data_)
{
    for (int i = 0; i < typeVec_.size(); ++i)
    {
        getEntity(entID_)->setComponent(typeVec_[i], data_[i]);
    }
}

std::vector<std::unique_ptr<Entity> >* EntityMgr::getEntities()
{
    return &entVec;
}
