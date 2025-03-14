#include "simple_logger.h"

#include "winplatform.h"

void winplatform_think(Entity *self);
void winplatform_update(Entity *self);
void winplatform_free(Entity *self);
void winplatform_collide(Entity *self);
void winplatform_rhythm(Entity *self);

Entity *winplatform_new()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new winplatform entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/platform6.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = gfc_vector2d(2900,900);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = winplatform_think;
    self->update = winplatform_update;
    self->collide = winplatform_collide;
    self->free = winplatform_free;
    self->rhythm = winplatform_rhythm;
    self->type = 0;
    self->velocity = gfc_vector2d(1,0);
    self->moving = 4;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
    self->win = 0;


    return self;
}

void winplatform_think(Entity *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);

}

void winplatform_rhythm(Entity *self)
{
    if(!self)return;
    if(self->moving==3)
    {
        self->moving=4;
        self->win = 0;
        self->sprite = gf2d_sprite_load_all(
            "images/platform6.png",
            128,
            128,
            16,
            0);
    }
    else if(self->moving==4)
    {
        self->moving=3;
        self->win = 1;
        self->sprite = gf2d_sprite_load_all(
            "images/platform3.png",
            128,
            128,
            16,
            0);
    }
}

void winplatform_update(Entity *self)
{
    if(!self)return;
    //self->frame += 0.1;
    if (self->frame >= 15)self->frame = 0;
    //46 to 65 is run
    //0 to 15 is idle
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);

}

void winplatform_collide(Entity *self)
{
    if(!self)return;
}

void winplatform_free(Entity *self)
{
    if(!self)return;
}
