#ifndef __TELEPORTENEMY_H__
#define __TELEPORTENEMY_H__

#include "entity.h"

/**
 * @brief spawn a new teleportenemy entity
 * @param position where to spawn it
 * @return NULL on error, or a pointer to the spawned teleportenemy entity
 */
Entity *teleportenemy_new();

#endif
