#include "monster.h"
#include <cstdlib>

Monster::Monster(World *w, std::string name) : Creature(w)
{
    glyph = 'm';
    level = 1;
    hp = 5;
    mp = 5;
    exp = 0;
    maxhp = 5;
    maxmp = 5;
    expToNextLevel = 5;
}

void Monster::moveBy(int mx, int my)
{
    if(x + mx >= 0 && x + mx < world->width && y + my >= 0 && y + my < world->height)
    {
        Tile t = world->tiles[x + mx][y + my];
        if(t.type == FLOOR)
        {
            x += mx;
            y += my;
        }
    }
}

void Monster::act()
{
    int mx = rand() % 3 - 1;
    int my = rand() % 3 - 1;
    while(!(x + mx >= 0 && x + mx < world->width))
    {
        mx = rand() % 3 - 1;
    }
    while(!(y + my >= 0 && y + my < world->height))
    {
        my = rand() % 3 - 1;
    }
    moveBy(mx, my);
}
