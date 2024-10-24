#include <Components/Components.h>
#include <Entities/Entity.h>
#include <assert.h>
Component::Component(Entity* owner_)
	: owner{owner_}
{
}
Component::~Component()
{
}

void Component::update(sf::RenderWindow& wnd_, float dt_)
{
}

void Component::render(sf::RenderWindow& wnd_, float dt_)
{
}

void Component::execute(sf::RenderWindow& wnd_, float dt_)
{
}


void cTransform::init(Entity& owner_, void** data_)
{
	owner = &owner_;

	auto& data = *reinterpret_cast<TransformInitData*>(data_);
	this->acceleration = data.acceleration_;
	this->position = data.position_;
	this->velocity = data.vel_;
}



void cRender::init(Entity& owner_, void** data_)
{
	owner = &owner_;

	auto* data = reinterpret_cast<RenderInitData*>(data_);
	this->texture = data->texture;
	
}

void cBBox::init(Entity& owner_, void** data_)
{
	owner = &owner_;
	auto* data = reinterpret_cast<BBoxInitData*>(data_);
	this->worldPosOffset = data->worldPosOffset_;
	this->boundingSize = (sf::Vector2i)data->boundingSize_;
	this->transform = data->transform_;
}



void cAnimation::init(Entity& owner_, void** data_)
{
	owner = &owner_;

	auto* data = reinterpret_cast<AnimationInitData*>(data_);
	auto* ff = &data->frames;
	this->frames.clear();
	this->frames.resize(data->frames.size());
	for (int i = 0; i < data->frames.size(); ++i)
	{
		this->frames[i] = data->frames[i];
	}
	this->animFrameDelay = data->animFrameDelay;
	this->animTimeElapsed = 0.f;
	this->idx = 0;
	this->isPlaying = data->isPlaying;
	this->animLoopDelay = data->animLoopDelay;
	this->loopWaitElapsed = 0.f;
	this->isLoopWaiting = false;
	this->reverseBeforeLoopWait = data->reverseBeforeLoopWait;
	currFrameRect = {frames[0]};
}



void cAnimMap::init(Entity& owner_, void** data_)
{
	owner = &owner_;

	auto* data = reinterpret_cast<AnimMapInitData*>(data_);
	assert(data->animNames.size() == data->frames.size() && "animMap arrays are not parallel!");

	this->animMap.clear();
	this->animMap.reserve(data->animNames.size());
	this->animData.clear();
	this->animData.reserve(data->animNames.size());

	for (int i = 0; i < data->animNames.size(); ++i)
	{
		this->animMap.emplace(data->animNames[i], std::vector<sf::IntRect>{});
		this->animMap.at(data->animNames[i]).clear();
		this->animMap.at(data->animNames[i]).reserve(data->frames[i].size());
		for (int j = 0; j < data->frames[i].size(); ++j)
		{
			this->animMap.at(data->animNames[i]).emplace_back(data->frames[i][j]);
		}
		animData.emplace(data->animNames[i], AnimMapSubData{});
		animData.at(data->animNames[i]).animFrameDelay = data->animSubDataVec[i].animFrameDelay;
		animData.at(data->animNames[i]).animLoopDelay= data->animSubDataVec[i].animLoopDelay;
		animData.at(data->animNames[i]).isPlaying = data->animSubDataVec[i].isPlaying;
		animData.at(data->animNames[i]).reverseBeforeLoopWait = data->animSubDataVec[i].reverseBeforeLoopWait;
		animData.at(data->animNames[i]).loops = data->animSubDataVec[i].loops;
	}
	this->animTimeElapsed = 0.f;
	this->loopWaitElapsed = 0.f;
	this->isLoopWaiting = false;
	this->idx = 0;

	this->currAnimStr = data->currAnimStr;
	currFrameRect = { animMap.at(currAnimStr).at(idx)};
}
