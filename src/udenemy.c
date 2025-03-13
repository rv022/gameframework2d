#include "simple_logger.h"

#include "udenemy.h"

void udenemy_think(Entity *self);
void udenemy_update(Entity *self);
void udenemy_free(Entity *self);
void udenemy_collide(Entity *self);
void udenemy_rhythm(Entity *self);

Entity *udenemy_new()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new udenemy entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/enemy.png",
        128,
        128,
        16,
        0);
    self->frame = 3;
    self->position = gfc_vector2d(1200,750);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = udenemy_think;
    self->update = udenemy_update;
    self->collide = udenemy_collide;
    self->free = udenemy_free;
    self->rhythm = udenemy_rhythm;
    self->type = 2;
    self->velocity = gfc_vector2d(0,1);
    self->moving = 2;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
    self->health = 1;


    return self;
}

void udenemy_think(Entity *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);

}

void udenemy_rhythm(Entity *self)
{
    if(!self)return;
    if(self->moving==1)
    {
        self->moving=2;
        self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
        self->velocity = gfc_vector2d(0,3);
    }
    else if(self->moving==2)
    {
        self->moving=1;
        self->flip = gfc_vector2d_dup(gfc_vector2d(1,0));
        self->velocity = gfc_vector2d(0,-3);
    }
}

void udenemy_update(Entity *self)
{
    if(!self)return;
    //self->frame += 0.1; 35 36 are angry frame
    //if (self->frame >= 15)self->frame = 0;
    //46 to 65 is run
    //0 to 15 is idle
    gfc_vector2d_add(self->position, self->position, self->velocity);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);

}

void udenemy_collide(Entity *self)
{
    if(!self)return;
    if(self->health<1)
    {
        self->velocity.y=25;
    }
}

void udenemy_free(Entity *self)
{
    if(!self)return;
}
