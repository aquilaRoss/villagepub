
#include "villageRNG_Implimentation.h"
#include "grand.h"

VillageRNGImplimentation::VillageRNGImplimentation(int seed, int numberOfTimesCalled, std::string name)
{
	_name = name;
	_numberOfTimesCalled = 0;
	advanceTo(seed, numberOfTimesCalled);
}

std::string VillageRNGImplimentation::name() const
{
	return _name;
}

void VillageRNGImplimentation::name(const std::string & name)
{
	_name = name;
}

void VillageRNGImplimentation::advanceTo(int seed, int numberOfTimesCalled)
{
	_seed = seed;
	_rawRNG.seed(_seed);
	
	for (int index = 0; index < numberOfTimesCalled; index++)
	{
		next();
		_numberOfTimesCalled++;
	}
}

int VillageRNGImplimentation::next(int min, int max)
{
	// GRand produces in the 0 to (n-1) range
	// so if i want values in the 0-100 i need to ask for 0-101
	// or if i want -10 to 10 i need to ask for 0-21 and -10 (not -11 because it return n-1 so will never return 21)
	// or if i want 10 to 20, i need to ask for 0-11 (getting 0-10) then adding 10

	int randomRange = max - min;
	int mustBeLessThan = randomRange + 1;
	int notOffsetRandomNumber = _rawRNG.i(mustBeLessThan);
	int offsetRandomNumer = notOffsetRandomNumber + min;

	_numberOfTimesCalled++;

	return offsetRandomNumer;
}

bool VillageRNGImplimentation::next()
{
	if (next(0, 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
std::string VillageRNGImplimentation::next(const StringList & listOfStrings)
{
	if (listOfStrings.size() > 0)
	{
		auto listIterator = std::next(listOfStrings.begin(), next(0, (int)listOfStrings.size() - 1));
		return *listIterator;
	}

	return "";
}
*/

int VillageRNGImplimentation::getSeed() const
{
	return _seed;
}

int VillageRNGImplimentation::getNumberOfTimesUsed() const
{
	return _numberOfTimesCalled;
}
