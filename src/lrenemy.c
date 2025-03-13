#include "simple_logger.h"

#include "lrenemy.h"

void lrenemy_think(Entity *self);
void lrenemy_update(Entity *self);
void lrenemy_free(Entity *self);
void lrenemy_collide(Entity *self);
void lrenemy_rhythm(Entity *self);

Entity *lrenemy_new()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new lrenemy entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/enemy.png",
        128,
        128,
        16,
        0);
    self->frame = 2;
    self->position = gfc_vector2d(1000,835);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = lrenemy_think;
    self->update = lrenemy_update;
    self->collide = lrenemy_collide;
    self->free = lrenemy_free;
    self->rhythm = lrenemy_rhythm;
    self->type = 2;
    self->velocity = gfc_vector2d(3,0);
    self->moving = 4;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
    self->health = 1;


    return self;
}

void lrenemy_think(Entity *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);

}

void lrenemy_rhythm(Entity *self)
{
    if(!self)return;
    if(self->moving==4)
    {
        self->moving=3;
        self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
        self->velocity = gfc_vector2d(-3,0);
    }
    else if(self->moving==3)
    {
        self->moving=4;
        self->flip = gfc_vector2d_dup(gfc_vector2d(1,0));
        self->velocity = gfc_vector2d(3,0);
    }
}

void lrenemy_update(Entity *self)
{
    if(!self)return;
    //self->frame += 0.1; 35 36 are angry frame
    //if (self->frame >= 15)self->frame = 0;
    //46 to 65 is run
    //0 to 15 is idle
    gfc_vector2d_add(self->position, self->position, self->velocity);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);

}

void lrenemy_collide(Entity *self)
{
    if(!self)return;
    if(self->health<1)
    {
        self->velocity.y=25;
    }
}

void lrenemy_free(Entity *self)
{
    if(!self)return;
}
