#include "simple_logger.h"

#include "verticalplatform.h"

void verticalplatform_think(Entity *self);
void verticalplatform_update(Entity *self);
void verticalplatform_free(Entity *self);
void verticalplatform_collide(Entity *self);
void verticalplatform_rhythm(Entity *self);
void verticalplatform_tape(Entity *self);
void verticalplatform_play(Entity *self);
void verticalplatform_rewind(Entity *self);

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
    self->position = gfc_vector2d(1100,780);
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

    self->play = verticalplatform_play;
    self->rewind = verticalplatform_rewind;
    self->tape = verticalplatform_tape;
    self->rewindPosition = malloc(sizeof(float)*100000);
    self->rewindNumber = 0;
    self->currentRewind = 0;
    self->rewinding = 0;
    self->win = 0;
    self->winCool = 0;


    return self;
}

void verticalplatform_tape(Entity *self)
{
    self->rewindPosition[self->rewindNumber] = self->position;
    self->rewindNumber++;
}

void verticalplatform_play(Entity *self)
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

void verticalplatform_rewind(Entity *self)
{
    if(!self)return;
    if(self->currentRewind>0 && self->rewinding==1 && self->win==0)
    {
        self->position = self->rewindPosition[self->currentRewind];
        self->currentRewind--;
    }
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
    self->winCool++;
    verticalplatform_rewind(self);
    if(self->rewinding==0)
    {
    gfc_vector2d_add(self->position, self->position, self->velocity);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    }
    if (self->position.y >= 780)self->position.y = 780;

}

void verticalplatform_collide(Entity *self)
{
    if(!self)return;
}

void verticalplatform_free(Entity *self)
{
    if(!self)return;
}
