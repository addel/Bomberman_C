/*
** my_getnbr.c for my_getnbr in /home/siba_a/sem02/libmy/file_o
** 
** Made by SIBA Anais
** Login   <siba_a@etna-alternance.net>
** 
** Started on  Fri Oct 24 10:29:05 2014 SIBA Anais
** Last update Wed Oct 29 12:20:52 2014 SIBA Anais
*/
void	my_putchar(char c);

int	is_neg(char *str)
{
  int	i;
  int	count;

  i = 0;
  count = 0;
  while (str[i] > '9' || str[i] < '0')
    {
      if (str[i] == '-')
        count = count + 1;
      i = i + 1;
    }
  if ((count % 2) != 0)
    return (1);
  return (0);
}

int	is_int(char c)
{
  if (c >= '0' && c <= '9')
    return (1);
  return (0);
}

int	my_getnbr(char *str)
{
  int	i;
  int	res;

  i = 0;
  res = 0;
  if(str[0] != '-' && str[0] != '+' && (str[0] > '9' || str[0] < '0'))
    return (0);
  while (is_int(str[i]) == 0)
      i = i + 1;

  while (is_int(str[i]) == 1)
    {
      res = ((res * 10) + (str[i] - '0'));
      i = i + 1;
    }
  if (is_neg(str) == 1)
    return (-res);
  return (res);
}
