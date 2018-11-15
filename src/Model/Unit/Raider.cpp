#include "Raider.h"
#include "../Weapons/Weapons.h"
#include "../GlobalConfig.h"

Raider::Raider(int x, int y) :
        OffensiveUnit(x, y, GlobalConfig.raiderHitPoints, GlobalConfig.raiderRange, Weapons::smallCannon,
                      GlobalConfig.raiderSpeed, GlobalConfig.raiderCost) {}

Raider::~Raider() {}

bool Raider::canMoveAboveTerrain(Terrain &terrain) {
	return terrain == Sand() || terrain == Dunes() || terrain == Rocks();
}

void Raider::reciveBonusDammage(const Weapon &weapon) {
	life -= weapon.getVehicleBonus();
}
