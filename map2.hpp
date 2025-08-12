#pragma once
#include "player.hpp"
#include<raylib.h>

class map2{
private:
    Texture2D Background, c1, c2, g1, rocks, sky;
    float scrollingMid, scrollingMid2, scrollingfront1, scrollingfront2, scrollingfront3;

public:
    float flooroffset;
    map2();
    ~map2();
    void update(player &p1, Rectangle &enemy);
    void draw();
};