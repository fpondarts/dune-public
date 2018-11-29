#ifndef __HEAVY_FACTORY_H__
#define __HEAVY_FACTORY_H__

#include "Building.h"

class HeavyFactory : public Building {
public:
	explicit HeavyFactory(nlohmann::json& j);
	~HeavyFactory();
};

#endif
