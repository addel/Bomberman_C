/*
** prohibit_client.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Sun Aug 14 13:47:20 2016 LE Jean
** Last update Thu Aug 25 16:57:39 2016 LE Jean
*/

#include <server.h>

void	prohibit_client(int fd_socket, fd_set *readfds)
{
  int   prohibit_fd;
  socklen_t             sock_len;
  struct sockaddr_in    sock_client;

  if (FD_ISSET(fd_socket, readfds))
    {
      prohibit_fd = accept(fd_socket, (struct sockaddr*)&sock_client, &sock_len);
      write(prohibit_fd, "SERVER'S FULL, please retry later\n", 35);
      close(prohibit_fd);
    }
}

int	win_or_lose(t_clients *clients, int player_id)
{
  int	i;

  for (i = 0; i < 4; i++)
    if ((clients[i].fd != player_id + 3) && (clients[i].fd != 0))
      clients_signal(clients[i].fd, player_id, 7, "DIE\n");
  if (my_close_sock(player_id + 3) == -1)
    return (-1);
  clients[player_id - 1].fd= 0;
  clients->done = clients->done + 1;
  if (clients->done == 3)
    for (i = 0; i < 4; i++)
      if (clients[i].fd != 0)
	if (write(clients[i].fd, "WIN\n", 5) == -1)
	  return (-1);
  return (0);
}
