/*
** exit_server.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Thu Jun  2 12:04:10 2016 LE Jean
** Last update Sat Jun 25 18:18:00 2016 LE Jean
*/

#include <server.h>

int	my_close_sock(int client)
{
  int   err_cl;

  err_cl = 0;
  if (client != 0)
    err_cl = close(client);
  if (err_cl == -1)
    {
      perror("close()");
      return (err_cl);
    }
  return (err_cl);
}
