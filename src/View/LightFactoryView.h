#ifndef __LIGHT_FACTORY_VIEW_H__
#define __LIGHT_FACTORY_VIEW_H__

#include "BuildingView.h"
#include "../Buildings/LightFactory.h"
#include "Area.h"
#include "../Position.h"
#include "SdlWindow.h"
#include "SdlTexture.h"
#include <vector>
#include <map>
#include <string>

class LightFactoryView: public BuildingView{
    public:
        LightFactoryView(LightFactory& lightFactory, SdlWindow& window);
        virtual void draw(Area& camara);
    private:
        static std::map<std::string, std::vector<SdlTexture*> > sprites;
        std::vector<SdlTexture*>::iterator anim_it;
        SdlTexture* base;
};

#endif