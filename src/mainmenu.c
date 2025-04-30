#include <SDL.h>
#include "simple_logger.h"

#include "gf2d_graphics.h"

#include "entity.h"
#include "mainmenu.h"

int main_menu(Sprite *image){

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



    gf2d_sprite_draw_image(image,gfc_vector2d(500,250));

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
