#ifndef __WORLD_H__
#define __WORLD_H__

#include "gf2d_sprite.h"

typedef struct
{
    Sprite *background;
    Sprite *tileLayer;
    Sprite *tileSet;
    Uint8 *tileMap;
    Uint32 tileHeight;
    Uint32 tileWidth;
}World;

World *world_load(const char *filename);

World *world_test_new();

void world_setup_camera(World *world);

World *world_new();

void world_free(World *world);

void world_draw(World *world);

#endif
