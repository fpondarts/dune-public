#ifndef __PLAYER_COLOR_MAKER_H__
#define __PLAYER_COLOR_MAKER_H__

#include "../Model/Player.h"

class PlayerColorMaker{
    private:
        PlayerColorMaker();
    public:
        static void makeColor(Player& player, int* r, int* g, int* b);
};

#endif