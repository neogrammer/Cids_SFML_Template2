#include <Components/Components.h>
#include <Entities/Entity.h>
#include <variant>

sf::IntRect cAnimMap::getCurrFrame()
{
	return animMap.at(currAnimStr).at(idx);
}


void cAnimMap::update(sf::RenderWindow& wnd_, float dt_)
{
	if (!animData[currAnimStr].loops && idx == animMap.at(currAnimStr).size() - 1)
	{
	}
	else
	{


		if (!isLoopWaiting)
			animTimeElapsed += dt_;
		else
			loopWaitElapsed += dt_;

		if (!isLoopWaiting)
		{
			if (animTimeElapsed >= animData[currAnimStr].animFrameDelay)
			{
				animTimeElapsed = 0.f;
				animate();

			}
		}
		else
		{
			if (loopWaitElapsed >= animData[currAnimStr].animLoopDelay)
			{
				loopWaitElapsed = 0.f;

				isLoopWaiting = false;

				idx = 0;
			}
		}
	}
}

void cAnimMap::animate()
{
	if (animData[currAnimStr].isPlaying && !isLoopWaiting)
	{
		currFrameRect = animMap.at(currAnimStr).at(idx);

		if (!isLoopWaiting)
		{
			if (!isReversing)
			{
				if (idx + 1 == animMap.at(currAnimStr).size())
				{
					if (animData[currAnimStr].reverseBeforeLoopWait)
					{
						isReversing = true;
						isLoopWaiting = false;
						loopWaitElapsed = 0.f;
					}
					else
					{
						isLoopWaiting = true;
						loopWaitElapsed = 0.f;
					}
				}
			}
			else
			{
				if (idx - 1 < 0)
				{
					isLoopWaiting = true;
					loopWaitElapsed = 0.f;
					isReversing = false;
				}
			}
		}
		if (!isLoopWaiting)
		{
			if (!isReversing)
			{

				idx += 1;
				if (idx >= animMap.at(currAnimStr).size())
				{
					//	idx = 0;

				}
			}
			else
			{
				idx -= 1;
				if (idx < 0)
				{
					idx = 0;
					isReversing = false;
					isLoopWaiting = true;
					loopWaitElapsed = 0.f;
				}
			}
		}
	}


}
