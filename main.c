/*
** main.c for main.c in /home/zellou_i/rendu/PSU_2013_myscript
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Fri Feb 21 21:30:29 2014 ilyas zelloufi
** Last update Fri Feb 21 23:05:01 2014 ilyas zelloufi
*/

#include "my_script.h"

t_struct		*my_init_struct(int ac, char **av)
{
  t_struct		*ptr;
  struct termios        old;

  if ((ptr = malloc(sizeof(t_struct))) == NULL)
    return (NULL);
  if (tcgetattr(0, &old) == -1)
    return (NULL);
  ptr->old = old;
  ptr->fd_name = check_file_name(ac, av);
  ptr->option = check_option(ac, av);
  return (ptr);
}

int			main(int ac, char **av)
{
  t_struct		*ptr;

  if ((ptr = my_init_struct(ac, av)) == NULL)
    return (-1);
  if (my_script(ptr) == -1)
    return (-1);
  return (0);
}
