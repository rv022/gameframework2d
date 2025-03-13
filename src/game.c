#include <SDL.h>
#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"

#include "gfc_list.h"

#include "camera.h"
#include "entity.h"
#include "enemy.h"
#include "platform.h"
#include "verticalplatform.h"
#include "teleportplatform.h"
#include "launchplatform.h"
#include "winplatform.h"
#include "player.h"
#include "world.h"

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    World *world;
    int i = 0;
    int l = 35;
    //int list = 0;
    //int k = 0;

    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Sprite *rhythmNote;
    Sprite *cassette;
    Entity *player;
    Entity *platform;
    Entity *verticalPlatform;
    Entity *teleportPlatform;
    Entity *launchPlatform;
    Entity *winPlatform;

    GFC_Color mouseGFC_Color = gfc_color8(0,128,255,200);
    
    /*program initializtion*/
    init_logger("gf2d.log",0);
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        gfc_vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
    entity_system_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    camera_set_size(gfc_vector2d(1200,720));
    
    /*demo setup*/
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16,0);
    rhythmNote = gf2d_sprite_load_image("images/quarterNote.png");
    cassette = gf2d_sprite_load_image("images/cassette.png");


    slog("press [escape] to quit");
    player = player_new_entity();
    platform = platform_new();
    verticalPlatform = verticalplatform_new();
    teleportPlatform = teleportplatform_new();
    launchPlatform = launchplatform_new();
    winPlatform = winplatform_new();
    world = world_load("maps/testworld.map");
    world_setup_camera(world);

    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        i+=1;
        l-=1;
        //list = gfc_list_get_count(rewind);
        slog("%d",i);
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;

        //if (keys[SDL_SCANCODE_R])
        //{
            //for(int k = list; k>=0; k--)
                //player->position = gfc_list_get_nth(rewind,k);
        //}
        
        if((i%400)==0)
        {
            entity_rhythm(platform);
            entity_rhythm(verticalPlatform);
            entity_rhythm(launchPlatform);
        }
        if((i%200)==0)
        {
            entity_rhythm(winPlatform);
        }
        if((i%100)==0)
        {
            entity_rhythm(teleportPlatform);
        }
        if((i%10)==0)
        {
            if(player->win==0)
                entity_rhythm(player);
        }
        entity_system_think();
        entity_system_update();
        entity_system_collision();


        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            world_draw(world);
            
            entity_system_draw();

            //UI elements last
            gf2d_sprite_draw(
                mouse,
                gfc_vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseGFC_Color,
                (int)mf);

            if((i%100)==0)
            {
                l=35;
                gf2d_sprite_draw_image(rhythmNote,gfc_vector2d(550,0));
                //rewindPosition=player->position;
                //gfc_list_append(rewind,rewindPosition);
            }
            if(l>0)
                gf2d_sprite_draw_image(rhythmNote,gfc_vector2d(550,0));
            if(player->win==1)
                gf2d_sprite_draw_image(cassette,gfc_vector2d(0,0));




        gf2d_graphics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    entity_free(player);
    entity_free(platform);
    entity_free(verticalPlatform);
    entity_free(winPlatform);
    entity_free(teleportPlatform);
    entity_free(launchPlatform);
    world_free(world);
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
