//
//  setup.c
//  Bomberman
//
//  Created by agbo anthony on 26/06/2016.
//  Copyright (c) 2016 agbo anthony. All rights reserved.
//

#include "client.h"

// permet d'initialiser toutes les fonctionnalités de la SDL
int setup_SDL(){
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Erreur lors de l'initialisation de la SDL : %s", SDL_GetError());
        SDL_Quit();
        
        return -1;
    }
    return 1;
}

TTF_Font* Create_font( char* name, int size){
    TTF_Font* font;
    
    if ( TTF_Init() == -1 )
    {
        printf("Erreur lors de l'initialisation de ttf : %s", SDL_GetError());
        return font;
    }
    
    // Load our fonts, with a  X size
    font = TTF_OpenFont( name, size);
    
    // Error check
    if ( !font )
    {
        printf("Erreur de chargement : %s", SDL_GetError());
        return font;
    }
    
    return font;
}

SDL_Window* CreateWindow(char* text, int x, int y)
{
    SDL_Window* window;
    window = SDL_CreateWindow(text, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_HIDDEN);
    if ( window < 0 )
    {
        printf("Erreur lors de la création de la window %s: %s", text, SDL_GetError());
        return window;
    }
    
    return window;
}

SDL_Window* CreateMainWindow(char* text, int x, int y)
{
    SDL_Window* window;
    window = SDL_CreateWindow(text, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_RESIZABLE);
    
    if ( window < 0 )
    {
        printf("Erreur lors de la création de la window %s: %s", text, SDL_GetError());
        return window;
    }
    
    return window;
}

SDL_Renderer* CreateRenderer( SDL_Window* window){
    SDL_Renderer* renderer;
    
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    
    if ( renderer < 0 )
    {
        printf("Erreur lors de la création du renderer : %s", SDL_GetError());
        return renderer;
    }
    return renderer;
}

SDL_Texture* CreateSolidTexture(TTF_Font* font, SDL_Color textColor, char* text, SDL_Renderer* renderer, int* space){
    int w;
    int h;
    SDL_Texture* solidTexture;
    SDL_Rect solidRect;
    
    w = h = 0;
    solidRect = CreateSolid_Rect(space[0], space[1], space[2], space[3]);
    SDL_Surface* solid = TTF_RenderText_Solid(font, text, textColor);
    solidTexture = SurfaceToTexture(solid, renderer);
    
    SDL_QueryTexture( solidTexture, NULL, NULL, &solidRect.w, &solidRect.h );
    return solidTexture;
}

SDL_Rect CreateSolid_Rect(int x, int y, int w, int h){
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = w;
    return rect;
}

SDL_Texture* SurfaceToTexture( SDL_Surface* surf, SDL_Renderer* renderer)
{
    SDL_Texture* texture;
    
    texture = SDL_CreateTextureFromSurface(renderer, surf);
    
    SDL_FreeSurface(surf);
    
    return texture;
}

void load_images(t_game *game){
    
    game->img_texture[10] = IMG_Load(TILESET);
    game->img_texture[0] = IMG_Load(Tile_0);
    game->img_texture[1] = IMG_Load(Tile_1);
    game->img_texture[2] = IMG_Load(Tile_2);
    game->img_texture[3] = IMG_Load(Tile_3);
    game->img_texture[4] = IMG_Load(Tile_4);
    game->img_texture[5] = IMG_Load(Tile_5);
    game->img_texture[6] = IMG_Load(Tile_6);
    game->img_texture[7] = IMG_Load(Tile_7);
    game->img_texture[8] = IMG_Load(Tile_8);
    game->img_texture[9] = IMG_Load(TILESET_BONUS);
    game->img_texture[11] = IMG_Load(PERSO);
    
}
