#include <Helper/Physics.h>
#include <Helper/IamCOLLIDABLE.h>
#include <Entities/Player.h>

void Physics::HandleCollisions(Entity& offender_, std::vector<IamCOLLIDABLE*>& possibles_, float dt_)
{
	// check collisions
	sf::Vector2f cp;
	sf::Vector2i cn;
	sf::Vector2f co;
	float ct;

	std::vector<std::pair<std::pair<float, IamCOLLIDABLE*>, std::pair<sf::Vector2f, sf::Vector2i>> > z;
	z.clear();
	for (auto* poss : possibles_)
	{
		cp = { 0.f,0.f };
		cn = { 0,0 };
		ct = 0.f;
		// get all the closest collisions that occur within range
		if (DynamicAABBvAABB(offender_, *poss, cp, cn, ct, dt_))
		{
			z.push_back(std::pair< std::pair<float, IamCOLLIDABLE*>, std::pair<sf::Vector2f, sf::Vector2i> >(std::pair<float, IamCOLLIDABLE*>(ct, poss), std::pair<sf::Vector2f, sf::Vector2i>(cp, cn)));
		}

	}


	if (!z.empty())
	{
		if (z.size() > 1)
		{
			// sort all the shortest collisions into ascending order again, this time, for handling order
			std::sort(z.begin(), z.end(), [](const std::pair<std::pair<float, IamCOLLIDABLE*>, std::pair<sf::Vector2f, sf::Vector2i>>& a, const std::pair<std::pair<float, IamCOLLIDABLE*>, std::pair<sf::Vector2f, sf::Vector2i>>& b)->bool
				{
					return a.first.first < b.first.first;
				});
		}

		// resolve in correct order
		for (auto j : z)
		{
			// get all the closest collisions that occur within range                              cp,                  cn,                     ct
			if (DynamicAABBvAABB(offender_, *j.first.second, j.second.first, j.second.second, j.first.first, dt_))
			{

				offender_.IgetVelocity() += { static_cast<sf::Vector2f>(j.second.second).x* sf::Vector2f{ std::abs(offender_.IgetVelocity().x) , std::abs(offender_.IgetVelocity().y)}.x* (1.f - j.first.first), static_cast<sf::Vector2f>(j.second.second).y* sf::Vector2f{std::abs(offender_.IgetVelocity().x) , std::abs(offender_.IgetVelocity().y)}.y* (1.f - j.first.first) };
				offender_.tickPos(dt_);
				if (j.second.second.y = -1)
				{
					Player* p = dynamic_cast<Player*>(&offender_);
					if (p)
					{
					
							p->setGrounded(true);
							p->justLanded = true;
							
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
								dispatch(p->fsm, EventLanded{ true });
							else
								dispatch(p->fsm, EventLanded{ false });
						
					}
				}


			}
		}

	}
	else
	{
		// no collisions do a regular tickpos
		offender_.tickPos(dt_);
	}
}

bool Physics::PointVsAABB(sf::Vector2f& pt_, IamCOLLIDABLE& aabb_)
{
	return (pt_.x >= aabb_.IgetPos().x + aabb_.IgetOffset().x && pt_.x <= aabb_.IgetPos().x + aabb_.IgetOffset().x + aabb_.IgetSize().x
		&& pt_.y >= aabb_.IgetPos().y + aabb_.IgetOffset().y && pt_.y <= aabb_.IgetPos().y + aabb_.IgetOffset().y + aabb_.IgetSize().y);

}

bool Physics::AABBvAABB(IamCOLLIDABLE& a_, IamCOLLIDABLE& b_)
{
	if (a_.IgetPos().x + a_.IgetOffset().x < b_.IgetPos().x + b_.IgetOffset().x + b_.IgetSize().x && a_.IgetPos().x + a_.IgetOffset().x + a_.IgetSize().x > b_.IgetPos().x + b_.IgetOffset().x
		&& a_.IgetPos().y + a_.IgetOffset().y < b_.IgetPos().y + b_.IgetOffset().y + b_.IgetSize().y && a_.IgetPos().y + a_.IgetOffset().y + a_.IgetSize().y > b_.IgetPos().y + b_.IgetOffset().y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Physics::RayVsAABB(sf::Vector2f origin_, sf::Vector2f direction_, IamCOLLIDABLE& target_, sf::Vector2f& contactPoint_, sf::Vector2i& contactNormal_, float& contactTime_)
{
	sf::Vector2f t_near = { ((target_.IgetPos().x + target_.IgetOffset().x) - origin_.x) / direction_.x, ((target_.IgetPos().y + target_.IgetOffset().y) - origin_.y) / direction_.y};
	sf::Vector2f t_far = { (target_.IgetPos().x + target_.IgetOffset().x + target_.IgetSize().x - origin_.x) / direction_.x,  ((target_.IgetPos().y + target_.IgetOffset().y) + target_.IgetSize().y - origin_.y) / direction_.y };
	if (std::isnan(t_far.y) || std::isnan(t_far.x)) { return false; }
	if (std::isnan(t_near.y) || std::isnan(t_near.x)) { return false; }
	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);
	if (t_near.x > t_far.y || t_near.y > t_far.x) { return false; }
	contactTime_ = std::max(t_near.x, t_near.y);
	float t_hit_far = std::min(t_far.x, t_far.y);
	if (t_hit_far < 0) { return false; }
	contactPoint_ = origin_ + contactTime_ * direction_;
	if (t_near.x > t_near.y)
	{
		if (direction_.x < 0)
		{
			contactNormal_ = { 1, 0 };
		}
		else
		{
			contactNormal_ = { -1, 0 };
		}
	}
	else if (t_near.x < t_near.y)
	{
		if (direction_.y < 0)
		{
			contactNormal_ = { 0, 1 };
		}
		else
		{
			contactNormal_ = { 0, -1 };
		}
	}
	return true;
}

bool Physics::DynamicAABBvAABB(Entity& offender_, IamCOLLIDABLE& target_, sf::Vector2f& contactPoint_, sf::Vector2i& contactNormal_, float& contactTime_, float dt_)
{
	if (offender_.IgetVelocity().x == 0 && offender_.IgetVelocity().y == 0)
	{
		return false;
	}
	struct COLL : public IamCOLLIDABLE
	{
		sf::Vector2f pos;
		sf::Vector2i size;
		sf::Vector2f vel;
		sf::Vector2i off;

		COLL(sf::Vector2f pos_, sf::Vector2i size_, sf::Vector2f vel_, sf::Vector2i off_)
			: pos{ pos_ }
			, size{ size_ }
			, vel{ vel_ }
			, off{off_}
		{}
	};

	COLL expanded_target{ sf::Vector2f{ target_.IgetPos().x + target_.IgetOffset().x - offender_.halfW(), target_.IgetPos().y + target_.IgetOffset().y - offender_.halfH()}, sf::Vector2i{(int)target_.IgetSize().x + (int)offender_.IgetSize().x,(int)target_.IgetSize().x + (int)offender_.IgetSize().y },sf::Vector2f{ 0.f,0.f}, {0,0} };
	expanded_target.loadPointers(expanded_target.pos, expanded_target.size, expanded_target.vel, expanded_target.off);

	//expanded_target.pos = { target_.pos.x - offender_.halfW(), target_.pos.y - offender_.halfH() };
	//expanded_target.boundsSize = target_.boundsSize + offender_.boundsSize;
	sf::Vector2f dir = { (offender_.IgetPos().x + offender_.IgetOffset().x + offender_.halfW() + (offender_.IgetVelocity().x * dt_)) - (offender_.IgetPos().x + offender_.IgetOffset().x + offender_.halfW()),(offender_.IgetPos().y + offender_.IgetOffset().y + offender_.halfH() + (offender_.IgetVelocity().y * dt_)) - (offender_.IgetPos().y + offender_.IgetOffset().y + offender_.halfH()) };
	sf::Vector2f originOfRay = { offender_.IgetPos().x + offender_.IgetOffset().x + offender_.halfW(), offender_.IgetPos().y + offender_.IgetOffset().y + offender_.halfH()};

	float lengthOfDir = sqrtf(dir.x * dir.x + dir.y * dir.y);

	dir.x = dir.x / lengthOfDir;
	dir.y = dir.y / lengthOfDir;

	if (RayVsAABB(originOfRay,  dir,  *dynamic_cast<IamCOLLIDABLE*>(&expanded_target), contactPoint_, contactNormal_, contactTime_))
	{
			if (contactTime_ <= 1.0f && contactTime_ > 0.f)
			{
				return true;
			}
	}
	return false;
}

