/*
** protocol.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Wed Jun 22 16:05:12 2016 LE Jean
** Last update Wed Sep  7 22:44:26 2016 LE Jean
*/

#include <server.h>

int     commands(char *buff, t_clients *clients, int map[10][10], t_bombs *bombs)
{
  t_map coord;
  int   ret;

  ret = 0;
  coord.x = 0;
  coord.y = 0;
  init_coord(clients->id, buff, &coord, map);
  if ((my_strcmp(buff, "UP\n") == 0)
      || (my_strcmp(buff, "DOWN\n") == 0)) 
    ret = move_xory(coord, clients, buff, map, 0);
  else if ((my_strcmp(buff, "LEFT\n") == 0)
	   || (my_strcmp(buff, "RIGHT\n") == 0))
    ret = move_xory(coord, clients, buff, map, 1);
  else if (my_strcmp(buff, "DROP\n") == 0)
    ret = drop_bomb(clients, buff, &coord, &bombs);
  else if (my_strcmp(buff, "EXPLODE\n") == 0)
    ret = explode_bomb(clients, bombs, map);
  else
    ret = write(clients->id, "KO\n", 3);
  put_bomb_map(clients, map, &bombs);
  display_map(map);
  return (ret);
}

void	init_coord(int client, char *buff, t_map *coord, int map[10][10])
{
  find_player(coord, client, map);
  if (my_strcmp(buff, "UP\n") == 0 || my_strcmp(buff, "LEFT\n") == 0)
    {
      coord->min = 0;
      coord->max = 10;
      if (my_strcmp(buff, "UP\n") == 0)
	coord->new_move = coord->y - 1;
      else
	coord->new_move = coord->x - 1;
    }
  else
    {
      coord->min = -1;
      coord->max = 9;
      if (my_strcmp(buff, "DOWN\n") == 0)
	coord->new_move = coord->y + 1;
      else
	coord->new_move = coord->x + 1;
    }
}

int     player_dies(t_clients *clients, int player_id, int map[10][10])
{
  int   i;
  int   j;

  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
      if (map[i][j] == player_id)
	map[i][j] = 0;
  if (win_or_lose(clients, player_id) == -1)
    return (-1);
  return (0);
}

int	clients_signal(int client, int id, int len, char *buff)
{
  char	c[len];

  my_memset(c, len);
  sprintf(c, "%d ", id);
  my_strcat(c, buff);
  if (write(client, c, len) == -1)
    {
      perror("write()");
      return (-1);
    }
  my_memset(c, len);
  return (0);
}

int	send_info(t_clients *clients, char *buff, int flag)
{
  int	i;

  if (flag == 1)
    if (write(clients->id, "OK\n", 3) == -1)
      {
	perror("write()");
	return (-1);
      }
  for (i = 0; i < 4; i++)
    if ((clients[i].fd != clients->id) && (clients[i].fd != 0))
      if (clients_signal(clients[i].fd, clients->id - 3, 10, buff) == -1)
	return (-1);
  return (0);
}
