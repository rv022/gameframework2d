#ifndef __TELEPORTPLATFORM_H__
#define __TELEPORTPLATFORM_H__

#include "entity.h"

/**
 * @brief spawn a new teleportplatform entity
 * @param position where to spawn it
 * @return NULL on error, or a pointer to the spawned teleportplatform entity
 */
Entity *teleportplatform_new();


#endif
