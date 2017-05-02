//
//  init_client.c
//  Bomberman
//
//  Created by agbo anthony on 15/06/2016.
//  Copyright (c) 2016 agbo anthony. All rights reserved.
//

#include "client.h"

char    *my_memset(char *s, int n)
{
    int   i;
    
    for (i = 0; i < n; ++i)
        s[i] = '\0';
    return (s);
}

// Fonctions pour recuperer une IP et Port tapé au clavier
void check_ip (SDL_Event event, t_game game){

    pthread_t t_listenSrv;
    pthread_t t_askSrv;
    pthread_t th;
    
    game.sock = -1;
    
    load_images(&game);
    
    pthread_join(t_listenSrv, NULL);
    pthread_join(t_askSrv, NULL);

    
    //SDL_Event event;
    SDL_bool done;
    
    done = SDL_TRUE;
    
    while (done) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    /* Quit */
                    done = SDL_FALSE;
                    break;
                case SDL_KEYDOWN :
                    switch (event.key.keysym.scancode) {
                        case 41:
                            /* Quit */
                            done = SDL_FALSE;
                            SDL_Quit();
                            break;
                        case 28 :
                            done = SDL_FALSE;
                            free(NETWORK);
                            NETWORK = malloc(500 * sizeof(char));
                            break;
                        case (55):
                            if (strlen(NETWORK) == 0)
                                strcpy(NETWORK, convert_scancode(event.key.keysym.scancode));
                            else
                                strcat(NETWORK, convert_scancode(event.key.keysym.scancode));
                            break;
                        case (44):
                            if (game.sock < 0) {
                                if (strlen(NETWORK) == 0)
                                    strcpy(NETWORK, convert_scancode(event.key.keysym.scancode));
                                else
                                    strcat(NETWORK, convert_scancode(event.key.keysym.scancode));
                                Update_menu_ip_render(game.window_ip, game.menu_ip);
                            } else {
                                game.msg = "DROP\n";
                                talkSrv(&game);
                            }
                            break;
                        case (42):
                            NETWORK[strlen(NETWORK) - 1] = '\0';
                            Update_menu_ip_render(game.window_ip, game.menu_ip);
                            break;
                        case (26):
                            printf(" game.sock = %d \n", game.sock);
                            if (game.sock > 0) {
                                game.msg = "UP\n";
                                talkSrv(&game);
                            }
                            break;
                        case (7):
                            if (game.sock != 0) {
                                game.msg = "RIGHT\n";
                                talkSrv(&game);
                            }
                            break;
                        case (4):
                            if (game.sock != 0) {
                                game.msg = "LEFT\n";
                                talkSrv(&game);
                            }
                            break;
                        case (22):
                            if (game.sock != 0) {
                                game.msg = "DOWN\n";
                                talkSrv(&game);
                            }
                            break;

                        case (40):

                            split_ip(NETWORK, &game);
                            
                            if (game.port && game.ip) {
                                printf("ip %s - port %s\n", game.ip, game.port);
                                if (setConnection(&game) > 0) {
                                    Stop_song(game.song);
                                    game.song = Play_song(2);
                                    show_map(game.menu_ip, &game);
                                    pthread_create(&th, NULL, listenSrv, &game);
                                    
                                }
                                else {
                                    free(NETWORK);
                                    NETWORK = malloc(500 * sizeof(char));
                                }
                            }
                            break;
                        default:
                            if ((event.key.keysym.scancode >= 30 ) && (event.key.keysym.scancode <= 39)){
                                if (strlen(NETWORK) == 0){
                                    strcpy(NETWORK,convert_scancode(event.key.keysym.scancode));
                                }
                                else{
                                    strcat(NETWORK, convert_scancode(event.key.keysym.scancode));
                                }
                                Update_menu_ip_render(game.window_ip, game.menu_ip);
                            }
                            break;
                    }
                    break;
            }
        }
    }
}

void split_ip(char *text, t_game *game){

    const char s[2] = " ";
    char *token;
    char port[200];
    int n;
    char ip[200];
    game->ip= malloc(sizeof(char)* 120);
    game->port= malloc(sizeof(char)* 120);
    /* get the first token */
    
    token = strtok(text, " ");
    printf("%s\n", game->ip);
    printf("%s\n", game->port);
    my_memset(ip, 200);
    my_memset(port, 200);
    
    for( n = 0; token != NULL; n++)
    {
        if (n < 4)
        {
            strcat(ip, token);
            strcat(ip, ".");
        } else {
            strcat(port, token);
        }
        token = strtok(NULL, " ");
    }

    ip[strlen(ip) - 1] = '\0';

    strcpy(game->ip, ip);
    strcpy(game->port, port);

    printf("le port : %s \n", game->port);
    printf("l'ip : %s \n", game->ip);
};

char* convert_scancode(int scancode){
    switch (scancode) {
        case 30:
            return "1";
            break;
        case 31:
            return "2";
            break;
        case 32:
            return "3";
            break;
        case 33:
            return "4";
            break;
        case 34:
            return "5";
            break;
        case 35:
            return "6";
            break;
        case 36:
            return "7";
            break;
        case 37:
            return "8";
            break;
        case 38:
            return "9";
            break;
        case 39:
            return "0";
            break;
        case 44:
            return " ";
            break;
        default:
            return "";
            break;
    }
};
