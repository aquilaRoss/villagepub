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

	/// @brief Resets the RNG to a specific point in its sequence.
	///
	/// This method does NOT restart the sequence from the beginning.
	/// Instead, it:
	///  1. Re-initializes the RNG with the given seed.
	///  2. Advances the RNG internally 'numberOfTimesCalled' steps,
	///     discarding all intermediate values.
	///
	/// After calling this, the RNG will produce the same sequence of
	/// numbers as if it had been used 'numberOfTimesCalled' times since
	/// initialization with the given seed.
	///
	/// @param seed The initial seed to use for RNG.
	/// @param numberOfTimesCalled The number of steps to advance in the sequence.
	virtual void advanceTo(int seed, int numberOfTimesCalled) = 0;

	virtual int next(int min, int max) = 0;
	virtual bool next() = 0;

	virtual int getSeed() const = 0;
	virtual int getNumberOfTimesUsed() const = 0;
};

using VillageRNGInterface = std::shared_ptr<VillageRNGInterfaceClass>;

VillageRNGInterface GetVillageRNGInterface(int seed = 0, int numberOfTimesCalled = 0, std::string name = "Unamed");

#endif // __VILLAGE_RNG_INTERFACE__H
