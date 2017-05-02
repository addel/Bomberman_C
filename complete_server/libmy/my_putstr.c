/*
** my_putstr.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Thu Jun  2 12:07:56 2016 LE Jean
** Last update Sat Jun 11 12:16:18 2016 LE Jean
*/

#include <unistd.h>

void	my_putstr(char *str, int fd)
{
  int	i;

  for (i = 0; str[i]; i++);
  write(fd, str, i);
}
