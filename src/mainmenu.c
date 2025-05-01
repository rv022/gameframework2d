#include <SDL.h>
#include "simple_logger.h"

#include "gf2d_graphics.h"

#include "entity.h"
#include "mainmenu.h"

typedef struct
{
    Uint32 button_max;
    Button *button_list;
}ButtonManager;

static ButtonManager menu_system = {0};

void menu_system_close()
{
    if(menu_system.button_list)
    {
        menu_system_free_all();
        free(menu_system.button_list);
        menu_system.button_list = NULL;
    }
    memset(&menu_system.button_list,0,sizeof(ButtonManager));
}

void menu_system_init(Uint32 maxButtons)
{
    if(menu_system.button_list)
    {
        slog("cannot have two instances of an button manager, one is already active.");
        return;
    }
    if(!maxButtons)
    {
        slog("cannot initialize menu system for zero buttons");
        return;
    }
    menu_system.button_list = gfc_allocate_array(sizeof(Button),maxButtons);
    if(!menu_system.button_list)
    {
        slog("failed to allocate %i buttons", maxButtons);
        return;
    }
    menu_system.button_max = maxButtons;
    atexit(menu_system_close);
}

void menu_system_free_all()
{
    int i;
    for(i = 0; i<menu_system.button_max;i++)
    {
        if(menu_system.button_list[i]._inuse)
        {
            button_free(&menu_system.button_list[i]);
        }
    }
}


Button *button_new()
{
    int i;
    for(i = 0; i<menu_system.button_max;i++)
    {
        if(menu_system.button_list[i]._inuse)continue;
        memset(&menu_system.button_list[i],0,sizeof(Button));
        menu_system.button_list[i]._inuse = 1;
        return &menu_system.button_list[i];
    }
    slog("no more available buttons.");
    return NULL;
}


void button_free(Button *self)
{
    if(!self)return;
    if(self->sprite)
    {
        gf2d_sprite_free(self->sprite);
        if(self->free)self->free(self->data);
    }

}

void button_collide(Button *self)
{
        if(!self)return;
        if(self->collide)self->collide(self);
}


void menu_system_collision()
{
    return;
}

void button_think(Button *self)
{
    if(!self)return;
    if(self->think)self->think(self);
}

void menu_system_think()
{
    int i;
    for(i = 0; i<menu_system.button_max;i++)
    {
        if(!menu_system.button_list[i]._inuse)continue;
        button_think(&menu_system.button_list[i]);
    }

}

void button_update(Button *self)
{
    if(!self)return;
    if(self->update)self->update(self);
}

void menu_system_update()
{
    int i;
    for(i = 0; i<menu_system.button_max;i++)
    {
        if(!menu_system.button_list[i]._inuse)continue;
        button_update(&menu_system.button_list[i]);
    }

}

void button_draw(Button *self)
{
    if(!self)return;
    if(!self->sprite)return;
    gf2d_sprite_draw(
                    (self->sprite),
                     self->position,
                     NULL,
                     NULL,
                     NULL,
                     NULL,
                     NULL,
                     (Uint32)self->frame
    );
}
void menu_system_draw()
{
    int i;
    for(i = 0; i<menu_system.button_max;i++)
    {
        if(!menu_system.button_list[i]._inuse)continue;
        button_draw(&menu_system.button_list[i]);
    }
}


















int main_menu(){

    int menu=0;

    int mx,my;
    float mf = 0;
    Sprite *mouse;

    GFC_Color mouseGFC_Color = gfc_color8(0,128,255,200);

    SDL_ShowCursor(SDL_DISABLE);

    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16,0);


    while(menu==0){

      SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;

    gf2d_graphics_clear_screen();

    menu_system_draw();


    gf2d_sprite_draw(
                mouse,
                gfc_vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseGFC_Color,
                (int)mf);

    gf2d_graphics_next_frame();

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_MOUSEBUTTONDOWN)
        {
            menu = 1;
            return 0;
        }
        if(event.type==SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_p:
                    menu = 1;
                    return 0;
                case SDLK_ESCAPE:
                    return 1;
}
        }}


}
return 0;
}
