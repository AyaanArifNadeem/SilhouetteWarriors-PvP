#pragma once
#include "player.hpp"
#include<raylib.h>

class map1{
private:
    Texture2D Background, c1, c2, g1, g2, g3, rocks, sky;
    float scrollingMid, scrollingMid2, scrollingfront1, scrollingfront2, scrollingfront3;

public:
    float flooroffset;
    map1();
    ~map1();
    void update(player &p1, player &enemy);
    void draw();
};