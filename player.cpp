#include "player.h"
#include "creature.h"

Player::Player() : Creature()
{
    glyph = '@';
}

Player::Player(World *w) : Creature(w)
{
    glyph = '@';
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
