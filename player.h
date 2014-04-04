// -*-c++-*-
#ifndef PLAYER_H
#define PLAYER_H

#include "world.h"
#include "creature.h"

class World;

class Player: public Creature
{
public:
    Player();
    Player(World *w);

    void moveBy(int mx, int my);
};

#endif
