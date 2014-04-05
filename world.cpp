#include "world.h"
#include "monster.h"
// #include "monster.h"
#include <stdio.h>
#include <time.h>
#include <cstdlib>

Tile::Tile()
{
    this->type = FLOOR;
    this->glyph = '.';
}

Tile::Tile(TileType type)
{
    this->type = type;
    if(type == FLOOR)
    {
        this->glyph = '.';
    }
    else if(type == WALL)
    {
        this->glyph = '#';
    }
}

void World::build()
{
    std::srand(time(NULL));
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            tiles[x][y]= (std::rand() % 10) < 5 ? Tile(FLOOR) : Tile(WALL);
        }
    }
    smooth(8);
}

void World::smooth(int times) {
    Tile tiles2[WIDTH][HEIGHT];
    for(int time = 0; time < times; time++) {
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                int floors = 0;
                int rocks = 0;
                for(int ox = -1; ox < 2; ox++) {
                    for(int oy = -1; oy < 2; oy++) {
                        if(x + ox < 0 || x + ox >= width || y + oy < 0 ||
                           y + oy >= height) {
                            continue;
                        }
                        if(tiles[x + ox][y + oy].type == FLOOR) {
                            floors++;
                        }
                        else {
                            rocks++;
                        }
                    }
                }
                tiles2[x][y] = floors >= rocks ? Tile(FLOOR) : Tile(WALL);
            }
        }
        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {
                tiles[i][j] = tiles2[i][j];
            }
        }
    }
}

World::World()
{
    this->width = WIDTH;
    this->height = HEIGHT;
    build();
}

void World::addToWorld(Creature *c)
{
    c->world = this;
    creatures.push_back(c);
    add(c);
}

void World::addToWorld(Creature *c, int x, int y)
{
    c->world = this;
    creatures.push_back(c);
    add(c, x, y);
}

void World::add(Creature *c)
{
    c->x = rand() % width;
    c->y = rand() % height;
    TileType tt = tiles[c->x][c->y].type;
    while(tt == BOUNDS || tt == WALL)
    {
        c->x = rand() % width;
        c->y = rand() % height;
        tt = tiles[c->x][c->y].type;
    }
}

void World::add(Creature *c, int x, int y)
{
    c->x = x;
    c->y = y;
}
