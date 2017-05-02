/*
** start_coms.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Thu Jun  2 11:50:17 2016 LE Jean
** Last update Thu Aug 25 16:58:59 2016 LE Jean
*/

#include <server.h>

int			start_coms(int fd_socket, t_clients *clients,
				   int map[10][10], t_bombs *bombs)
{
  fd_set		readfds;
  int			err;
  int			hfd;

  err = 0;
  hfd = clients[3].fd + 1;
  clients->done = 0;
  bombs->to_explode = 0;
  while (err != -1 && err != -21)
    {
      init_fd_set(fd_socket, &readfds, clients);
      if ((err = my_select(&readfds, hfd)) != -1)
	{
	  if ((err = manage(&readfds, clients, map, bombs, fd_socket)) == -1)
	    return (-1);
	}
      else
	return (-1);
    }
  free(bombs);
  if (server_main(fd_socket, clients) == -1)
    return (-1);
  return (0);
}

void    init_fd_set(int fd_socket, fd_set *readfds, t_clients *clients)
{
  int   i;

  FD_ZERO(readfds);
  for (i = 0; i < 4; ++i)
    {
      if (clients[i].fd != 0)
	FD_SET(clients[i].fd, readfds);
    }
  FD_SET(fd_socket, readfds);
}

int			my_select(fd_set *readfds, int n)
{
  int			ret_sel;

  ret_sel = select(n, readfds, NULL, NULL, NULL);
  if (ret_sel < 0)
    {
      perror("select()");
      return (-1);
    }
  return (0);
}

int	manage(fd_set *readfds, t_clients *clients, int map[10][10],
	       t_bombs *bombs, int fd_socket)
{
  char	buff[16];
  int	i;

  prohibit_client(fd_socket, readfds);
  for (i = 0; i < 4; ++i)
    if (clients[i].fd != 0)
      if (FD_ISSET(clients[i].fd, readfds))
	{
	  my_memset(buff, 16);
	  if (read(clients[i].fd, buff, 16) <= 0)
	    {
	      if (player_dies(clients, i + 1, map) == -1)
		return (-1);
	    }
	  else
	    {
	      clients->id = clients[i].fd;
	      if (commands(buff, clients, map, bombs) == -1)
		return (-1);
	    }
	}
  for (i = 0; i < 4; i++)
    if (clients[i].fd != 0)
      return (0);
  return (-21);
}
