#include "simple_logger.h"

#include "strongudenemy.h"

void strongudenemy_think(Entity *self);
void strongudenemy_update(Entity *self);
void strongudenemy_free(Entity *self);
void strongudenemy_collide(Entity *self);
void strongudenemy_rhythm(Entity *self);

Entity *strongudenemy_new()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new strongudenemy entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/enemy.png",
        128,
        128,
        16,
        0);
    self->frame = 1;
    self->position = gfc_vector2d(200,835);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = strongudenemy_think;
    self->update = strongudenemy_update;
    self->collide = strongudenemy_collide;
    self->free = strongudenemy_free;
    self->rhythm = strongudenemy_rhythm;
    self->type = 2;
    self->velocity = gfc_vector2d(0,-1);
    self->moving = 1;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
    self->health = 50;


    return self;
}

void strongudenemy_think(Entity *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);

}

void strongudenemy_rhythm(Entity *self)
{
    if(!self)return;
    if(self->moving==1)
    {
        self->moving=2;
        self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
        self->velocity = gfc_vector2d(0,1);
    }
    else if(self->moving==2)
    {
        self->moving=1;
        self->flip = gfc_vector2d_dup(gfc_vector2d(1,0));
        self->velocity = gfc_vector2d(0,-1);
    }
    if(self->verticalCollision==0&&self->health!=50)
    {
        self->frame = 35;
        self->verticalCollision=1;
    }
    else if(self->verticalCollision==1&&self->health!=50)
    {
        self->verticalCollision=0;
        self->frame = 1;
    }
}

void strongudenemy_update(Entity *self)
{
    if(!self)return;
    //self->frame += 0.1; 35 36 are angry frame
    //if (self->frame >= 15)self->frame = 0;
    //46 to 65 is run
    //0 to 15 is idle
    gfc_vector2d_add(self->position, self->position, self->velocity);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);

}

void strongudenemy_collide(Entity *self)
{
    if(!self)return;
    if(self->health<1)
    {
        self->velocity.y=25;
    }
}

void strongudenemy_free(Entity *self)
{
    if(!self)return;
}
