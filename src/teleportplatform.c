#include "simple_logger.h"

#include "teleportplatform.h"

void teleportplatform_think(Entity *self);
void teleportplatform_update(Entity *self);
void teleportplatform_free(Entity *self);
void teleportplatform_collide(Entity *self);
void teleportplatform_rhythm(Entity *self);
void teleportplatform_tape(Entity *self);
void teleportplatform_play(Entity *self);
void teleportplatform_rewind(Entity *self);

Entity *teleportplatform_new()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new teleportplatform entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/platform4.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = gfc_vector2d(1300,750);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = teleportplatform_think;
    self->update = teleportplatform_update;
    self->collide = teleportplatform_collide;
    self->free = teleportplatform_free;
    self->rhythm = teleportplatform_rhythm;
    self->type = 0;
    self->velocity = gfc_vector2d(1,0);
    self->moving = 4;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));

    self->play = teleportplatform_play;
    self->rewind = teleportplatform_rewind;
    self->tape = teleportplatform_tape;
    self->rewindPosition = malloc(sizeof(float)*100000);
    self->rewindNumber = 0;
    self->currentRewind = 0;
    self->rewinding = 0;
    self->win = 0;
    self->winCool = 0;


    return self;
}

void teleportplatform_tape(Entity *self)
{
    self->rewindPosition[self->rewindNumber] = self->position;
    self->rewindNumber++;
}

void teleportplatform_play(Entity *self)
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

void teleportplatform_rewind(Entity *self)
{
    if(!self)return;
    if(self->currentRewind>0 && self->rewinding==1 && self->win==0)
    {
        self->position = self->rewindPosition[self->currentRewind];
        self->currentRewind--;
    }
}

void teleportplatform_think(Entity *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);

}

void teleportplatform_rhythm(Entity *self)
{
    if(!self)return;
    if(self->moving==4)
    {
        self->moving=3;
        self->position = gfc_vector2d(self->position.x,self->position.y-300);
    }
    else if(self->moving==3)
    {
        self->moving=4;
        self->position = gfc_vector2d(self->position.x,self->position.y+300);
    }
}

void teleportplatform_update(Entity *self)
{
    if(!self)return;
    self->winCool++;
    teleportplatform_rewind(self);
    if(self->rewinding==0)
    {
        self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    }
    if (self->position.y >= 750)self->position.y = 750;
}

void teleportplatform_collide(Entity *self)
{
    if(!self)return;
}

void teleportplatform_free(Entity *self)
{
    if(!self)return;
}
