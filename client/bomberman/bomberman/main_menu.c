//
//  menu.c
//  Bomberman
//
//  Created by agbo anthony on 23/08/2016.
//  Copyright (c) 2016 agbo anthony. All rights reserved.
//

#include "client.h"

SDL_Renderer* Create_menu_render(SDL_Window * window){
    
    TTF_Init();
    SDL_Renderer *render;
    int font_size = 100;
    char * text = "PRESS X";
    SDL_Color normalColor = {242, 19, 19};
    SDL_Rect Rect_dest;
    SDL_Surface* surface_background;
    SDL_Surface* surface_text;
    SDL_Texture* texture;
    SDL_Texture* texture_text;
    
    Rect_dest.x = 0;
    Rect_dest.y = 0;
    Rect_dest.w = 500;
    Rect_dest.h = 500;
    
    TTF_Font* police = TTF_OpenFont(FONT_MENU_PATH, font_size);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_RenderClear(render);
    //Ecriture des surfaces surfaces
    surface_background = SDL_LoadBMP(BACKGROUND_MENU_PATH);
    if ( !surface_background )
        fprintf(stdout,"Échec de chargement du background (%s)\n",SDL_GetError());
    
    surface_text = TTF_RenderText_Blended(police, text, normalColor);
    if ( !surface_text )
        fprintf(stdout,"Échec de chargement du texte (%s)\n",SDL_GetError());
    
    //Libère la mémoire utilisé par la police
    TTF_CloseFont(police);
    
    texture = SDL_CreateTextureFromSurface(render, surface_background);
    if ( !texture )
        fprintf(stdout,"Échec de création de la texture1 - %s\n",SDL_GetError());
    
    SDL_FreeSurface(surface_background);
    
    
    // on copy sur le render le background
    SDL_RenderCopy(render, texture, NULL, &Rect_dest);
    
    Rect_dest.x = 100;
    Rect_dest.y = 450;
    Rect_dest.w = 300;
    Rect_dest.h = 50;
    
    // on copy sur le render le background
    texture_text = SDL_CreateTextureFromSurface(render, surface_text);
    if ( !texture_text )
        fprintf(stdout,"Échec de création de la texture2 - %s\n",SDL_GetError());
    
    SDL_RenderCopy(render, texture_text, NULL, &Rect_dest);
    SDL_FreeSurface(surface_text);
    
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture_text);
    TTF_Quit();
    return render;
}

void Main_menu(SDL_Window *window, SDL_Window *window_ip, SDL_Renderer *main_menu, SDL_Renderer *menu_ip){

    SDL_Event event;
    SDL_bool done = SDL_TRUE;
    //SDL_RenderClear(menu_ip);
    SDL_RenderPresent(main_menu);
    SDL_HideWindow(window_ip);
    int menu_on;
    t_game game;
    
    //game
    /*pthread_t t_listenSrv;
    pthread_t t_askSrv;
    pthread_t th;*/
    
    NETWORK = malloc(500 * sizeof(char));
    
    game.window_ip = window_ip;
    game.main_window = window;
    game.menu_ip = menu_ip;
    game.sock = -1;
    game.main_menu = main_menu;
    game.render = menu_ip;
    /*pthread_join(t_listenSrv, NULL);
    pthread_join(t_askSrv, NULL);*/
    
    game.song = Play_song(0);
    //defini le menu afficher. 0:main;1:menu_ip
    menu_on = 0;
    
    while (done) {
        if (SDL_PollEvent(&event)) {
            SDL_RenderPresent(menu_ip);
            //SDL_RenderPresent(main_menu);
            switch (event.type) {
                case SDL_QUIT:
                    /* Quit */
                    done = SDL_FALSE;
                    break;
                case SDL_KEYDOWN :
                    switch (event.key.keysym.scancode) {
                            /* X preessed, start le menu IP */
                        case 27:
                            //on crée le menu_ip
                            if (menu_on != 1){
                                printf("lancement du menuIP\n");

                                SDL_HideWindow(window);
                                SDL_ShowWindow(window_ip);
                                //lancement du create enter ip
                                menu_on = 1;
                                //check_enterText(event, window, window_ip, NETWORK, menu_ip);
                                check_ip(event, game);
                            }
                            break;
                        case 28:
                            //pressY
                            if(menu_on != 0){
                                printf("retour au menu principal\n");
                                SDL_HideWindow(window_ip);
                                SDL_ShowWindow(window);
                                menu_on = 0;
                            }
                            break;
                        case 41:
                            /* Quit */
                            done = SDL_FALSE;
                            SDL_Quit();
                            break;
                    }
                    break;
            }
        }
    }
    Stop_song(game.song);
    free(NETWORK);
}

