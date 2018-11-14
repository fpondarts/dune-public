#include "Building.h"

Building::Building(const int x, const int y, const int hitPoints, const int energy, const int cost,
 				   const int width, const int height, BuildingType type)
	:Attackable(hitPoints, x, y)
	,energy(energy)
	,cost(cost)
	,width(width)
	,height(height)
	,key(type) {}

Building::~Building() {}

void Building::reciveBonusDammage(const Weapon &weapon) {
	life -= weapon.getBuildingBonus();
}

bool Building::is(Building::BuildingType type) {
    return this->key == type;
}