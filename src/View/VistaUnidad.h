#ifndef __VISTA_UNIDAD_H__
#define __VISTA_UNIDAD_H__


#include "../Unit/Unit.h"
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "../Position.h"
#include <map>
#include "Orientacion.h"
#include "Area.h"

class VistaUnidad{
	public:
		VistaUnidad(Unit& unidad, SdlWindow& window);
		Unit& getUnit();
		void dibujar(Area camara);
	private:
		Unit& unidad;
		Position prev_pos;
		Orientacion orientacion;
		static std::map<int,SdlTexture*> vistas;
};

#endif