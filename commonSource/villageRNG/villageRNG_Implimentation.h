#ifndef __VILLAGE_RNG_IMPLIMENTATION__H
#define __VILLAGE_RNG_IMPLIMENTATION__H

#include "villageRNG_Interface.h"
#include "grand.h"

class VillageRNGImplimentation : public VillageRNGInterfaceClass
{
public:
	VillageRNGImplimentation(int seed = 0, int numberOfTimesCalled = 0, std::string name = "Unamed");
	~VillageRNGImplimentation() {};

	std::string name() const override;
	void name(const std::string & name) override;

	void restart(int seed, int numberOfTimesCalled) override;
	int next(int min, int max) override;
	bool next() override;

	int getSeed() const override;
	int getNumberOfTimesUsed() const override;

private:
	std::string _name;
	int _seed;
	int _numberOfTimesCalled;

	GRand _rawRNG;
};

#endif
