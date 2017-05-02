//
//  client.c
//  bomberXcode
//
//  Created by Anais on 02/09/2016.
//  Copyright © 2016 siba_a. All rights reserved.
//

#include "client.h"

void init_client(t_clients *client, int x, int y)
{
    client->x = x;
    client->y = y;
    client->bp = 1;
    client->wait = 0;
    client->drop = 0;
}

void die_client(t_game *game, int id)
{
    int			x;
    int			y;
    
    x = game->clients[id].x / 50;
    y = game->clients[id].y / 50;
    
    game->clients[id].y = 0;
    game->clients[id].x = 0;
    game->textures[y][x] = get_texture(0, game);
    game->map[y][x] = 0;
}

void move_client(t_game *game, char* msg, int id)
{
    int			x;
    int			y;
    SDL_Texture* BlueShapes;
    
    BlueShapes = NULL;
    x = game->clients[id].x / 50;
    y = game->clients[id].y / 50;
    
    if (game->clients[id].drop == 1)
        drop_client(game, id, x, y);
    else
    {
        game->map[y][x] = 0;
        game->textures[game->clients[id].y / 50][game->clients[id].x / 50] = game->textures[y][x];
        game->textures[y][x] = get_texture(0, game);
    }
    xory_client(game, msg, id, x, y);
    game->map[game->clients[id].y / 50][game->clients[id].x / 50] = id + 1;
}

void xory_client(t_game *game, char* msg, int id, int x, int y)
{
    int change;
    
    change = 0;    
    if (strcmp(msg, "UP\n") == 0)
    {
        game->clients[id].y = (y - 1) * 50;
        change = 1;
    }
    else if (strcmp(msg, "DOWN\n") == 0)
    {
        game->clients[id].y = (y + 1) * 50;
        change = 1;
    }
    else if (strcmp(msg, "RIGHT\n") == 0)
    {
        game->clients[id].x = (x + 1) * 50;
        change = 1;
    }
    else if (strcmp(msg, "LEFT\n") == 0)
    {
        game->clients[id].x = (x - 1) * 50;
        change = 1;
    }
    
    if (change == 1)
        game->textures[game->clients[id].y / 50][game->clients[id].x / 50] = get_texture(id + 1, game);
}

void drop_client(t_game *game, int id, int x, int y)
{
    game->clients[id].drop = 0;
    game->clients[id].wait = 1;
    game->clients[id].xB = x;
    game->clients[id].yB = y;
    game->map[y][x] = 6;
    game->textures[y][x] = get_texture(6, game);
}