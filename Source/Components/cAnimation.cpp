#include <Components/Components.h>
#include <Entities/Entity.h>
#include <variant>

const sf::IntRect& cAnimation::getCurrFrame()
{
	return currFrameRect;
}



void cAnimation::update(sf::RenderWindow& wnd_, float dt_)
{
	if (!isLoopWaiting)
		animTimeElapsed += dt_;
	else
		loopWaitElapsed += dt_;

	if (!isLoopWaiting)
	{
		if (animTimeElapsed >= animFrameDelay)
		{
			animTimeElapsed = 0.f;
			animate();

		}
	}
	else
	{
		if (loopWaitElapsed >= animLoopDelay)
		{
			loopWaitElapsed = 0.f;

			isLoopWaiting = false;

			idx = 0;
		}
	}
}

void cAnimation::animate()
{
	if (isPlaying && !isLoopWaiting)
	{
		currFrameRect = frames[idx];

		if (!isLoopWaiting)
		{
			if (!isReversing)
			{
				if (idx + 1 == frames.size())
				{
					if (reverseBeforeLoopWait)
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
				if (idx >= frames.size())
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