typedef struct graphics
{
    SDL_Surface* surface;
    SDL_Rect screen;

    SDL_Rect outter;
    SDL_Color shade;
    SDL_Rect inner;

    SDL_Rect outline1;
    SDL_Rect outline2;
    SDL_Color dark;
    
    SDL_Rect path;
    SDL_Color path_color;
    
    SDL_Rect fill;
    SDL_Color fill_color;

    SDL_Rect fill1;
    SDL_Rect fill2;
    SDL_Rect fill3;
    SDL_Rect fill4;
} Graphics;

void graphicsInit( Graphics* gfx )
{
    // FFE5AC
    gfx->surface    = SDL_SetVideoMode( SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE );
    gfx->screen     = ( SDL_Rect  ){    0,    0, SCREEN_W, SCREEN_H };
    gfx->outter = ( SDL_Rect ){ 10, 10, 648, 648 };
    gfx->inner = ( SDL_Rect ){ 20, 20, 628, 628 };
    gfx->shade = ( SDL_Color ){ 0xFF, 0xE5, 0xAC, 0xFF };

    gfx->outline1 = ( SDL_Rect ){ 4, 4, 660, 660 };
    gfx->outline2 = ( SDL_Rect ){ 26, 26, 616, 616 };
    gfx->dark = ( SDL_Color ){ 0xCB, 0xB5, 0x83, 0xFF };

    //gfx->back       = ( SDL_Rect  ){    1,    1,      698,      698 };
    //gfx->back_color = ( SDL_Color ){ 0xFF, 0xFF,     0xFF,     0xFF };
    gfx->path       = ( SDL_Rect  ){   30,   30,      608,      608 };
    // C19059
    gfx->path_color = ( SDL_Color ){ 0x00, 0x00,     0x00,     0xFF };
    gfx->fill       = ( SDL_Rect  ){  150,  150,      368,      368 };
    gfx->fill_color = ( SDL_Color ){ 0xE0, 0xCA,     0x99,     0xFF };

    gfx->fill1 = ( SDL_Rect ){ 154, 154, 360, 360 };// fill_color
    gfx->fill2 = ( SDL_Rect ){ 160, 160, 348, 348 };// shade
    gfx->fill3 = ( SDL_Rect ){ 170, 170, 328, 328 };// fill_color
    gfx->fill4 = ( SDL_Rect ){ 176, 176, 316, 316 };// dark
}

void graphicsDraw( Graphics* gfx, Player* plyr, Target* trgt )
{
    // E0CA99
    // CBB583
    SDL_FillRect( gfx->surface, NULL, SDL_MapRGB( gfx->surface->format, gfx->dark.r, gfx->dark.g, gfx->dark.b ) );
    SDL_FillRect( gfx->surface, &gfx->outline1, SDL_MapRGB( gfx->surface->format, gfx->fill_color.r, gfx->fill_color.g, gfx->fill_color.b ) );
    SDL_FillRect( gfx->surface, &gfx->outter, SDL_MapRGB( gfx->surface->format, gfx->shade.r, gfx->shade.g, gfx->shade.b ) );
    SDL_FillRect( gfx->surface, &gfx->inner, SDL_MapRGB( gfx->surface->format, gfx->fill_color.r, gfx->fill_color.g, gfx->fill_color.b ) );
    SDL_FillRect( gfx->surface, &gfx->outline2, SDL_MapRGB( gfx->surface->format, gfx->dark.r, gfx->dark.g, gfx->dark.b ) );

    SDL_FillRect( gfx->surface, &gfx->path, SDL_MapRGB( gfx->surface->format, gfx->path_color.r, gfx->path_color.g, gfx->path_color.b ) );
    
    SDL_FillRect( gfx->surface, &gfx->fill, SDL_MapRGB( gfx->surface->format, gfx->dark.r, gfx->dark.g, gfx->dark.b ) );
    SDL_FillRect( gfx->surface, &gfx->fill1, SDL_MapRGB( gfx->surface->format, gfx->fill_color.r, gfx->fill_color.g, gfx->fill_color.b ) );
    SDL_FillRect( gfx->surface, &gfx->fill2, SDL_MapRGB( gfx->surface->format, gfx->shade.r, gfx->shade.g, gfx->shade.b ) );
    SDL_FillRect( gfx->surface, &gfx->fill3, SDL_MapRGB( gfx->surface->format, gfx->fill_color.r, gfx->fill_color.g, gfx->fill_color.b ) );
    SDL_FillRect( gfx->surface, &gfx->fill4, SDL_MapRGB( gfx->surface->format, gfx->dark.r, gfx->dark.g, gfx->dark.b ) );
    

    SDL_FillRect( gfx->surface, &trgt->clear, SDL_MapRGB( gfx->surface->format, 0x00, 0x00, 0x00 ) );
    SDL_FillRect( gfx->surface, &trgt->outter, SDL_MapRGB( gfx->surface->format, trgt->color.r, trgt->color.g, trgt->color.b ) );
    SDL_FillRect( gfx->surface, &trgt->fill, SDL_MapRGB( gfx->surface->format, 0x00, 0x00, 0x00 ) );
    SDL_FillRect( gfx->surface, &trgt->goal, SDL_MapRGB( gfx->surface->format, trgt->color.r, trgt->color.g, trgt->color.b ) );
    SDL_FillRect( gfx->surface, &trgt->inner, SDL_MapRGB( gfx->surface->format, 0x00, 0x00, 0x00 ) );
    
    SDL_FillRect( gfx->surface, &plyr->body, SDL_MapRGB( gfx->surface->format, plyr->body_color.r, plyr->body_color.g, plyr->body_color.b ) );
    SDL_FillRect( gfx->surface, &plyr->outter, SDL_MapRGB( gfx->surface->format, plyr->shade.r, plyr->shade.g, plyr->shade.b ) );
    SDL_FillRect( gfx->surface, &plyr->fill, SDL_MapRGB( gfx->surface->format, plyr->fill_color.r, plyr->fill_color.g, plyr->fill_color.b ) );
    SDL_FillRect( gfx->surface, &plyr->inner, SDL_MapRGB( gfx->surface->format, plyr->shade.r, plyr->shade.g, plyr->shade.b ) );
    SDL_FillRect( gfx->surface, &plyr->center, SDL_MapRGB( gfx->surface->format, plyr->body_color.r, plyr->body_color.g, plyr->body_color.b ) );
}
