#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_text.h"
#include "gfc_vector.h"
#include "gf2d_sprite.h"

typedef struct Entity_S //forward declaring struct while defining it
{
    Uint8           _inuse; /**<memory management flag*/
    GFC_TextLine    name; /**<name of entity for debugging*/
    Sprite          *sprite; /**<graphic representation of entity*/
    float           frame; /**<for drawing the sprite*/
    GFC_Vector2D    position; /**<where to draw it*/
    GFC_Vector2D    velocity; /**<how we are moving*/
    GFC_Vector2D    acceleration; /**<how we are moving*/
    void (*think)(struct Entity_S *self);
    void (*update)(struct Entity_S *self);
    void (*free)(struct Entity_S *self);
    void *data;
}Entity;

/**
 * @brief initialize the entity sub entity_system_init
 * @param maxEnts upper limit for how many entities can exist at once.
 */
void entity_system_init(Uint32 maxEnts);

/**
 * @brief free all entities in the manager
 */
void entity_system_free_all();

/**
 *@brief get a new empty entity to work with
 * @return NULL if out of entities, or a blank entity otherwise.
 */
Entity *entity_new();

void entity_free(Entity *self);

void entity_system_think();

void entity_system_update();

void entity_system_draw();

void entity_draw(Entity *self);

#endif
