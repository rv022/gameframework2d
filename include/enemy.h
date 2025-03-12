#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.h"

/**
 * @brief spawn a new enemy entity
 * @param position where to spawn it
 * @return NULL on error, or a pointer to the spawned enemy entity
 */
Entity *enemy_new();

#endif
