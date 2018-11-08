#ifndef __HARVESTER_H__
#define __HARVESTER_H__

#include "PassiveUnit.h"
#include "../Weapons/AssaultRifle.h"

class Harvester : public PassiveUnit {
public:
	Harvester(int x, int y);

	~Harvester();

	virtual bool canMoveAboveTerrain(Terrain &terrain);

	virtual void reciveBonusDammage(const Weapon &weapon) override;

private:
	const int spiceCapacity;
};

#endif
