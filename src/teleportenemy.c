#include "simple_logger.h"

#include "teleportenemy.h"

void teleportenemy_think(Entity *self);
void teleportenemy_update(Entity *self);
void teleportenemy_free(Entity *self);
void teleportenemy_collide(Entity *self);
void teleportenemy_rhythm(Entity *self);
void teleportenemy_tape(Entity *self);
void teleportenemy_play(Entity *self);
void teleportenemy_rewind(Entity *self);

Entity *teleportenemy_new()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new teleportenemy entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/enemy.png",
        128,
        128,
        16,
        0);
    self->frame = 4;
    self->position = gfc_vector2d(2100,835);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = teleportenemy_think;
    self->update = teleportenemy_update;
    self->collide = teleportenemy_collide;
    self->free = teleportenemy_free;
    self->rhythm = teleportenemy_rhythm;
    self->type = 2;
    self->velocity = gfc_vector2d(1,0);
    self->moving = 4;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
    self->health = 1;

    self->play = teleportenemy_play;
    self->rewind = teleportenemy_rewind;
    self->tape = teleportenemy_tape;
    self->rewindPosition = malloc(sizeof(float)*100000);
    self->rewindNumber = 0;
    self->currentRewind = 0;
    self->rewinding = 0;
    self->win = 0;
    self->winCool = 0;


    return self;
}

void teleportenemy_tape(Entity *self)
{
    self->rewindPosition[self->rewindNumber] = self->position;
    self->rewindNumber++;
}

void teleportenemy_play(Entity *self)
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

void teleportenemy_rewind(Entity *self)
{
    if(!self)return;
    if(self->currentRewind>0 && self->rewinding==1 && self->win==0)
    {
        self->position = self->rewindPosition[self->currentRewind];
        self->currentRewind--;
    }
}

void teleportenemy_think(Entity *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);

}

void teleportenemy_rhythm(Entity *self)
{
    if(!self)return;
    if(self->moving==4)
    {
        self->moving=3;
        self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
        self->position.x-=300;
    }
    else if(self->moving==3)
    {
        self->moving=2;
        self->flip = gfc_vector2d_dup(gfc_vector2d(0,1));
        self->position.y-=300;
    }
    else if(self->moving==2)
    {
        self->moving=1;
        self->flip = gfc_vector2d_dup(gfc_vector2d(1,1));
        self->position.x+=300;
    }
    else if(self->moving==1)
    {
        self->moving=4;
        self->flip = gfc_vector2d_dup(gfc_vector2d(1,0));
        self->position.y+=300;
    }
}

void teleportenemy_update(Entity *self)
{
    if(!self)return;
    self->winCool++;
    teleportenemy_rewind(self);
    if(self->rewinding==0)
    {
        self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    }
    if (self->position.y >= 835)self->position.y = 835;

}

void teleportenemy_collide(Entity *self)
{
    if(!self)return;
    if(self->health<1 && self->rewinding==0)
    {
        self->position.y=-10000;
    }
}

void teleportenemy_free(Entity *self)
{
    if(!self)return;
}
