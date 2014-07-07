/*
** my_libpty.c for my_libpty in /home/zellou_i/rendu/PSU_2013_myscript
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Thu Feb 20 16:10:17 2014 ilyas zelloufi
** Last update Fri Feb 28 01:20:17 2014 ilyas zelloufi
*/

#include "my_script.h"

int			my_openpty(int *fdm, int *fds)
{
  char			name[16];
  int			n;
  int			nb;

  nb = 0;
  if ((*fdm = open("/dev/ptmx", O_RDWR)) < 0)
    return (-1);
  if (ioctl(*fdm, TIOCGPTN, &n) < 0)
    return (-1);
  sprintf(name, "/dev/pts/%i", n);
  if (chmod(name, 0620) == -1)
    return (-1);
  if (ioctl(*fdm, TIOCSPTLCK, &nb) < 0)
    return (-1);
  if ((*fds = open(name, O_RDWR)) < 0)
    return (-1);
  return (0);
}

int			my_logintty(int fds)
{
  if (setsid() == -1)
    return (-1);
  if ((dup2(fds, 0)) == -1)
    return (-1);
  if ((dup2(fds, 1)) == -1)
    return (-1);
  if ((dup2(fds, 2)) == -1)
    return (-1);
  return (0);
}

int                     my_forkpty(int *fdm, int *fds, t_struct *ptr)
{
  int                   pid;
  char			*shell_name;

  if (my_openpty(fdm, fds))
    return (-1);
  if ((pid = fork()) < 0)
    return (-1);
  if (pid == 0)
    {
      close(*fdm);
      if (my_logintty(*fds) == -1)
	return (-1);
      if ((shell_name = getenv("SHELL")) == NULL)
	shell_name = "/bin/bash";
      if (execl(shell_name, "", NULL) == -1)
	return (-1);
     exit(0);
    }
  close(*fds);
  if (raw_mode(0) == -1)
    return (-1);
  if (my_handle_master(fdm, ptr, pid) == -1)
    return (-1);
  return (0);
}

int			raw_mode(int fd)
{
  struct termios	raw;

  if (tcgetattr(fd, &raw) == -1)
    return (-1);
  cfmakeraw(&raw);
  if (tcsetattr(fd, TCSANOW, &raw) == -1)
    return (-1);
  return (0);
}
