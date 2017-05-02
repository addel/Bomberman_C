/*
** my_strcat.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette/libmy
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Sat Jun 25 18:08:35 2016 LE Jean
** Last update Sat Jun 25 18:09:04 2016 LE Jean
*/

char	*my_strcat(char *str1, char *str2)
{
  int	i;
  int	c;

  i = 0;
  c = 0;
  while (str1[i] != '\0')
    i = i + 1;
  while (str2[c] != '\0')
    {
      str1[i] = str2[c];
      c = c + 1;
      i = i + 1;
    }
  return (str1);
}
