/*
** bonus_malus.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Tue Aug  9 13:45:05 2016 LE Jean
** Last update Sat Sep  3 15:41:17 2016 LE Jean
*/

#include <server.h>

int	bonus_malus(t_clients *clients, int borm, int id)
{
  if (borm == 9 || borm == 10)
    {
      if (send_borm(clients, id, borm, 1) == -1)
	return (-1);
    }
  else if (borm == 11 || borm == 12)
    {
      if (verif_neg(clients, id, -1) == 1)
	return (0);
      if (send_borm(clients, id, borm, -1) == -1)
	return (-1);
    }
  return (0);
}

int	my_random(t_clients *clients, int x, int y)
{
  int	i;
  float nb;
  char	buff[8];

  nb = 0;
  my_memset(buff, 8);
  srand(time(NULL));
  nb = rand() % (3 - 0) + 0;
  nb = nb + 9;
  if (nb == 9)
    sprintf(buff, "BB %d;%d\n", x, y);
  else if (nb == 10)
    sprintf(buff, "BP %d;%d\n", x, y);
  else if (nb == 11)
    sprintf(buff, "MB %d;%d\n", x, y);
  else if (nb == 12)
    sprintf(buff, "MP %d;%d\n", x, y);
  for (i = 0; i < 4; i++)
    if (clients[i].fd != 0)
      write(clients[i].fd, buff, 8);
  return (nb);
}

void	manage_bomb(t_clients *clients)
{
  if (clients[clients->id - 4].stock_bomb == 0)
    clients[clients->id - 4].fbomb = 1;
  else
    {
      clients[clients->id - 4].fbomb = 0;
      clients[clients->id - 4].stock_bomb -= 1;
    }
}

void	map_bm(t_clients *clients, t_bombs *bombs, int cible,
	       int map[10][10])
{
  int	x;
  int	y;

  x = bombs[cible].x;
  y = bombs[cible].y;
  if (map[y][x] == 8)
    map[y][x] = my_random(clients, x, y);
  if (y - 1 >= 0)
    if (map[y - 1][x] == 8)
      map[y - 1][x] = my_random(clients, x, y - 1);
  if (y + 1 <= 9)
    if (map[y + 1][x] == 8)
      map[y + 1][x] = my_random(clients, x, y + 1);
  if (x - 1 >= 0)
    if (map[y][x - 1] == 8)
      map[y][x - 1] = my_random(clients, x - 1, y);
  if (x + 1 <= 9)
    if (map[y][x + 1] == 8)
      map[y][x + 1] = my_random(clients, x + 1, y);
}

void	map_pw(t_bombs *bombs, int map[10][10], int cible, int pw)
{
  int   i;

  for (i = 1; i <= pw; i++)
    {
      if (map[bombs[cible].y][bombs[cible].x] != 7
	  && map[bombs[cible].y][bombs[cible].x] != 8)
	map[bombs[cible].y][bombs[cible].x] = 0;
      if (bombs[cible].y - i >= 0)
	if (map[bombs[cible].y - i][bombs[cible].x] != 7
	    && map[bombs[cible].y - i][bombs[cible].x] != 8)
	  map[bombs[cible].y - i][bombs[cible].x] = 0;
      if (bombs[cible].y + i <= 9)
	if (map[bombs[cible].y + i][bombs[cible].x] != 7
	    && map[bombs[cible].y + i][bombs[cible].x] != 8)
	  map[bombs[cible].y + i][bombs[cible].x] = 0;
      if (bombs[cible].x - i >= 0)
	if (map[bombs[cible].y][bombs[cible].x - i] != 7
	    && map[bombs[cible].y][bombs[cible].x - i] != 8)
	  map[bombs[cible].y][bombs[cible].x - i] = 0;
      if (bombs[cible].x + i <= 9)
	if (map[bombs[cible].y][bombs[cible].x + i] != 7
	    && map[bombs[cible].y][bombs[cible].x + i] != 8)
	  map[bombs[cible].y][bombs[cible].x + i] = 0;
    }
}
