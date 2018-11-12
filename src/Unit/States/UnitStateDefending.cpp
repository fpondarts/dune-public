#include "UnitStateDefending.h"

#include "../Unit.h"

UnitState *UnitStateDefending::makeAction(Map &map, Unit &unit) {
    return unit.makeDefending(map);
}

bool UnitStateDefending::isAttacking() {
    return true;
}
