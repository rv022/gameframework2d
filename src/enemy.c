#include "simple_logger.h"

#include "enemy.h"

void enemy_think(Entity *self);
void enemy_update(Entity *self);
void enemy_free(Entity *self);
void enemy_collide(Entity *self);
void enemy_rhythm(Entity *self);
void enemy_rewind(Entity *self);
void enemy_tape(Entity *self);
void enemy_play(Entity *self);

Entity *enemy_new()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new enemy entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/enemy.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = gfc_vector2d(500,835);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = enemy_think;
    self->update = enemy_update;
    self->collide = enemy_collide;
    self->free = enemy_free;
    self->rhythm = enemy_rhythm;
    self->type = 2;
    self->velocity = gfc_vector2d(1,0);
    self->moving = 4;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
    self->health = 50;

    self->play = enemy_play;
    self->rewind = enemy_rewind;
    self->tape = enemy_tape;
    self->rewindPosition = malloc(sizeof(float)*100000);
    self->rewindNumber = 0;
    self->currentRewind = 0;
    self->rewinding = 0;
    self->win = 0;
    self->winCool = 0;


    return self;
}

void enemy_tape(Entity *self)
{
    self->rewindPosition[self->rewindNumber] = self->position;
    self->rewindNumber++;
}

void enemy_play(Entity *self)
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

void enemy_rewind(Entity *self)
{
    if(!self)return;
    if(self->currentRewind>0 && self->rewinding==1 && self->win==0)
    {
        self->position = self->rewindPosition[self->currentRewind];
        self->currentRewind--;
    }
}

void enemy_think(Entity *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);

}



void enemy_rhythm(Entity *self)
{
    if(!self)return;
    if(self->moving==4)
    {
        self->moving=3;
        self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
        self->velocity = gfc_vector2d(-1,0);
    }
    else if(self->moving==3)
    {
        self->moving=4;
        self->flip = gfc_vector2d_dup(gfc_vector2d(1,0));
        self->velocity = gfc_vector2d(1,0);
    }
    if(self->verticalCollision==0&&self->health!=50)
    {
        self->frame = 34;
        self->verticalCollision=1;
    }
    else if(self->verticalCollision==1&&self->health!=50)
    {
        self->verticalCollision=0;
        self->frame = 0;
    }

}

void enemy_update(Entity *self)
{
    if(!self)return;
    //self->frame += 0.1; 35 36 are angry frame
    //if (self->frame >= 15)self->frame = 0;
    //46 to 65 is run
    //0 to 15 is idle
    self->winCool++;
    enemy_rewind(self);
    if(self->rewinding==0)
    {
        gfc_vector2d_add(self->position, self->position, self->velocity);
        self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    }
    if (self->position.y >= 835)self->position.y = 835;

}

void enemy_collide(Entity *self)
{
    if(!self)return;
    if(self->health<1 && self->rewinding==0)
    {
        self->position.y=-10000;
    }
}

void enemy_free(Entity *self)
{
    if(!self)return;
}
