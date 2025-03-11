#include "simple_logger.h"

#include "camera.h"
#include "player.h"

void player_think(Entity *self);
void player_update(Entity *self);
void player_free(Entity *self);
Entity *player_new_entity()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new player entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/player.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = gfc_vector2d(0,0);

    self->think = player_think;
    self->update = player_update;
    self->free = player_free;

    return self;
}

void player_think(Entity *self)
{
    GFC_Vector2D dir = {0};
    if(!self)return;
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_W])
    {
        dir.y = -1;
    }
    if (keys[SDL_SCANCODE_S])
    {
        dir.y = 1;
    }
    if (keys[SDL_SCANCODE_D])
    {
        dir.x = 1;
    }
    if (keys[SDL_SCANCODE_A])
    {
        dir.x = -1;
    }
    gfc_vector2d_normalize(&dir);
    gfc_vector2d_scale(self->velocity,dir,3);
}

void player_update(Entity *self)
{
    if(!self)return;
    self->frame += 0.1;
    if (self->frame >= 15)self->frame = 0;
    //46 to 65 is run
    //0 to 15 is idle
    gfc_vector2d_add(self->position, self->position, self->velocity);

    camera_center_on(self->position);
}

void player_free(Entity *self)
{
    if(!self)return;
}
