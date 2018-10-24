#ifndef __POSITIONABLE_H__
#define __POSITIONABLE_H__

#include "Position.h"

class Positionable {
protected:
    Position pos;
    int value;
public:
    Positionable(int x, int y);

    Position getPosition() const;

    int getValue();

};

#endif //__POSITIONABLE_H__
