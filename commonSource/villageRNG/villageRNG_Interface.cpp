
#include "villageRNG_Implimentation.h"

VillageRNGInterface GetVillageRNGInterface(int seed, int numberOfTimesCalled, std::string name)
{
	return std::make_shared<VillageRNGImplimentation>(seed, numberOfTimesCalled, name);
}