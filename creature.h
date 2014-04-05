// -*-c++-*-
#ifndef CREATURE_H
#define CREATURE_H

#include "world.h"
#include <string>

class World;

class Creature
{
public:
    Creature(World *w);

    int x;
    int y;
    char glyph;
    World *world;

    std::string name;
    int level;
    int hp;
    int mp;
    int exp;
    int maxhp;
    int maxmp;
    int expToNextLevel;

    virtual void moveBy(int mx, int my);
    virtual void act();
};

#endif
