#include "simple_logger.h"

#include "enemy.h"

void enemy_think(Entity *self);
void enemy_update(Entity *self);
void enemy_free(Entity *self);
void enemy_collide(Entity *self);
Entity *enemy_new()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new enemy entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/enemy.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = gfc_vector2d(120,700);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = enemy_think;
    self->update = enemy_update;
    self->collide = enemy_collide;
    self->free = enemy_free;
    self->type = 0;
    self->velocity = gfc_vector2d(1,0);
    self->moving = 2;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));

    return self;
}

void enemy_think(Entity *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);
}

void enemy_update(Entity *self)
{
    if(!self)return;
    //self->frame += 0.1;
    if (self->frame >= 15)self->frame = 0;
    //46 to 65 is run
    //0 to 15 is idle
    gfc_vector2d_add(self->position, self->position, self->velocity);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);

}

void enemy_collide(Entity *self)
{
    if(!self)return;
}

void enemy_free(Entity *self)
{
    if(!self)return;
}
