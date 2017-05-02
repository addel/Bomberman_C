/*
** bombs.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette/sources
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Sun Jul 10 13:59:58 2016 LE Jean
** Last update Wed Sep  7 22:46:20 2016 LE Jean
*/

#include <server.h>

int	drop_bomb(t_clients *clients, char *buff, t_map *coord, t_bombs **bombs)
{
  int	i;
  int	inc;

  i = clients->nb_bomb;
  manage_bomb(clients);
  if (verif_fbomb(clients) != 0)
    return (0);
  for (inc = 0; inc < i; inc++)
    if (((*bombs)[inc].x == coord->x) && ((*bombs)[inc].y == coord->y))
      {
	if (write(clients->id, "KO\n", 3) == -1)
	  {
	    perror("write()");
	    return (-1);
	  }
	return (0);
      }
  (*bombs)[i].x = coord->x;
  (*bombs)[i].y = coord->y;
  if (send_info(clients, buff, 1) == -1)
    return (-1);
  clients->nb_bomb = clients->nb_bomb + 1;
  return (0);
}

int     verif_fbomb(t_clients *clients)
{
  if (clients[clients->id - 4].fbomb == 1)
    {
      if (write(clients->id, "KO\n", 3) == -1)
	{
	  perror("write()");
	  return (-1);
	}
      return (1);
    }
  return (0);
}

void	put_bomb_map(t_clients *clients, int map[10][10], t_bombs **bombs)
{
  int	i;
  int	j;
  int	k;

  for (k = 0; k < clients->nb_bomb; k++)
    if ((*bombs)[k].y != 11 && (*bombs)[k].x != 11)
      {
	i = (*bombs)[k].y;
	j = (*bombs)[k].x;
	if (map[i][j] == 0)
	  map[i][j] = 6;
      }
}

int	explode_bomb(t_clients *clients, t_bombs *bombs,
		     int map[10][10])
{
  map_pw(bombs, map, bombs->to_explode, clients[clients->id - 4].power_bomb);
  map_bm(clients, bombs, bombs->to_explode, map);
  bombs[bombs->to_explode].y = 11;
  bombs[bombs->to_explode].x = 11;
  clients[clients->id - 4].fbomb = 0;
  clients[clients->id - 4].stock_bomb += 1;
  display_map(map);
  if (send_info(clients, "EXPLODE\n", 1) == -1)
    return (-1);
  verif_players(clients, map);
  bombs->to_explode = bombs->to_explode + 1;
  return (0);
}

int	verif_players(t_clients *clients, int map[10][10])
{
  int	id;

  for (id = 1; id < 5; id++)
    if (up_flag(map, id) < 1)
      if (clients[id - 1].fd != 0)
	  if (win_or_lose(clients, id) == -1)
	    return (-1);
  return (0);
}
