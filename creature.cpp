#include "creature.h"
#include <cstdlib>

Creature::Creature()
{
    x = 0;
    y = 0;
    world = NULL;
}

Creature::Creature(World *w)
{
    x = 0;
    y = 0;
    world = w;
}

// Creature::~Creature()
// {
//     if(world != NULL)
//     {
//         delete world;
//     }
// }
