// -*-c++-*-
#ifndef CREATURE_H
#define CREATURE_H

#include "world.h"

class World;

class Creature
{
public:
    Creature();
    Creature(World *w);
    // ~Creature();

    int x;
    int y;
    char glyph;
    World *world;

    virtual void moveBy(int mx, int my) =0;
};

#endif
