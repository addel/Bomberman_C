//
//  menu_ip.c
//  Bomberman
//
//  Created by agbo anthony on 24/08/2016.
//  Copyright (c) 2016 agbo anthony. All rights reserved.
//

#include "client.h"

SDL_Renderer* Create_menu_ip_render(SDL_Window *window){
    TTF_Init();
    SDL_Renderer* menu_ip;
    int font_size = 24;
    char *pressY;
    char *acceuil;
    SDL_Color normalColor = {250, 0, 0};
    SDL_Rect Rect_dest;
    SDL_Surface* surface_background;
    SDL_Surface* surface_acceuil;
    SDL_Surface* surface_pressY;
    SDL_Texture* main_texture;
    SDL_Texture* texture_acceuil;
    SDL_Texture* texture_pressY;
    
    Rect_dest.x = 0;
    Rect_dest.y = 0;
    Rect_dest.w = 500;
    Rect_dest.h = 500;
    
    pressY = malloc(500 * sizeof(char));
    acceuil = malloc(500 * sizeof(char));
    
    acceuil = "ENTER AN @IP And @PORT (X X X X @port)";
    pressY = "Press Y for Quit";
    TTF_Font* police = TTF_OpenFont(FONT_MENU_PATH, font_size);
    menu_ip = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        
    //Ecriture des surfaces
    surface_background = SDL_LoadBMP(BACKGROUND_MENU_IP_PATH);
    if ( !surface_background )
        fprintf(stdout,"Échec de chargement du background (%s)\n",SDL_GetError());
    
    surface_acceuil = TTF_RenderText_Blended(police, acceuil, normalColor);
    if ( !surface_acceuil )
        fprintf(stdout,"Échec de chargement du texte (%s)\n",SDL_GetError());
    
    surface_pressY = TTF_RenderText_Blended(police, pressY, normalColor);
    if ( !surface_pressY )
        fprintf(stdout,"Échec de chargement du texte (%s)\n",SDL_GetError());
    
    TTF_CloseFont(police);
    
    main_texture = SDL_CreateTextureFromSurface(menu_ip, surface_background);
    SDL_FreeSurface(surface_background);
    SDL_RenderCopy(menu_ip, main_texture, NULL, &Rect_dest);
    
    //free(pressY);
    //free(acceuil);
    
    Rect_dest.x = 0;
    Rect_dest.y = 150;
    Rect_dest.w = 500;
    Rect_dest.h = 30;
    texture_acceuil = SDL_CreateTextureFromSurface(menu_ip, surface_acceuil);
    SDL_FreeSurface(surface_acceuil);
    SDL_RenderCopy(menu_ip, texture_acceuil, NULL, &Rect_dest);
    
    Rect_dest.x = 100;
    Rect_dest.y = 450;
    Rect_dest.w = 250;
    Rect_dest.h = 30;
    texture_pressY = SDL_CreateTextureFromSurface(menu_ip, surface_pressY);
    SDL_FreeSurface(surface_pressY);
    SDL_RenderCopy(menu_ip, texture_pressY, NULL, &Rect_dest);
    SDL_RenderPresent(menu_ip);
    TTF_Quit();
    return menu_ip;
    
}

SDL_Renderer* Update_menu_ip_render(SDL_Window *window, SDL_Renderer* menu_ip){
    SDL_RenderClear(menu_ip);
    TTF_Init();
    //SDL_Renderer* menu_ip;
    int font_size = 32;
    char *pressY;
    SDL_Color normalColor = {250, 0, 0};
    SDL_Rect Rect_dest;
    SDL_Surface* surface_background;
    SDL_Surface* surface_acceuil;
    SDL_Surface* surface_pressY;
    SDL_Texture* main_texture;
    SDL_Texture* texture_acceuil;
    SDL_Texture* texture_pressY;
    
    Rect_dest.x = 0;
    Rect_dest.y = 0;
    Rect_dest.w = 500;
    Rect_dest.h = 500;
    
    pressY = malloc(500 * sizeof(char));
    
    //if (strlen(NETWORK) <= 0){
      //  strcat(NETWORK, text);
    pressY = "Press Y for Quit";
    TTF_Font* police = TTF_OpenFont(FONT_MENU_PATH, font_size);
    //menu_ip = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    //Ecriture des surfaces
    surface_background = SDL_LoadBMP(BACKGROUND_MENU_IP_PATH);
    if ( !surface_background )
        fprintf(stdout,"Échec de chargement du background (%s)\n",SDL_GetError());
    
    surface_acceuil = TTF_RenderText_Blended(police, NETWORK, normalColor);
    if ( !surface_acceuil )
        fprintf(stdout,"Échec de chargement du texte (%s)\n",SDL_GetError());
    
    surface_pressY = TTF_RenderText_Blended(police, pressY, normalColor);
    if ( !surface_pressY )
        fprintf(stdout,"Échec de chargement du texte (%s)\n",SDL_GetError());
    
    TTF_CloseFont(police);
    
    main_texture = SDL_CreateTextureFromSurface(menu_ip, surface_background);
    SDL_FreeSurface(surface_background);
    SDL_RenderCopy(menu_ip, main_texture, NULL, &Rect_dest);
    
    //free(pressY);
    //free(acceuil);
    
    Rect_dest.x = 100;
    Rect_dest.y = 150;
    Rect_dest.w = 250;
    Rect_dest.h = 50;
    texture_acceuil = SDL_CreateTextureFromSurface(menu_ip, surface_acceuil);
    SDL_FreeSurface(surface_acceuil);
    SDL_RenderCopy(menu_ip, texture_acceuil, NULL, &Rect_dest);
    
    Rect_dest.x = 100;
    Rect_dest.y = 450;
    Rect_dest.w = 250;
    Rect_dest.h = 30;
    texture_pressY = SDL_CreateTextureFromSurface(menu_ip, surface_pressY);
    SDL_FreeSurface(surface_pressY);
    SDL_RenderCopy(menu_ip, texture_pressY, NULL, &Rect_dest);
    SDL_RenderPresent(menu_ip);
    TTF_Quit();
    return menu_ip;
    

    
}