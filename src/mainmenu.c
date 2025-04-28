#include "simple_logger.h"

#include "gf2d_graphics.h"

#include "entity.h"
#include "mainmenu.h"

int main_menu(Sprite *image){
    int menu=0;

    while(menu==0){

    gf2d_graphics_clear_screen();

    gf2d_sprite_draw_image(image,gfc_vector2d(500,250));

    gf2d_graphics_next_frame();

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
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
