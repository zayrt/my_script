/*
** my_script.h for myscript.h in /home/zellou_i
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Thu Feb 20 21:45:08 2014 ilyas zelloufi
** Last update Sun Mar  2 23:20:43 2014 ilyas zelloufi
*/

#ifndef MY_SCRIPT_H__
# define MY_SCRIPT_H__

#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <pty.h>

typedef struct		s_struct
{
  struct termios	old;
  int			fd;
  char			*fd_name;
  int			option;
} t_struct;

int			my_openpty(int *, int *);
int			my_logintty(int);
int			raw_mode(int);
int			my_read_input(int, int *);
int			my_read_master(int, t_struct *);
int			my_handle_master(int *, t_struct *, int);
int			my_forkpty(int *, int *, t_struct *);
int			my_script(t_struct *);
char			*check_file_name(int, char **);
int			check_option(int, char **);
t_struct		*my_handle_params(t_struct *);
int			write_time(int *);
int			my_script_end(t_struct *);
t_struct		*my_init_struct(int, char **);

#endif /* MY_SCRIPT_H__ */
