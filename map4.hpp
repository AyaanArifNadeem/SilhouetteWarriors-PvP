#pragma once
#include "player.hpp"
#include<raylib.h>

class map4{
private:
    Texture2D Background, c1, c2, c3, g1, g2, g3, sky;
    float scrollingMid, scrollingMid2, scrollingMid3, scrollingfront1, scrollingfront2, scrollingfront3;

public:
    float flooroffset;
    map4();
    ~map4();
    void update(player &p1, player &p2);
    void draw();
};