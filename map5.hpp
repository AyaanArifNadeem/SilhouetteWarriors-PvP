#pragma once
#include "player.hpp"
#include<raylib.h>

class map5{
private:
    Texture2D Background, c2, c3, c4, g1, g2, sky;
    float scrollingMid, scrollingMid2, scrollingMid3, scrollingfront1, scrollingfront2, scrollingfront3;

public:
    float flooroffset;
    map5();
    ~map5();
    void update(player &p1, player &p2);
    void draw();
};