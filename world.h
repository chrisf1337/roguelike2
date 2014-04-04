// -*-c++-*-
#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "creature.h"

const int WIDTH = 100;
const int HEIGHT = 100;

class Creature;

enum TileType
{
    FLOOR, WALL, BOUNDS
};

class Tile
{
public:
    Tile();
    Tile(TileType type);

    TileType type;
    char glyph;
};

class World
{
private:
    void smooth(int times);
    void placeRandomly(Creature *c);

public:
    World();

    int width;
    int height;
    std::vector<Creature*> creatures;
    Tile tiles[WIDTH][HEIGHT];

    void addToWorld(Creature *c);

    void build();
};

#endif
