#include "creature.h"
#include <cstdlib>

Creature::Creature(World *w)
{
    x = 0;
    y = 0;
    world = w;
}

// implemented by child classes
void Creature::moveBy(int mx, int my)
{

}

// implemented by child classes
void Creature::act()
{

}
