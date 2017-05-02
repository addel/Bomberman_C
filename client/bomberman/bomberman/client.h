//
//  client.h
//  Bomberman
//
//  Created by agbo anthony on 15/06/2016.
//  Copyright (c) 2016 agbo anthony. All rights reserved.
//

#ifndef Bomberman_client_h
#define Bomberman_client_h

//#include "agbo.h"
#include "anais.h"
//Librairies
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

//global
extern char *NETWORK;

//Constante
#define	BUFFER 255

#define LARGEUR_TILE 900  // hauteur et largeur du tileset.
#define HAUTEUR_TILE 900
#define TILESET_SIZE 100
#define NOMBRE_BLOCS_LARGEUR 10  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 10
//#define THEME "/Users/anais/Projects/bomber/client/bomberman/bomberman"

//#define FONT_MENU_PATH "/System/Library/Fonts/Helvetica.dfont"
//#define BACKGROUND_MENU_PATH "/Users/anais/Projects/bomber/client/bomberman/bombermanbackground.bmp"
//#define BACKGROUND_MENU_IP_PATH "/Users/anais/Projects/bomber/client/bomberman/bombermanbackground_menu_ip.bmp"

//#define FONT_MENU_PATH "/System/Library/Fonts/Helvetica.dfont"
//#define BACKGROUND_MENU_PATH "/Users/anais/Projects/bomber/client/bomberman/bombermanbackground.bmp"
//#define BACKGROUND_MENU_IP_PATH "/Users/anais/Projects/bomber/client/bomberman/bombermanbackground_menu_ip.bmp"

/* Bomb's Structure */
typedef struct  s_bombs
{
    int		id;
    int     x;
    int     y;
    int		timer;
}               t_bombs;

/* Client's Structure */
typedef struct	s_clients
{
    int		fd;
    int		id;
    int     drop;
    int     wait;
    int		stock_bomb; // 1
    int		power_bomb; // porté de la bombe, 1
    int     xB;
    int     yB;
    int     bp;
    int		x;
    int		y;
}               t_clients;

/* Game's Structure */
typedef struct	s_game
{
    char        *port;
    char        *ip;
    int         sock;
    int         id;
    char        *msg;
    t_clients   clients[4];
    t_bombs     bombs[50];
    int         nbBomb;
    int         t_bomb_id;
    int         map[10][10];
    SDL_Renderer*   render;
    SDL_Renderer*   main_menu;
    SDL_Texture*    textures[10][10];
    //liste des images déja chargé dans une surface
    SDL_Surface*    img_texture[20];
    Mix_Music       *song;
    SDL_Renderer    *menu_ip;
    SDL_Window      *window_ip;
    SDL_Window      *main_window;
    struct sockaddr_in	server;
    
}               t_game;

/* Map's Structure */
typedef struct  s_map
{
    int     x;
    int		y;
    int		min;
    int		max;
    int		new_move;
}               t_map;

typedef struct  s_tile
{
    int		id;
    int     x;
    int     y;
    int		timer;
}   s_map;

typedef struct s_arg {
    int sock;
    char* msg;
}       t_arg;

//Fonctions

//fonctions de la partie client back
int setConnection(t_game *ag);
int	listenSrv(t_game *games);
void change_map(char *msg, int sock);
int talkSrv(t_game *games);
void cleanMsg(char msg[BUFFER]);

//fonctions de la map
void show_map(SDL_Renderer* render, t_game *game);
void init_map(t_game *game);
SDL_Texture* get_texture(int val, t_game *game);
//void explode_bomber(int id, t_game *game);
void explode_bomber(t_game *game);
char* get_filepath(int val);
SDL_Rect get_src_dest (int val);

//fonctions des clients
void init_client(t_clients *client, int x, int y);
void move_client(t_game *game, char* msg, int id);
void drop_client(t_game *game, int id, int x, int y);
void xory_client(t_game *game, char* msg, int id, int x, int y);
void die_client(t_game *game, int id);

// fonctions de lecture de musique et des sons
char* list_song(int track);
char* list_effect(int track);
Mix_Music* Play_song(int track);
Mix_Music* Play_effect(int track);
void Stop_song(Mix_Music *musique);

//fonctions de gestion des menus
SDL_Renderer* Create_menu_render(SDL_Window *window);
void Main_menu(SDL_Window *window, SDL_Window *window_ip, SDL_Renderer *main_menu, SDL_Renderer *menu_ip);
SDL_Renderer* Create_menu_ip_render(SDL_Window *window);
void Menu_ip(SDL_Window *window, SDL_Renderer *menu_ip);
SDL_Renderer* Update_menu_ip_render(SDL_Window *window, SDL_Renderer* menu_ip);

//fonctions de la partie get_ip
char* event_enterText();
void menu_ip(SDL_Event event, char* text);
char* convert_scancode(int scancode);
char* check_enterText(SDL_Event event, SDL_Window* window, SDL_Window* window_ip, char *text, SDL_Renderer* renderer_ip);
void check_ip (SDL_Event event, t_game game);
void split_ip(char *text, t_game *game);
char    *my_memset(char *s, int n);

// fonctions de setup.c
int setup_SDL();
TTF_Font* Create_font( char* name, int size);
SDL_Window* CreateMainWindow(char* text, int x, int y);
SDL_Window* CreateWindow(char* text, int x, int y);
SDL_Renderer* CreateRenderer(SDL_Window* window);
SDL_Texture* SurfaceToTexture( SDL_Surface* surf, SDL_Renderer* renderer);
SDL_Rect CreateSolid_Rect(int x, int y, int w, int h);
SDL_Texture* CreateSolidTexture(TTF_Font* font, SDL_Color textColor, char* text, SDL_Renderer* renderer, int * space);
void load_images(t_game *game);

// gestion action client
void map_event(SDL_Event event, t_game game);

//fonctions de update windows
void Update_IP_Windows(SDL_Renderer* renderer, char* text, SDL_Window* window);
void Update_Windows(SDL_Renderer* renderer, SDL_Window* window);

//fonction de la lib c
int	my_getnbr(char *str);

#endif
