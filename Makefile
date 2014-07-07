##
## Makefile for Makefile in /home/zellou_i/rendu/PSU_2013_myscript
##
## Made by ilyas zelloufi
## Login   <zellou_i@epitech.net>
##
## Started on  Thu Feb 20 21:14:20 2014 ilyas zelloufi
## Last update Tue Feb 25 18:23:28 2014 ilyas zelloufi
##

CC = gcc

RM = rm -f

CFLAGS += -Wextra -Wall -Werror

LDFLAGS =

NAME = my_script

SRCS =	my_script.c \
	my_libpty.c \
	check_params.c \
	main.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
