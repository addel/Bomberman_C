//
//  main.c
//  Bomberman
//
//  Created by agbo anthony on 15/06/2016.
//  Copyright (c) 2016 agbo anthony. All rights reserved.
//

#include "client.h"

pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

char *NETWORK = "";

int main(int argc, const char * argv[]) {    
    //initialisation des variables3
    SDL_Window* window;
    SDL_Window* window_ip;
    SDL_Event event;
    SDL_Renderer* renderer;
    SDL_Renderer* main_menu;
    SDL_Renderer* menu_ip;
    char *text;
    
    //demarage SDL
    setup_SDL();
    //création des windows
    window_ip = CreateWindow("Network", 500, 500);
    window = CreateMainWindow("Bomberman", 500, 500);
    //Création des screen
    main_menu = Create_menu_render(window);
    menu_ip = Create_menu_ip_render(window_ip);
    Main_menu(window, window_ip, main_menu, menu_ip);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
