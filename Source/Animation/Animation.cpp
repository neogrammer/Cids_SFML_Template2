#include <Animation/Animation.h>
#include <Types/ComponentTypes.h>
#include <assert.h>
#include <fstream>
AnimationPackage::AnimationPackage(int numFrames, int startX, int startY, int frameW, int frameH)
	: frames{}
	, animdataVec{}
	, animNames{}
	, rectVecContainer{}
{


	frames.clear();
	frames.reserve(numFrames);
	for (int i = 0; i < numFrames; ++i)
	{
		frames.emplace_back(sf::IntRect{ {startX + i*frameW, startY},{frameW,frameH} });
	}

	assert(frames.size() > 0 && "frames in Animation package not copied over in the constructor");

	singleAnimation = true;
	initialized = true;

}

AnimationPackage::AnimationPackage(std::vector<sf::IntRect> frames_, std::vector<std::string> animNames_, std::vector<std::vector<sf::IntRect>> rectVecContainer_, std::vector<AnimMapInitSubData> animdataVec_)
	: frames{}
	, animdataVec{std::move(animdataVec_)}
	, animNames{std::move(animNames_)}
	, rectVecContainer{std::move(rectVecContainer_)}
{
	frames.clear();


	assert(animdataVec.size() > 0 && "animdataVec in Animation package not copied over in the constructor");
	assert(animNames.size() > 0 && "animNames in Animation package not copied over in the constructor");
	assert(rectVecContainer.size() > 0 && "rectVecContainer in Animation package not copied over in the constructor");

	singleAnimation = false;
	initialized = true;
}

AnimationPackage::AnimationPackage(const std::string& filename)
	: frames{}
	, animdataVec{}
	, animNames{}
	, rectVecContainer{}
{
	std::fstream file;
	file.open(filename);

	if (file.is_open())
	{
		std::string checkStr;
		file >> checkStr;
		assert(checkStr.contains("AnimationPackage") && "Animation package loaded file is not correct type of data file");

		int vecSizeNames, vecSizeRects, vecSizeData;
		file >> vecSizeNames >> vecSizeRects >> vecSizeData;
		frames.clear();
		animNames.clear();
		animNames.reserve(vecSizeNames);
		animdataVec.clear();
		animdataVec.reserve(vecSizeData);
		rectVecContainer.clear();
		rectVecContainer.reserve(vecSizeRects);

		file >> checkStr;
		assert(checkStr == "Names" && "Animation package loaded file Names is not the first set of data to read in!");


		for (int i = 0; i < vecSizeNames; ++i)
		{
			std::string name;
			file >> name;
			animNames.emplace_back(name);
		}


		file >> checkStr;
		assert(checkStr == "Frames" && "Animation package loaded file Frames is not the second set of data to read in!");


		for (int i = 0; i < vecSizeRects; ++i)
		{
			int numFrames, startX, startY, frameW, frameH;
			file >> numFrames >> startX >> startY >> frameW >> frameH;
			rectVecContainer.emplace_back(std::vector<sf::IntRect>{});
			rectVecContainer.back().clear();
			rectVecContainer.back().reserve(numFrames);
			for (int j = 0; j < numFrames; ++j)
			{
				rectVecContainer[i].emplace_back(sf::IntRect{{startX * frameW + j * frameW, startY * frameH},{frameW,frameH}});
			}
		}


		file >> checkStr;
		assert(checkStr == "Data" && "Animation package loaded file Data is not the third set of data to read in!");

		for (int i = 0; i < vecSizeData; ++i)
		{
			int animDelayMS, playing, loopWaitDelayMS, loopWaits, loops;
			file >> animDelayMS >> playing >> loopWaitDelayMS >> loopWaits >> loops;
			bool pl = (playing == 1) ? true : false;
			bool lw = (loopWaits == 1) ? true : false;
			float aDelay =animDelayMS / 1000.f;
			float lDelay= loopWaitDelayMS / 1000.f;
			bool looping = (loops == 1) ? true : false;

		

			animdataVec.emplace_back(aDelay, pl, lDelay, lw, looping);

			initialized = true;
		}

		file.close();
	}

	singleAnimation = false;

}

std::vector<sf::IntRect> AnimationPackage::getFrames()
{
	return std::move(frames);
}

AnimMapInitData AnimationPackage::getData()
{
	assert(!singleAnimation && "Animation Package is setup for a single animation package! You are tring to load data from the unfilled vectors");
	assert(initialized && "Animation Package not initialized!!  oh no!");
	return { std::move(animNames), std::move(rectVecContainer), std::move(animdataVec) };
}

