typedef struct player
{
    SDL_Rect body;
    SDL_Color body_color;

    SDL_Rect fill;
    SDL_Color fill_color;

    SDL_Rect outter;
    SDL_Rect inner;
    SDL_Color shade;

    SDL_Rect center;

    SDL_Rect bounds;
    int x_speed, y_speed;
    Direction dir;
    Direction prev;
} Player;


void playerInit( Player* plyr )
{
    // 20AEC9 [ body_color ]( dark outter line )
    // 4DDBF6 [ shade ]( middle gradient )
    // 64E7FF [ fill_color ]( light )
    plyr->body   = ( SDL_Rect ){ 30, 30, 120, 120 };
    plyr->outter = ( SDL_Rect ){ 40, 40, 100, 100 };
    plyr->fill   = ( SDL_Rect ){ 44, 44,  92,  92 };
    plyr->inner  = ( SDL_Rect ){ 51, 51,  78,  78 };
    plyr->center = ( SDL_Rect ){ 55, 55,  70,  70 };

    plyr->body_color = ( SDL_Color ){ 0x20, 0xAE, 0xC9, 0xFF };
    plyr->fill_color = ( SDL_Color ){ 0x64, 0xE7, 0xFF, 0xFF };
    plyr->shade      = ( SDL_Color ){ 0x4D, 0xDB, 0xF6, 0xFF };

    plyr->bounds  = ( SDL_Rect  ){ 30, 30, 518, 518 };
    plyr->x_speed = plyr->y_speed = 0;
    plyr->dir     = ( Direction )RIGHT;
    plyr->prev    = ( Direction )STOP;
}

void fixPlayerPos( Player* plyr )
{
    if( plyr->body.x == plyr->bounds.x && plyr->body.y <= plyr->bounds.y )
    {
        plyr->body.y = plyr->bounds.y;
    }
    if( plyr->body.x >= plyr->bounds.w && plyr->body.y == plyr->bounds.y )
    {
        plyr->body.x = plyr->bounds.w;
    }
    if( plyr->body.x == plyr->bounds.w && plyr->body.y >= plyr->bounds.h )
    {
        plyr->body.y = plyr->bounds.h;
    }
    if( plyr->body.x <= plyr->bounds.x && plyr->body.y == plyr->bounds.h )
    {
        plyr->body.x = plyr->bounds.x;
    }

    plyr->outter.x = plyr->body.x + 10;
    plyr->outter.y = plyr->body.y + 10;
    plyr->fill.x = plyr->outter.x + 4;
    plyr->fill.y = plyr->outter.y + 4;
    plyr->inner.x = plyr->fill.x + 7;
    plyr->inner.y = plyr->fill.y + 7;
    plyr->center.x = plyr->inner.x + 4;
    plyr->center.y = plyr->inner.y + 4;
}

void playerMovement( Player* plyr )
{
    if( plyr->body.x == plyr->bounds.x && plyr->body.y <= plyr->bounds.y )
    {
        plyr->body.y = plyr->bounds.y;
        plyr->dir = RIGHT;
    }
    else if( plyr->body.x >= plyr->bounds.w && plyr->body.y == plyr->bounds.y )
    {
        plyr->body.x = plyr->bounds.w;
        plyr->dir = DOWN;
    }
    else if( plyr->body.x == plyr->bounds.w && plyr->body.y >= plyr->bounds.h )
    {
        plyr->body.y = plyr->bounds.h;
        plyr->dir = LEFT;
    }
    else if( plyr->body.x <= plyr->bounds.x && plyr->body.y == plyr->bounds.h )
    {
        plyr->body.x = plyr->bounds.x;
        plyr->dir = UP;
    }

    switch( plyr->dir )
    {
        case RIGHT:
            plyr->x_speed = 5;
            plyr->y_speed = 0;
            break;
        case DOWN:
            plyr->x_speed = 0;
            plyr->y_speed = 5;
            break;
        case LEFT:
            plyr->x_speed = -5;
            plyr->y_speed = 0;
            break;
        case UP:
            plyr->x_speed = 0;
            plyr->y_speed = -5;
            break;
        case STOP:
            plyr->x_speed = 0;
            plyr->y_speed = 0;
            break;
    }

    plyr->body.x += plyr->x_speed;
    plyr->body.y += plyr->y_speed;

    plyr->outter.x = plyr->body.x + 10;
    plyr->outter.y = plyr->body.y + 10;
    plyr->fill.x = plyr->outter.x + 4;
    plyr->fill.y = plyr->outter.y + 4;
    plyr->inner.x = plyr->fill.x + 7;
    plyr->inner.y = plyr->fill.y + 7;
    plyr->center.x = plyr->inner.x + 4;
    plyr->center.y = plyr->inner.y + 4;
}
