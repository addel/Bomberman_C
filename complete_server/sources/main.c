/*
** main.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Thu Jun  2 11:38:49 2016 LE Jean
** Last update Wed Jul 13 12:57:11 2016 LE Jean
*/

#include  <server.h>

int		main()
{
  int		fd_socket;
  t_clients	*clients;
  int		port;
  int		rc;

  port = 4242;
  fd_socket = 0;
  if ((clients = malloc(4*sizeof(t_clients))) == NULL)
    {
      perror("malloc()");
      return (-1);
    }
  if ((fd_socket = init_serv(fd_socket, port)) == -1)
    return (-1);
  rc = server_main(fd_socket, clients);
  free(clients);
  return (rc);
}
