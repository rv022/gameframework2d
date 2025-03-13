#include "simple_logger.h"

#include "platform.h"

void platform_think(Entity *self);
void platform_update(Entity *self);
void platform_free(Entity *self);
void platform_collide(Entity *self);
void rhythm(Entity *self);
void platform_tape(Entity *self);
void platform_play(Entity *self);
void platform_rewind(Entity *self);

Entity *platform_new()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new platform entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/platform5.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = gfc_vector2d(520,700);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = platform_think;
    self->update = platform_update;
    self->collide = platform_collide;
    self->free = platform_free;
    self->rhythm = rhythm;
    self->type = 0;
    self->velocity = gfc_vector2d(1,0);
    self->moving = 4;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));

    self->play = platform_play;
    self->rewind = platform_rewind;
    self->tape = platform_tape;
    self->rewindPosition = malloc(sizeof(float)*100000);
    self->rewindNumber = 0;
    self->currentRewind = 0;
    self->rewinding = 0;
    self->win = 0;
    self->winCool = 0;


    return self;
}

void platform_tape(Entity *self)
{
    self->rewindPosition[self->rewindNumber] = self->position;
    self->rewindNumber++;
}

void platform_play(Entity *self)
{
    if(!self)return;
    if(self->win==2 && self->rewinding==1 && self->winCool>1)
    {
        if(self->currentRewind<self->rewindNumber && self->rewinding==1)
        {
            self->position = self->rewindPosition[self->currentRewind];
            self->currentRewind++;
            self->winCool=0;
        }
    }
}

void platform_rewind(Entity *self)
{
    if(!self)return;
    if(self->currentRewind>0 && self->rewinding==1 && self->win==0)
    {
        self->position = self->rewindPosition[self->currentRewind];
        self->currentRewind--;
    }
}

void platform_think(Entity *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);

}

void rhythm(Entity *self)
{
    if(!self)return;
    if(self->moving==4)
    {
        self->moving=3;
        self->velocity = gfc_vector2d(-1,0);
    }
    else if(self->moving==3)
    {
        self->moving=4;
        self->velocity = gfc_vector2d(1,0);
    }
}

void platform_update(Entity *self)
{
    if(!self)return;
    self->winCool++;
    platform_rewind(self);
    if(self->rewinding==0)
    {
    gfc_vector2d_add(self->position, self->position, self->velocity);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    }

}

void platform_collide(Entity *self)
{
    if(!self)return;
}

void platform_free(Entity *self)
{
    if(!self)return;
}
