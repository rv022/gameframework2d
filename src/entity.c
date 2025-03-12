#include "simple_logger.h"

#include "camera.h"
#include "entity.h"

typedef struct
{
    Uint32 entity_max;
    Entity *entity_list;
}EntityManager;

static EntityManager entity_system = {0};

void entity_system_close()
{
    if(entity_system.entity_list)
    {
        entity_system_free_all();
        free(entity_system.entity_list);
        entity_system.entity_list = NULL;
    }
    memset(&entity_system.entity_list,0,sizeof(EntityManager));
}
void entity_system_init(Uint32 maxEnts)
{
    if(entity_system.entity_list)
    {
        slog("cannot have two instances of an entity manager, one is already active.");
        return;
    }
    if(!maxEnts)
    {
        slog("cannot initialize entity system for zero entities");
        return;
    }
    entity_system.entity_list = gfc_allocate_array(sizeof(Entity),maxEnts);
    if(!entity_system.entity_list)
    {
        slog("failed to allocate %i entities", maxEnts);
        return;
    }
    entity_system.entity_max = maxEnts;
    atexit(entity_system_close);
}

void entity_system_free_all()
{
    int i;
    for(i = 0; i<entity_system.entity_max;i++)
    {
        if(entity_system.entity_list[i]._inuse)
        {
            entity_free(&entity_system.entity_list[i]);
        }
    }
}


Entity *entity_new()
{
    int i;
    for(i = 0; i<entity_system.entity_max;i++)
    {
        if(entity_system.entity_list[i]._inuse)continue;
        memset(&entity_system.entity_list[i],0,sizeof(Entity));
        entity_system.entity_list[i]._inuse = 1;
        return &entity_system.entity_list[i];
    }
    slog("no more available entities.");
    return NULL;
}

void entity_collide(Entity *self)
{
        if(!self)return;
        if(self->collide)self->collide(self);
}

void entity_system_collision()
{
    int i,j;
    float t,p;
    if(entity_system.entity_list)
    {
        for(i = 0; i<entity_system.entity_max;i++)
        {
            if(entity_system.entity_list[i]._inuse)
            {
                for(j = 0; j<entity_system.entity_max;j++)
                {
                    if(entity_system.entity_list[j]._inuse)
                    {
                        if(i!=j)
                        {
                            if(gfc_rect_overlap(entity_system.entity_list[i].box,entity_system.entity_list[j].box))
                            {
                                t = entity_system.entity_list[i].position.y;
                                p = entity_system.entity_list[j].position.y;

                                if((p>(t+100)) && ((t+120)>p) && entity_system.entity_list[i].type==1)
                                {
                                    entity_system.entity_list[i].verticalCollision=1;
                                }
                                entity_collide(&entity_system.entity_list[i]);
                            }
                        }
                    }
                }
            }
        }
    }
}


void entity_free(Entity *self)
{
    if(!self)return;
    if(self->sprite)
    {
        gf2d_sprite_free(self->sprite);
        if(self->free)self->free(self->data);
    }
}

void entity_think(Entity *self)
{
    if(!self)return;
    if(self->think)self->think(self);
}

void entity_system_think()
{
    int i;
    for(i = 0; i<entity_system.entity_max;i++)
    {
        if(!entity_system.entity_list[i]._inuse)continue;
        entity_think(&entity_system.entity_list[i]);
    }

}

void entity_update(Entity *self)
{
    if(!self)return;
    if(self->update)self->update(self);
}

void entity_system_update()
{
    int i;
    for(i = 0; i<entity_system.entity_max;i++)
    {
        if(!entity_system.entity_list[i]._inuse)continue;
        entity_update(&entity_system.entity_list[i]);
    }

}

void entity_draw(Entity *self)
{
    GFC_Vector2D offset, position;
    if(!self)return;
    offset = camera_get_offset();
    gfc_vector2d_add(position,self->position,offset);
    if(!self->sprite)return;
    gf2d_sprite_draw(
                    (self->sprite),
                     position,
                     NULL,
                     NULL,
                     NULL,
                     NULL,
                     NULL,
                     (Uint32)self->frame
    );
}
void entity_system_draw()
{
    int i;
    for(i = 0; i<entity_system.entity_max;i++)
    {
        if(!entity_system.entity_list[i]._inuse)continue;
        entity_draw(&entity_system.entity_list[i]);
    }
}



/*eol@eof*/
