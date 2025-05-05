#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "gfc_text.h"
#include "gfc_vector.h"
#include "gfc_shape.h"
#include "gfc_primitives.h"
#include "gf2d_sprite.h"


typedef struct Button_S //forward declaring struct while defining it
{
    Uint8           _inuse; /**<memory management flag*/
    int count;
    GFC_TextLine    name; /**<name of entity for debugging*/
    Sprite          *sprite; /**<graphic representation of entity*/
    float           frame; /**<for drawing the sprite*/
    GFC_Vector2D    position; /**<where to draw it*/
    GFC_Rect        box; /**<bounding box*/
    void (*think)(struct Button_S *self);
    void (*update)(struct Button_S *self);
    void (*free)(struct Button_S *self);
    void(*collide)(struct Button_S *self);
    void *data;
}Button;

/**
 * @brief initialize the button sub entity_system_init
 * @param maxButtons upper limit for how many buttons can exist at once.
 */
void menu_system_init(Uint32 maxButtons);

/**
 * @brief free all entities in the manager
 */
void menu_system_free_all();

/**
 *@brief get a new empty entity to work with
 * @return NULL if out of entities, or a blank entity otherwise.
 */
Button *button_new();

void button_free(Button *self);

void menu_system_think();

void button_collide();

void menu_system_collision(int x, int y);

void menu_system_update();

void menu_system_draw();

void button_draw(Button *self);

int main_menu();

#endif
