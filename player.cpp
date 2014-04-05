#include <string>
#include "player.h"
#include "creature.h"

Player::Player(World *w, std::string name) : Creature(w)
{
    glyph = '@';
    level = 1;
    hp = 10;
    mp = 10;
    exp = 0;
    maxhp = 10;
    maxmp = 10;
    expToNextLevel = 5;
}

void Player::moveBy(int mx, int my)
{
    if(x + mx >= 0 && x + mx < world->width && y + my >= 0 && y + my < world->height)
    {
        Tile t = world->tiles[x + mx][y + my];
        if(t.type == FLOOR || t.type == WALL)
        {
            x += mx;
            y += my;
            if(t.type == WALL)
            {
                world->tiles[x][y].type = FLOOR;
                world->tiles[x][y].glyph = '.';
            }
        }
    }
}
