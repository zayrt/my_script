/*
** test.c for test in /home/zellou_i
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Wed Feb 19 11:54:09 2014 ilyas zelloufi
** Last update Sat Mar  1 22:53:27 2014 ilyas zelloufi
*/

#include "my_script.h"

int		my_read_input(int fd, int *fdm)
{
  char		buf[20];
  int		ret;

  ret = read(fd, buf, 20);
  if (ret == -1)
    {
      perror("Function read fail\n");
      return (-1);
    }
  else if (ret > 0)
    {
      buf[ret] = '\0';
      write(*fdm, buf, ret);
    }
  return (0);
}

int		my_read_master(int fdm, t_struct *ptr)
{
  char		buf[20];
  int		ret;

  ret = read(fdm, buf, 20);
  if (ret < 0)
    {
      my_script_end(ptr);
      exit (0);
    }
  else if (ret > 0)
    {
      buf[ret] = '\0';
      write(1, buf, ret);
      write(ptr->fd, buf, ret);
    }
  return (0);
}

int		my_handle_master(int *fdm, t_struct *ptr, int pid)
{
  int		ret;
  fd_set	set;

  FD_ZERO(&set);
  while (waitpid(pid, &ret, WNOHANG) != pid)
    {
      FD_SET(0, &set);
      FD_SET(*fdm, &set);
      if ((select(*fdm + 1, &set, NULL, NULL, NULL)) == -1)
	return (-1);
      if (FD_ISSET(0, &set))
	if (my_read_input(0, fdm) == -1)
	  return (-1);
      if (FD_ISSET(*fdm, &set))
	my_read_master(*fdm, ptr);
    }
    return (0);
}

int		my_script(t_struct *ptr)
{
  int		fdm;
  int		fds;
  int		fd;

  if ((ptr = my_handle_params(ptr)) == NULL)
    return (-1);
  if (ptr->fd_name == NULL)
    printf("Script started, file is typescript\n");
  else
    printf("Script started, file is %s\n", ptr->fd_name);
  write(ptr->fd, "Script started on", 17);
  fd = ptr->fd;
  write_time(&fd);
  if (my_forkpty(&fdm, &fds, ptr) == -1)
    return (-1);
  if (my_script_end(ptr) == -1)
    return (-1);
  return (0);
}
