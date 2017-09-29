typedef struct target
{
    SDL_Rect clear;
    SDL_Rect outter;
    SDL_Rect fill;
    SDL_Rect goal;
    SDL_Rect inner;
    SDL_Color color;
    Direction dir;
    int x_speed, y_speed;
} Target;

static int say_corner_collide = FALSE;
static int say_player_scored  = FALSE;

void targetInit( Target* trgt )
{
    trgt->clear  = ( SDL_Rect  ){    8,    8,  164,  164 };
    trgt->outter = ( SDL_Rect  ){   12,   12,  156,  156 };
    trgt->fill   = ( SDL_Rect  ){   25,   25,  130,  130 };
    trgt->goal   = ( SDL_Rect  ){   29,   29,  122,  122 };
    trgt->inner  = ( SDL_Rect  ){   30,   30,  120,  120 };
    trgt->color  = ( SDL_Color ){ 0x00, 0xCC, 0xFF, 0xFF };
    trgt->dir    = STOP;
    trgt->x_speed = 0;
    trgt->y_speed = 0;
}

void targetCheck( Target* trgt, Player* plyr )
{
    int plyr_x = plyr->body.x;
    int plyr_y = plyr->body.y;
    int plyr_w = plyr->body.x + plyr->body.w;
    int plyr_h = plyr->body.y + plyr->body.h;

    int outt_x = trgt->outter.x;
    int outt_y = trgt->outter.y;
    int outt_w = trgt->outter.x + trgt->outter.w;
    int outt_h = trgt->outter.y + trgt->outter.h;

    int fill_x = trgt->fill.x;
    int fill_y = trgt->fill.y;
    int fill_w = trgt->fill.x + trgt->fill.w;
    int fill_h = trgt->fill.y + trgt->fill.h;

    int goal_x = trgt->goal.x;
    int goal_y = trgt->goal.y;
    int goal_w = trgt->goal.x + trgt->goal.w;
    int goal_h = trgt->goal.y + trgt->goal.h;

    say_player_scored = FALSE;

    if( plyr_x >= outt_x && plyr_y >= outt_y && plyr_w <= outt_w && plyr_h <= outt_h )
    {
        //trgt->color = ( SDL_Color ){ 0xFF, 0xFF, 0x00, 0xFF };
        plyr->body_color = DARK_ORANGE;
        plyr->shade = MIDDLE_ORANGE;
        plyr->fill_color = LIGHT_ORANGE;
        if( plyr_x >= fill_x && plyr_y >= fill_y && plyr_w <= fill_w && plyr_h <= fill_h )
        {
            //trgt->color = ( SDL_Color ){ 0x00, 0xFF, 0xFF, 0xFF };
            plyr->body_color = DARK_GOLD;
            plyr->shade = MIDDLE_GOLD;
            plyr->fill_color = LIGHT_GOLD;
            if( plyr_x >= goal_x && plyr_y >= goal_y && plyr_w <= goal_w && plyr_h <= goal_h )
            {
                //trgt->color = ( SDL_Color ){ 0x00, 0xFF, 0x00, 0xFF };
                plyr->body_color = DARK_GREEN;
                plyr->shade = MIDDLE_GREEN;
                plyr->fill_color = LIGHT_GREEN;
            }
        }
        say_player_scored = TRUE;
    }
    else
    {
        //trgt->color = DARK_RED;
        plyr->body_color = DARK_RED;
        plyr->shade = MIDDLE_RED;
        plyr->fill_color = LIGHT_RED;
    }
    //return say_player_scored;
}

int targetMove( Target* trgt )
{
    //printf( "1: ( %d, %d )\n", trgt->clear.x, trgt->clear.y );
    trgt->clear.x += trgt->x_speed;
    trgt->clear.y += trgt->y_speed;
    //printf( "2: ( %d, %d )\n", trgt->clear.x, trgt->clear.y );

    say_corner_collide = FALSE;

    if( trgt->clear.x <= 8 && trgt->clear.y <= 8 ) // top left
    {   
        if( trgt->dir == UP || trgt->dir == LEFT )
        {
            trgt->dir = STOP;
            trgt->clear.x = 8;
            trgt->clear.y = 8;
            say_corner_collide = TRUE;
        }
    }
    else if( trgt->clear.x >= 495 && trgt->clear.y <= 8 ) // top right
    {   
        if( trgt->dir == RIGHT || trgt->dir == UP )
        {
            trgt->dir = STOP;
            trgt->clear.x = 495;
            trgt->clear.y = 8;
            say_corner_collide = TRUE;
        }
    }
    else if( trgt->clear.x >= 495 && trgt->clear.y >= 495 ) // bottom right
    {   
        if( trgt->dir == DOWN || trgt->dir == RIGHT )
        {
            trgt->dir = STOP;
            trgt->clear.x = 495;
            trgt->clear.y = 495;
            say_corner_collide = TRUE;
        }
    }
    else if( trgt->clear.x <= 8 && trgt->clear.y >= 495 ) // bottom left
    {   
        if( trgt->dir == LEFT || trgt->dir == DOWN )
        {
            trgt->dir = STOP;
            trgt->clear.x = 8;
            trgt->clear.y = 495;
            say_corner_collide = TRUE;
        }
    } 

    /*if( say_corner_collide == TRUE )
    {
        printf( "3: ( %d, %d )\n", trgt->clear.x, trgt->clear.y );
    }
    printf( "\n" );*/
    
    trgt->outter.x = trgt->clear.x  +  4;
    trgt->outter.y = trgt->clear.y  +  4;
    trgt->fill.x   = trgt->outter.x + 13;
    trgt->fill.y   = trgt->outter.y + 13;
    trgt->goal.x   = trgt->fill.x   +  4;
    trgt->goal.y   = trgt->fill.y   +  4;
    trgt->inner.x  = trgt->goal.x   +  1;
    trgt->inner.y  = trgt->goal.y   +  1;

    return say_corner_collide;
}

void setTargetDir( Target* trgt )
{
    if( trgt->clear.x == 8 && trgt->clear.y == 8 ) // top left
    {
        if( say_player_scored == TRUE )
        {
            trgt->x_speed =     5;
            trgt->y_speed =     0;
            trgt->dir     = RIGHT;
        }
        else
        {
            trgt->x_speed =    0;
            trgt->y_speed =    5;
            trgt->dir     = DOWN;
        }
    }
    else if( trgt->clear.x == 495 && trgt->clear.y == 8 ) // top right
    {
        if( say_player_scored == TRUE )
        {
            trgt->x_speed =    0;
            trgt->y_speed =    5;
            trgt->dir     = DOWN;
        }
        else
        {
            trgt->x_speed =   -5;
            trgt->y_speed =    0;
            trgt->dir     = LEFT;
        }
    }
    else if( trgt->clear.x == 495 && trgt->clear.y == 495 ) // bottom right
    {
        if( say_player_scored == TRUE )
        {
            trgt->x_speed =   -5;
            trgt->y_speed =    0;
            trgt->dir     = LEFT;
        }
        else
        {
            trgt->x_speed =  0;
            trgt->y_speed = -5;
            trgt->dir     = UP;
        }
    }
    else if( trgt->clear.x == 8 && trgt->clear.y == 495 ) // bottom left
    {
        if( say_player_scored == TRUE )
        {
            trgt->x_speed =  0;
            trgt->y_speed = -5;
            trgt->dir     = UP;
        }
        else
        {
            trgt->x_speed =     5;
            trgt->y_speed =     0;
            trgt->dir     = RIGHT;
        }
    }
    else
    {
        trgt->x_speed =    0;
        trgt->y_speed =    0;
        trgt->dir     = STOP;
    }
}
