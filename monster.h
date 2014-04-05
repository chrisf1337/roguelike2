// -*-c++-*-
#ifndef MONSTER_H
#define MONSTER_H

#include "world.h"
#include "creature.h"
#include <string>

class Monster : public Creature
{
public:
    Monster(World *w, std::string name);

    void moveBy(int mx, int my);
    void act();
};

#endif
