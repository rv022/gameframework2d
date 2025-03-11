#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"

/**
 * @brief spawn a new player entity
 * @param position where to spawn it
 * @return NULL on error, or a pointer to the spawned player entity
 */


Entity *player_new_entity();

void player_gravity(Entity *self);
void player_move(Entity *self);
void player_jump(Entity *self);

#endif
