// -*-c++-*-
#ifndef PLAYER_H
#define PLAYER_H

#include "world.h"
#include "creature.h"
#include <string>

class World;

class Player: public Creature
{
public:
    Player(World *w, std::string name);

    void moveBy(int mx, int my);
};

#endif
