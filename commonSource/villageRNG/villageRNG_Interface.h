#ifndef __VILLAGE_RNG_INTERFACE__H
#define __VILLAGE_RNG_INTERFACE__H

#include <memory>
#include <string>
#include <stdint.h>

class VillageRNGInterfaceClass
{
public:
	VillageRNGInterfaceClass() {};

	virtual std::string name() const = 0;
	virtual void name(const std::string & name) = 0;

	virtual void restart(int seed, int numberOfTimesCalled) = 0;
	virtual int next(int min, int max) = 0;
	virtual bool next() = 0;

	virtual int getSeed() const = 0;
	virtual int getNumberOfTimesUsed() const = 0;
};

using VillageRNGInterface = std::shared_ptr<VillageRNGInterfaceClass>;

VillageRNGInterface GetVillageRNGInterface(int seed = 0, int numberOfTimesCalled = 0, std::string name = "Unamed");

#endif // __VILLAGE_RNG_INTERFACE__H
