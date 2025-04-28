#include "simple_logger.h"

#include "strongudenemy.h"

void strongudenemy_think(Entity *self);
void strongudenemy_update(Entity *self);
void strongudenemy_free(Entity *self);
void strongudenemy_collide(Entity *self);
void strongudenemy_rhythm(Entity *self);
void strongudenemy_rewind(Entity *self);
void strongudenemy_tape(Entity *self);
void strongudenemy_play(Entity *self);

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
    self->position = gfc_vector2d(400,835);
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
    self->health = 25;

    self->play = strongudenemy_play;
    self->rewind = strongudenemy_rewind;
    self->tape = strongudenemy_tape;
    self->rewindPosition = malloc(sizeof(float)*100000);
    self->rewindNumber = 0;
    self->currentRewind = 0;
    self->rewinding = 0;
    self->win = 0;
    self->winCool = 0;


    return self;
}

void strongudenemy_tape(Entity *self)
{
    self->rewindPosition[self->rewindNumber] = self->position;
    self->rewindNumber++;
    //slog("rewindNumber %i", self->rewindNumber);
}

void strongudenemy_play(Entity *self)
{
    if(!self)return;
    if(self->win==2 && self->rewinding==1 && self->winCool>1)
    {
        if(self->currentRewind<self->rewindNumber && self->rewinding==1)
        {
            //slog("currentRewind %i", self->currentRewind);
            self->position = self->rewindPosition[self->currentRewind];
            self->currentRewind++;
            self->winCool=0;
        }
    }
}

void strongudenemy_rewind(Entity *self)
{
    if(!self)return;
    if(self->currentRewind>0 && self->rewinding==1 && self->win==0)
    {
        self->position = self->rewindPosition[self->currentRewind];
        self->currentRewind--;
    }
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
    if(self->verticalCollision==0&&self->health!=25)
    {
        self->frame = 35;
        self->verticalCollision=1;
    }
    else if(self->verticalCollision==1&&self->health!=25)
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
    self->winCool++;
    strongudenemy_rewind(self);
    if(self->rewinding==0)
    {
        gfc_vector2d_add(self->position, self->position, self->velocity);
        self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    }
    if (self->position.y >= 835)self->position.y = 835;
}

void strongudenemy_collide(Entity *self)
{
    if(!self)return;
    if(self->health<1 && self->rewinding==0)
    {
        self->position.y=-10000;
    }
}

void strongudenemy_free(Entity *self)
{
    if(!self)return;
}
