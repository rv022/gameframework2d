#include "simple_logger.h"

#include "playbutton.h"

void play_think(Button *self);
void play_update(Button *self);
void play_free(Button *self);
void play_collide(Button *self);


Button *play_new()
{
    Button *self;
    self = button_new();
    if(!self)
    {
        slog("failed to spawn a new play button");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/platform.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = gfc_vector2d(50,50);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->count = 0;
    self->think = play_think;
    self->update = play_update;
    self->collide = play_collide;
    self->free = play_free;


    return self;
}

void play_think(Button *self)
{
    //GFC_Vector2D dir = {0};
    if(!self)return;
    //gfc_vector2d_normalize(&dir);
    //gfc_vector2d_scale(self->velocity,dir,3);

}


void play_update(Button *self)
{
    if(!self)return;
    //self->frame += 0.1; 35 36 are angry frame
    //if (self->frame >= 15)self->frame = 0;
    //46 to 65 is run
    //0 to 15 is idle
}

void play_collide(Button *self)
{
    if(!self)return;

}

void play_free(Button *self)
{
    if(!self)return;
}
