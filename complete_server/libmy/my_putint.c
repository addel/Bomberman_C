/*
** my_putint.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Thu Jun  2 12:17:40 2016 LE Jean
** Last update Sat Jun 11 12:16:37 2016 LE Jean
*/

#include <unistd.h>

void	my_putint(int nb, int fd)
{
  char	res;
  int	div;

  div = 1;
  if (nb == (-2147483648))
    write(fd, "-2147483648", 11);
  else
    {
      if (nb < 0)
	{
	  write(fd, "-", 1);
	  nb = -nb;
	}
      while ((nb / div) >= 10)
	div = div * 10;
      while (div > 0)
	{
	  res = '0' + (nb / div) % 10;
	  write(fd, &res, 1);
	  div = div / 10;
	}
    }
}
