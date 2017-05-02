/*
** my_strcmp.c for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
** 
** Made by LE Jean
** Login   <le_j@etna-alternance.net>
** 
** Started on  Thu Jun  2 12:19:30 2016 LE Jean
** Last update Mon Jun  6 17:45:38 2016 LE Jean
*/

int	my_strcmp(char *str1, char *str2)
{
  int	i;

  if (str1 && str2)
    {
      for (i = 0; str1[i] && str2[i] && str1[i] == str2[i]; i++);
      if (str1[i] == '\0' && str2[i] == '\0')
	return (0);
      else if (str1[i] == '\0' || str1[i] < str2[i])
	return (-1);
      else
	return (1);
    }
  else
    return (0);
}
