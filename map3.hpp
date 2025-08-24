#pragma once
#include "player.hpp"
#include<raylib.h>

class map3{
private:
    Texture2D Background, g1, g2, rocks, sky;
    float scrollingfront1, scrollingfront2;

public:
    float flooroffset;
    map3();
    ~map3();
    void update(player &p1, player &p2);
    void draw();
};