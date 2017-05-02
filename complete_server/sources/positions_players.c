/*
** positions_players.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Wed Aug 10 13:27:12 2016 LE Jean
** Last update Wed Sep  7 22:49:28 2016 LE Jean
*/

#include <server.h>

int     new_position(t_map coord, t_clients *clients, char *buff,
		       int map[10][10], int trig)
{
  map[coord.y][coord.x] = 0;
  if (trig == 0)
    map[coord.new_move][coord.x] = clients->id - 3;
  else
    map[coord.y][coord.new_move] = clients->id - 3;
  return (send_info(clients, buff, 1));
}

int	up_flag(int map[10][10], int id)
{
  int	flag;
  int	i;
  int	j;

  flag = 0;
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
      if (map[i][j] == id)
	flag = 1;
  return (flag);
}

int	send_borm(t_clients *clients, int id, int borm, int pm)
{
  char	stock;
  char	a;
  char	buff[6];

  my_memset(buff, 6);
  a = (pm > 0) ? 'B' : 'M';
  if (borm == 9 || borm == 11)
    {
      clients[id].stock_bomb = clients[id].stock_bomb + pm;
      stock = clients[id].stock_bomb;
      sprintf(buff, "%cB %d\n", a, stock);
    }
  else
    {
      clients[id].power_bomb = clients[id].power_bomb + pm;
      stock = clients[id].power_bomb;
      sprintf(buff, "%cP %d\n", a, stock);
    }
  if (write(clients->id, buff, 6) == -1)
    return (-1);
  return (0);
}

int	verif_neg(t_clients *clients, int id, int p)
{
  if (p < 0)
    {
      if (clients[id].stock_bomb < 2)
	return (1);
      if (clients[id].power_bomb < 2)
	return (1);
    }
  return (0);
}

void	init_bomb(t_clients *clients)
{
  int	i;

  for (i = 0; i < 4; i++)
    {
      clients[i].stock_bomb = 1;
      clients[i].power_bomb = 1;
    }
}
