/*
** init_server.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Thu Jun  2 11:42:32 2016 LE Jean
** Last update Sat Aug 27 16:20:10 2016 SIBA Anais
*/

#include <server.h>

int     server_main(int fd_socket, t_clients *clients)
{
  if (wait_client(fd_socket, &clients) == -1)
    return (-1);
  my_putstr("Players connected !\n\n", 0);
  if (init_map(fd_socket, clients) == -1)
    return (-1);
  return (0);
}

int			init_serv(int fd_socket, int port)
{
  struct sockaddr_in	my_sockaddr;

  my_sockaddr.sin_family = AF_INET;
  my_sockaddr.sin_addr.s_addr = INADDR_ANY;
  my_sockaddr.sin_port = htons(port);
  if ((fd_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket()");
      return (-1);
    }
  if (bind(fd_socket, (struct sockaddr*) &my_sockaddr,
	   sizeof(my_sockaddr)) == -1)
    {
      perror("bind()");
      return (-1);
    }
  return (fd_socket);
}

int	wait_client(int fd_socket, t_clients **clients)
{
  int	i;
  char	p;
  char	buff[13];

  p = '1';
  my_memset(buff, 13);
  for (i = 0; i < 4; ++i)
    {
      if (((*clients)[i].fd = (client_connect(fd_socket))) == -1)
	return (-1);
      
      my_strcat(buff, &p);
      my_strcat(buff, " ID\n");

      if (write((*clients)[i].fd, buff, 13) == -1)
	return (-1);
      my_memset(buff, 13);
      p = p + 1;
    }
  return (0);
}

int			client_connect(int fd_socket)
{
  int			fd;
  socklen_t		sock_len;
  struct sockaddr_in	sock_client;

  fd = 0;
  sock_len = sizeof(sock_client);
  if (listen(fd_socket, 1) == -1)
    return (-1);
  my_putstr("Waiting a player...\n", 0);
  fd = accept(fd_socket, (struct sockaddr*)&sock_client, &sock_len);
  if (fd == -1)
    {
      perror("accept()");
      return (-1);
    }
  return (fd);
}
