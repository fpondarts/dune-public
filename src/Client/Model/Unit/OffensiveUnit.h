#ifndef __OffensiveUnit_H__
#define __OffensiveUnit_H__

#include "Unit.h"

#include <Model/Map.h>

class OffensiveUnit : public Unit {
public:
	explicit OffensiveUnit(nlohmann::json& j);
	Position& getVictimPosition();

	virtual void update(nlohmann::json& j) override;
	bool isAttacking();
	bool isShooting();

private:
	bool attacking;
	bool shooting;
	Position victim_pos;
};

#endif //__OffensiveUnit_H__
