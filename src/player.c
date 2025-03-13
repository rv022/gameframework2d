#include "simple_logger.h"

#include "camera.h"
#include "player.h"

void player_think(Entity *self);
void player_update(Entity *self);
void player_free(Entity *self);
void player_collide(Entity *self);
void player_move(Entity *self);
void player_jump(Entity *self);
void player_rhythm(Entity *self);

Entity *player_new_entity()
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a new player entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/player.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = gfc_vector2d(0,835);
    self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);
    self->think = player_think;
    self->update = player_update;
    self->collide = player_collide;
    self->free = player_free;
    self->rhythm = player_rhythm;
    self->directionLeft = 0;
    self->directionRight = 0;
    self->verticalCollision = 0;
    self->type=1;
    self->rewindPosition = malloc(sizeof(float)*100000);
    self->rewindNumber = 0;
    self->rewind = 0;
    self->rewinding = 0;
    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
    self->win = 0;
    self->winCool = 0;

    return self;
}

void player_rhythm(Entity *self)
{
    if(!self)return;
    self->rewindPosition[self->rewindNumber] = self->position;
    self->rewindNumber++;
}

void player_rewind(Entity *self)
{
    if(!self)return;
    if(self->rewind>0 && self->rewinding==1 && self->win==0)
    {
        self->position = self->rewindPosition[self->rewind];
        self->rewind--;
    }
    if(self->win==1 && self->rewinding==1 && self->winCool>1)
    {
        if(self->rewind<self->rewindNumber && self->rewinding==1)
        {
            self->position = self->rewindPosition[self->rewind];
            self->rewind++;
            self->winCool=0;
        }
    }
}

void player_think(Entity *self)
{
    GFC_Vector2D dir = {0};
    int jump = 0;
    if(!self)return;
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_a:
                    self->directionLeft=1;
                    self->flip = gfc_vector2d_dup(gfc_vector2d(1,0));
                    break;
                case SDLK_d:
                    self->directionRight=1;
                    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
                    break;
                case SDLK_j:
                    self->jump=12;
                    break;
                case SDLK_r:
                    if(self->win==0)
                    {
                        if(self->rewind==0 && self->rewinding==0)
                            self->rewind = self->rewindNumber;
                        self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
                        self->rewinding=1;
                    }
                    break;
                case SDLK_p:
                    if(self->win==1 && self->rewinding==0)
                    {
                        self->rewind = 1;
                        self->winCool = 1;
                    }
                    self->flip = gfc_vector2d_dup(gfc_vector2d(0,0));
                    self->rewinding=1;
                break;
            }
        }
        else if(event.type==SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_a:
                    self->directionLeft=0;
                break;
                case SDLK_d:
                    self->directionRight=0;
                break;
                case SDLK_j:
                    break;
                case SDLK_r:
                    self->rewinding=0;
                    break;
                case SDLK_p:
                    self->rewinding=0;
                    break;
            }
        }
    }
    if(jump==1)
    {
        dir.y=-1;
    }
    gfc_vector2d_normalize(&dir);
    gfc_vector2d_scale(self->velocity,dir,3);
}

void player_move(Entity *self)
{
    GFC_Vector2D dir = {0};
    if(self->directionLeft==1)
        dir.x=-1;
    if(self->directionRight==1)
        dir.x=1;
    gfc_vector2d_normalize(&dir);
    gfc_vector2d_scale(self->velocity,dir,3);
}

void player_jump(Entity *self)
{
    //slog("player jumped");
    if(self->jump>0)
    {
        self->velocity.y -= 12;
        self->jump-=1;
    }
}

void player_update(Entity *self)
{

    if(!self)return;
    self->frame += 0.1;
    self->winCool++;
    if (self->frame >= 15)self->frame = 0;
    //46 to 65 is run
    //0 to 15 is idle
    player_move(self);
    player_gravity(self);
    player_jump(self);
    player_rewind(self);
    gfc_vector2d_add(self->position, self->position, self->velocity);
    if(self->rewinding==0)
        self->box = gfc_rect(self->position.x-40, self->position.y+55, 80, 110);

    camera_center_on(self->position);
}

void player_collide(Entity *self)
{
    if(!self)return;
    if(self->verticalCollision==1)
    {
        if(self->moving==1)
        {
            gfc_vector2d_add(self->position, self->position, gfc_vector2d_multiply(self->velocity,gfc_vector2d(-1,-2)));
            self->verticalCollision=0;
        }
        else
        {
            gfc_vector2d_add(self->position, self->position, gfc_vector2d_multiply(self->velocity,gfc_vector2d(1,-1)));
            //slog("vertical collision");
            self->verticalCollision=0;
        }
    }
    if(self->moving==1)
    {
        gfc_vector2d_add(self->position, self->position, gfc_vector2d_multiply(self->velocity,gfc_vector2d(1,-2)));
    }
    if(self->moving==2)
    {
        gfc_vector2d_add(self->position, self->position, gfc_vector2d_multiply(self->velocity,gfc_vector2d(1,1)));
    }
    else if(self->moving==3)
    {
        gfc_vector2d_add(self->position, self->position, gfc_vector2d_multiply(self->velocity,gfc_vector2d(1,-1)));
    }
    else if(self->moving==4)
    {
        gfc_vector2d_add(self->position, self->position, gfc_vector2d_multiply(self->velocity,gfc_vector2d(-1,-1)));
    }
    else
        gfc_vector2d_add(self->position, self->position, gfc_vector2d_multiply(self->velocity,gfc_vector2d(-1,-1)));

}

void player_gravity(Entity *self)
{
    self->velocity.y += 2;
    if (self->position.y >= 835)self->position.y = 835;
}
void player_free(Entity *self)
{
    if(!self)return;
}
