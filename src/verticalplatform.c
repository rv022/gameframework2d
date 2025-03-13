#include "simple_logger.h"

#include "verticalplatform.h"

void verticalplatform_think(Entity *self);
void verticalplatform_update(Entity *self);
void verticalplatform_free(Entity *self);
void verticalplatform_collide(Entity *self);
void verticalplatform_rhythm(Entity *self);

Entity *verticalplatform_new()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new verticalplatform entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/platform2.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = gfc_vector2d(900,780);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = verticalplatform_think;
    self->update = verticalplatform_update;
    self->collide = verticalplatform_collide;
    self->free = verticalplatform_free;
    self->rhythm = verticalplatform_rhythm;
    self->type = 0;
    self->velocity = gfc_vector2d(0,-1);
    self->moving = 1;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));


    return self;
}

void verticalplatform_think(Entity *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);

}

void verticalplatform_rhythm(Entity *self)
{
    if(!self)return;
    if(self->moving==1)
    {
        self->moving=2;
        self->velocity = gfc_vector2d(0,1);
    }
    else if(self->moving==2)
    {
        self->moving=1;
        self->velocity = gfc_vector2d(0,-1);
    }
}

void verticalplatform_update(Entity *self)
{
    if(!self)return;
    //self->frame += 0.1;
    if (self->frame >= 15)self->frame = 0;
    //46 to 65 is run
    //0 to 15 is idle
    gfc_vector2d_add(self->position, self->position, self->velocity);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);

}

void verticalplatform_collide(Entity *self)
{
    if(!self)return;
}

void verticalplatform_free(Entity *self)
{
    if(!self)return;
}
