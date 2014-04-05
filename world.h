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

public:
    World();

    int width;
    int height;
    std::vector<Creature*> creatures;
    Tile tiles[WIDTH][HEIGHT];

    void addToWorld(Creature *c, int x, int y);
    void addToWorld(Creature *c);
    void add(Creature *c, int x, int y);
    void add(Creature *c);
    void build();
};

#endif
