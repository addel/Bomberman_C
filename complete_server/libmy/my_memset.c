/*
** my_memset.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Thu Jun  2 12:09:27 2016 LE Jean
** Last update Thu Jun  2 12:19:16 2016 LE Jean
*/

char    *my_memset(char *s, int n)
{
  int   i;

  for (i = 0; i < n; ++i)
    s[i] = '\0';
  return (s);
}
