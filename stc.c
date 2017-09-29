#include <stdio.h>
#include <SDL/SDL.h>
#include <emscripten.h>

#define TRUE 1
#define FALSE 0
static int running = TRUE;

static const int SCREEN_W = 668;
static const int SCREEN_H = 668;

#include "colors.h"
#include "direction.h"
#include "player.h"
#include "target.h"
#include "graphics.h"

Graphics gfx;
Target trgt;
Player plyr;

void loop()
{
    static SDL_Event e;
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
        {
            running = FALSE;
        }
        else if( e.type == SDL_KEYDOWN )
        {
            if( e.key.keysym.sym == SDLK_SPACE && plyr.dir != STOP )
            {
                fixPlayerPos( &plyr );
                targetCheck( &trgt, &plyr );
                setTargetDir( &trgt );
                plyr.prev = plyr.dir;
                plyr.dir = STOP;
            }
        }
    }

    if( plyr.dir == STOP )
    {
        if( targetMove( &trgt ) == TRUE )
        {
            trgt.dir = STOP;
            //trgt.color = ( SDL_Color ){ 0x00, 0xCC, 0xFF, 0xFF };
            plyr.body_color = DARK_TURQ;
            plyr.shade = MIDDLE_TURQ;
            plyr.fill_color = LIGHT_TURQ;
            plyr.dir = plyr.prev;
        }
    }
    else
    {
        playerMovement( &plyr );
    }

    graphicsDraw( &gfx, &plyr, &trgt );
    SDL_Flip( gfx.surface );
}

int main( int argc, char* args[] )
{
    printf( "Press SPACE to stop the cube\n" );

    SDL_Init( SDL_INIT_VIDEO );
    graphicsInit( &gfx );
    targetInit( &trgt );
    playerInit( &plyr );

    #ifdef EMSCRIPTEN
        emscripten_set_main_loop( loop, 0, 1 );
    #else
        while( running == TRUE )
        {
            loop();
        }
    #endif

    SDL_Quit();
    printf( "SDL_Quit\n" );
    return 0;
}
