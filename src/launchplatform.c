#include "simple_logger.h"

#include "launchplatform.h"

void launchplatform_think(Entity *self);
void launchplatform_update(Entity *self);
void launchplatform_free(Entity *self);
void launchplatform_collide(Entity *self);
void launchplatform_rhythm(Entity *self);

Entity *launchplatform_new()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new launchplatform entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/platform7.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = gfc_vector2d(1350,780);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = launchplatform_think;
    self->update = launchplatform_update;
    self->collide = launchplatform_collide;
    self->free = launchplatform_free;
    self->rhythm = launchplatform_rhythm;
    self->type = 0;
    self->velocity = gfc_vector2d(1,0);
    self->moving = 4;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));


    return self;
}

void launchplatform_think(Entity *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);

}

void launchplatform_rhythm(Entity *self)
{
    if(!self)return;
    if(self->moving==5)
    {
        self->moving=4;
        self->sprite = gf2d_sprite_load_all(
            "images/platform7.png",
            128,
            128,
            16,
            0);
    }
    else if(self->moving==4)
    {
        self->moving=5;
        self->sprite = gf2d_sprite_load_all(
            "images/platform.png",
            128,
            128,
            16,
            0);
    }
}

void launchplatform_update(Entity *self)
{
    if(!self)return;
    //self->frame += 0.1;
    if (self->frame >= 15)self->frame = 0;
    //46 to 65 is run
    //0 to 15 is idle
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);

}

void launchplatform_collide(Entity *self)
{
    if(!self)return;
}

void launchplatform_free(Entity *self)
{
    if(!self)return;
}
