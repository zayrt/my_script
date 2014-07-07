/*
** check_params.c for check_params in /home/zellou_i/rendu/PSU_2013_myscript
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Fri Feb 21 11:28:09 2014 ilyas zelloufi
** Last update Fri Feb 28 01:17:20 2014 ilyas zelloufi
*/

#include "my_script.h"

char			*check_file_name(int ac, char **av)
{
  int			i;

  i = 1;
  while (i < ac)
    {
      if (av[i][0] != '-' && av[i][0])
	return (av[i]);
      i++;
    }
  return (NULL);
}

int			check_option(int ac, char **av)
{
  int			i;

  i = 1;
  while (i < ac)
    {
      if (strcmp(av[i], "-a") == 0)
	return (0);
      i++;
    }
  return (-1);
}

t_struct		*my_handle_params(t_struct *ptr)
{
  int			fd;

  if (ptr->fd_name != NULL && ptr->option == 0)
    {
      if ((fd = open(ptr->fd_name, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
	return (NULL);
    }
  else if (ptr->option == 0)
    {
      if ((fd = open("typescript", O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
	return (NULL);
    }
  else if (ptr->fd_name != NULL)
    {
      if ((fd = open(ptr->fd_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	return (NULL);
    }
  else
    if ((fd = open("typescript", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
      return (NULL);
  ptr->fd = fd;
  return (ptr);
}

int			write_time(int *fd)
{
  char			format[128];
  time_t		temps;
  struct tm		date;
  int			len;

  if (time(&temps) == -1)
    return (-1);
  date = *localtime(&temps);
  len = strftime(format, 128, " %a %d %b %Y %0l:%M:%S %p %Z\n", &date);
  if (len != 0)
    write(*fd, format, len);
  return (0);
}

int			my_script_end(t_struct *ptr)
{
  struct termios	old;
  int			fd;

  old = ptr->old;
  if (tcsetattr(0, TCSANOW, &old) == -1)
    return (-1);
  if (ptr->fd_name == NULL)
    printf("Script done, file is typescript\n");
  else
    printf("Script done, file is %s\n", ptr->fd_name);
  write(ptr->fd, "\nScript done on", 15);
  fd = ptr->fd;
  write_time(&fd);
  if (close (fd) == -1)
    return (-1);
  if (close (ptr->fd) == -1)
    return (-1);
  return (0);
}
